#include "../../headers/webserv.hpp"

Response::Response(Http &http, char *env[]) : _http(http), _env(env)
{}

std::string Response::run(std::map<std::string, std::string> &request, std::string &body_string)
{
    int error = check_req_validity(request);
    if (error)
        return std::string("return response with a as status code");
    Server &server = getServer(_http, request);
    error = maxBodySize(server, request);
    if (error)
        return std::string("return response with a as status code");
    Location &location = getLocation(server, request);

    return std::string("default");
}

Location &Response::getLocation(Server &server, std::map<std::string, std::string> &request)
{
    std::string location = find_header(request, "location");
    std::pair<std::string, std::string> uri_pair = parse_uri(location);
    std::string uri = uri_pair.first;
    for (std::vector<Location>::iterator it = server.begin(); it != servers.end(); it++)
    {
        std::string path = (*it).attributes["path"];
    }
    return server.locations[0];
}

int Response::maxBodySize(Server &server, std::map<std::string, std::string> &request)
{
    std::string method = find_header(request, "method");
    std::string content_length = find_header(request, "Content-Length");
    std::string max_body_size = find_header(server.attributes, "max-body-size");
    if (method == "POST" && !max_body_size.empty() && std::stol(max_body_size) < std::stol(content_length))
        return 413;
    return 0;
}

Server& Response::getServer(Http &http, std::map<std::string, std::string> &request)
{
    std::vector<std::string> field = parse_line(request["Host"], ":");
    std::string reqHost = field[0];
    std::string reqPort = field[1].empty() ? "80" : field[1]; // 80 is the default port if the host header doesn't have one.

    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string port = find_header((*it).attributes, "listen");
        std::string host = find_header((*it).attributes, "host");
        std::string server_name = find_header((*it).attributes, "server-name");
        if ((reqHost == server_name || reqHost == host) && reqPort == port)
            return *it;
    }
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string port = find_header((*it).attributes, "listen");
        if (reqPort == port)
            return *it;
    }
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string host = find_header((*it).attributes, "host");
        if (reqHost == host)
            return *it;
    }
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string server_name = find_header((*it).attributes, "server-name");
        if (reqHost == server_name)
            return *it;
    }
    return http.servers[0];
}

int Response::check_req_validity(const std::map<std::string, std::string> &request)
{
    std::string content_length = find_header(request, "Content-Length");
    std::string content_type = find_header(request, "Content-Type");
    std::string transfer_encoding = find_header(request, "Transfer-Encoding");
    std::string method = find_header(request, "method");
    std::string uri = find_header(request, "location");
    std::string host = find_header(request, "Host");
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
    {// Host request empty => error
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

