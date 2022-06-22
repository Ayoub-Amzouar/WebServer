#include "../../headers/webserv.hpp"

std::string autoindex_dir(std::string path)
{
    std::string content;
    DIR *dir;
    struct dirent *ent;
    struct stat buf;
    if ((dir = opendir(path.c_str())) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            std::string file = ent->d_name;
            std::string file_path = path + "/" + file;
            stat(file_path.c_str(), &buf);
            content += file;
            content += " ";
            content += std::to_string(buf.st_size);
            content += " ";
            content += std::to_string(buf.st_mtime);
            content += "\n";
        }
        closedir(dir);
    }
    return content;
}

std::string Response::get_method(const ErrorPage &errPage, const Location &locationMap, const std::map<std::string, std::string> &requestMap, const std::string &body_file)
{
    //  get variables from location
    std::string index = Utils::find_in_map(locationMap.attributes, "index");
    std::string root = Utils::find_in_map(locationMap.attributes, "root");
    std::string path = Utils::find_in_map(locationMap.attributes, "path");
    std::string cgi = Utils::find_in_map(locationMap.attributes, "cgi-name");
    std::string cgi_extenstion = Utils::find_in_map(locationMap.attributes, "cgi-name");
    std::string autoindex = Utils::find_in_map(locationMap.attributes, "autoindex");
    //  get variables from request Map
    std::string uri = Utils::find_in_map(requestMap, "location");
    std::string content_length = Utils::find_in_map(requestMap, "Content-Length");
    std::string content_type = Utils::find_in_map(requestMap, "Content-Type");

    std::string url = Utils::give_me_uri(locationMap, requestMap);
    file_stats res = Utils::get_file_stats(url);
    if (!(res.exist))
        errPage.get_page(404);
    // DIR
    if (res.type == FT_DIR)
    {
        if ((url.c_str())[url.length() - 1] != '/')
        {
            std::string redirect = std::to_string(301) + "|http:/" + (Utils::parse_uri(uri)).first + "/";
            return redirection(redirect);
        }
        res = Utils::get_file_stats(url + index);
        if (!index.empty() || !res.exist())
        {
            if (autoindex != "on" && autoindex != "")
                errPage.get_page(403);
            std::string autoindex_res = autoindex_dir(url);
            return autoindex_res;
        }
        url += index;
    }
    //  FILE 
    res = Utils::get_file_stats(url);
    std::string file_extension = Utils::getFileExtension(url);
    // TODO: try to figure out which of the index file and location have a cgi
    if (!cgi.empty())
    {
    }
    if (!res.r_perm)
        errPage.get_page(403);
    std::string content = Utils::fileToStr(url);
    std::string contentType;
    if (file_extension.empty())
        contentType = "Content-Type: application/octet-stream";
    else
        contentType = Utils::content_type(file_extension);
    return Utils::status_line(200) + "\n" + contentType + "\n" + Utils::content_length(content.length()) + "\n\n" + content;
}
