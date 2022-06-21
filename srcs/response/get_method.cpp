#include "../../headers/webserv.hpp"

std::string Response::get_method(const ErrorPage &errPage, const Location &locationMap, const std::map<std::string, std::string> &requestMap, const std::string &body_file)
{
    //  get variables from location
    std::string index = Utils::find_in_map(locationMap, "index");
    std::string root = Utils::find_in_map(locationMap, "root");
    std::string path = Utils::find_in_map(locationMap, "path");
    std::string cgi = Utils::find_in_map(locationMap, "cgi-name");
    //  get variables from request Map
    std::string uri = Utils::find_in_map(requestMap, "location");
    std::string content_length = Utils::find_in_map(requestMap, "Content-Length");
    std::string content_type = Utils::find_in_map(requestMap, "Content-Type");
}