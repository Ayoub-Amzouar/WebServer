#include "../../headers/webserv.hpp"

std::string autoindexFileTime(std::string file_name)
{
    struct stat info;
    struct tm *tm_info;
    char buffer[20];
    stat(file_name.c_str(), &info);
    tm_info = localtime(&info.st_mtime);
    strftime(buffer, sizeof(buffer), "%b-%d-%Y %H:%M", tm_info);
    return buffer;
}

std::string Utils::autoindex_dir(const std::string path, const std::string uri)
{
    file_stats fs = Utils::get_file_stats(path);
    if (!fs.exist || !fs.r_perm)
        return std::string();
    std::string content;
    DIR *dir;
    struct dirent *ent;
    struct stat buf;
    if ((dir = opendir(path.c_str())) != NULL)
    {
        content = "<html><head><title>Index of " + uri + "</title></head><body bgcolor=\"white\"> <h1>Index of " + uri + "</h1><hr><pre>";
        while ((ent = readdir(dir)) != NULL)
        {
            std::string file = ent->d_name;
            if (file == ".")
                continue;
            std::string file_path = path + "/" + file;
            stat(file_path.c_str(), &buf);
            content += "<a href=\"" + uri + file;
            file_stats res = Utils::get_file_stats(file_path);
            content += (res.type == FT_DIR) ? "/" : "";
            content += file;
            if (res.type == FT_DIR)
                content += "/\">" + file + "/</a>";
            else
                content += "\">" + file + "</a>";
            if (file != "..")
            {
                content += autoindexFileTime(file_path);
                if (res.type != FT_DIR)
                    content += std::to_string(buf.st_size);
                else
                    content += "-";
            }
            content += "\n";
        }
        closedir(dir);
        content += "</pre><hr></body></html>";
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
        if (!index.empty() || !res.exist)
        {
            if (autoindex != "on" && !autoindex.empty())
                errPage.get_page(403);
            std::string autoindex_res = Utils::autoindex_dir(url, uri);
            return autoindex_res;
        }
        url += index;
    }
    //  FILE 
    res = Utils::get_file_stats(url);
    std::string file_extension = Utils::getFileExtension(url);
    if (!cgi.empty() && file_extension == cgi_extenstion)
    {
        // TODO: try to find the passed args to cgi;
        // Cgi cgi("php-cgi");
        // std::string cgi_res = cgi.run("GET", uri, body_file, root);
        // if(cgi_res.empty())
            return errPage.get_page(500);
        // return cgi_res;
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
