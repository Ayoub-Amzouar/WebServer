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
    std::string slash("/");

    std::string resource = root + "/" + Utils::erasePathFromUri((Utils::parse_uri(uri)).first, path);
    if (!(Utils::get_file_stats(resource).r_perm))
        return errPage.get_page(404);
    if (resource[resource.length() - 1] == slash[0])
    {
    }
}