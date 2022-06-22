#include "../../headers/webserv.hpp"

std::string Response::get_method(const ErrorPage &errPage, const Location &locationMap, const std::map<std::string, std::string> &requestMap, const std::string &body_file)
{
    //  get variables from location
    std::string index = Utils::find_in_map(locationMap.attributes, "index");
    std::string root = Utils::find_in_map(locationMap.attributes, "root");
    std::string path = Utils::find_in_map(locationMap.attributes, "path");
    std::string cgi = Utils::find_in_map(locationMap.attributes, "cgi-name");
    std::string autoindex = Utils::find_in_map(locationMap.attributes, "autoindex");
    //  get variables from request Map
    std::string uri = Utils::find_in_map(requestMap, "location");
    std::string content_length = Utils::find_in_map(requestMap, "Content-Length");
    std::string content_type = Utils::find_in_map(requestMap, "Content-Type");

    std::string url = Utils::give_me_uri(locationMap, requestMap);
    file_stats res = Utils::get_file_stats(url);
    file_stats res = Utils::get_file_stats(url);
    if (!(res.exist))
        errPage.get_page(404);
    // DIR
    else if (res.type == FT_DIR)
    {
        // request uri doesn't have / at the end
        if ((url.c_str())[url.length() - 1] != '/')
        {
            // return Utils::status_line(301) + "\n" + Utils::location("http:/" + (Utils::parse_uri(uri)).first + "/") + "\n" + Utils::content_length(0) + "\n" + Utils::content_type("html") + "\n\n";
            std::string redirect = std::to_string(301) + "|http:/" + (Utils::parse_uri(uri)).first + "/";
            return redirection(redirect);
        }
        //  if dir has index files
        res = Utils::get_file_stats(url + index);
        if (res.exist)
        {
            if (!res.r_perm)
                errPage.get_page(403);
        }
        //  autoindex
        else
        {
            if (autoindex == "off")
                errPage.get_page(403);
        }
    }
    // FILE
    else
    {
    }
}