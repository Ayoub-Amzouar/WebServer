#include "../../headers/webserv.hpp"

Response::Response(Http &http, char *env[]) : _http(http), _env(env)
{}

std::string Response::run(std::map<std::string, std::string> &header, std::string &body_string)
{
    int a = check_req_validity(header);
    if (a)
        return std::string("return response with a as status code");
    // Server server& = getServer(_http);
    
    return std::string("default");
}

Server& Response::getServer(Http &http, std::map<std::string, std::string> &header)
{
    std::string host = find_header(header, "Host");
    std::string del(":");
    std::vector<std::string> field = parse_line(host, del);
    std::string ip("80");
    std::string serverName = field[0];
    if (!field[1].empty())
        ip = field[1];
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        if (ip == (*it).attributes["listen"] && serverName == (*it).attributes["server-name"])
            return *it;
    }
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        if(ip == (*it).attributes["listen"])
            return *it;
    }
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        if(ip == (*it).attributes["server-name"])
            return *it;
    }
    return http.servers[0];
}

int Response::check_req_validity(const std::map<std::string, std::string> &header)
{
    std::string content_length = find_header(header, "Content-Length");
    std::string content_type = find_header(header, "Content-Type");
    std::string transfer_encoding = find_header(header, "Transfer-Encoding");
    std::string method = find_header(header, "method");
    std::string uri = find_header(header, "location");
    std::string host = find_header(header, "Host");
    {                                                                       // URI
        if (uri.find_first_not_of(ALLOWED_CHARACTERS) != std::string::npos) // 400
            return 400;
        else if (uri.length() > 2048) // 414
            return 414;
    }
    { // POST
        if (method == "POST")
        {
            if (content_type.empty() || content_length.empty() || transfer_encoding.empty())
                return 400;
            else if (transfer_encoding != "chunked")
                return 501;
        }
    }
    {// Host header empty => error
        if (host.empty())
            return 400;
    }
    return 0;
}

std::string Response::find_header(const std::map<std::string, std::string> &header, const std::string &str)
{
    std::map<std::string, std::string>::const_iterator end = header.end();
    std::map<std::string, std::string>::const_iterator it = header.find(str);
    if (it != end)
        return std::string("");
    return it->second;
}

