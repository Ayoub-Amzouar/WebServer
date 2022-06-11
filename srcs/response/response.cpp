#include "response.hpp"
#include "utils.hpp"
#include "cgi.hpp"

Response::Response(char *env[]) : _env(env)
{}

std::string Response::run(std::string cgiExnt, std::string cgiName, std::string root, std::string method, std::string uri, std::string reqBody)
{
    std::pair<std::string, std::string> pr = parse_uri(uri);
    std::string path = pr->first;
}