#include "../../headers/webserv.hpp"

// Response::Response(Http &http, char *env[]) : _http(http), _env(env)
Response::Response(Http &http) : _http(http)
{
    for (std::vector<Server>::iterator it = _http.servers.begin(); it != _http.servers.end(); it++)
    {
        _serversErrors.push_back(ErrorPage(find_header((*it).attributes, "error-pages")));
    }
}

std::string Response::run(std::map<std::string, std::string> &request, std::string &body_file)
{
    // is_req_well_formed
    {
        ErrorPage err("");
        int reqValdity = check_req_validity(request);
        if (reqValdity)
            return err.get_page(reqValdity);
    }
    // chouse server from config file
    int server_num = getServer(_http, request);
    Server &server = _http.servers[server_num];
    {
        ErrorPage &err = _serversErrors[server_num];
        //  check body size for post method
        int max_body_size = maxBodySize(server, request);
        if (max_body_size)
            return err.get_page(max_body_size);
        // get_matched_location_for_request_uri
        int location_num = getLocation(server, request);
        if (location_num == -1)
            return err.get_page(404);
        // choose location from server from config file
        Location &location = server.locations[location_num];
        // if location have redirection
        std::string redirect = find_header(location.attributes, "return");
        if (!redirect.empty())
            std::string("return redirection with " + redirect + " variable + you have to split the variable with red_code:locaiton");
        // allowded methods in location
        std::string methods = find_header(location.attributes, "methods");
        std::string reqMethod = find_header(request, "method");
        if (!methods.empty() && !reqMethod.empty())
        {
            std::vector<std::string> method = parse_line(methods, ",");
            std::vector<std::string>::iterator end = std::find(method.begin(), method.end(), reqMethod);
            if (end == method.end())
                return err.get_page(405);
        }
        // if (reqMethod == "GET")
        //     return get_method(location, request);
        // else if (reqMethod == "POST")
        //     return post_method(location, request, body_file);
        // else if (reqMethod == "DELETE")
        //     return delete_method(location, request);
    return err.get_page(404);
    }
}

int Response::getLocation(Server &server, std::map<std::string, std::string> &request)
{
    std::string location = find_header(request, "location");
    std::pair<std::string, std::string> uri_pair = parse_uri(location);
    std::string uri = uri_pair.first;
    int i;
    while(!uri.empty())
    {
        i = 0;
        for (std::vector<Location>::iterator it = server.locations.begin(); it != server.locations.end(); it++)
        {
            std::string path = (*it).attributes["path"];
            if (uri == path)
                return i;
            i++;
        }
        uri = cut_uri(uri);
    }
    return -1;
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

int Response::getServer(Http &http, std::map<std::string, std::string> &request)
{
    std::vector<std::string> field = parse_line(request["Host"], ":");
    std::string reqHost = field[0];
    std::string reqPort = field[1].empty() ? "80" : field[1]; // 80 is the default port if the host header doesn't have one.

    int i = 0;
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string port = find_header((*it).attributes, "listen");
        std::string host = find_header((*it).attributes, "host");
        std::string server_name = find_header((*it).attributes, "server-name");
        if ((reqHost == server_name || reqHost == host) && reqPort == port)
            return i;
        i++;
    }
    i = 0;
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string port = find_header((*it).attributes, "listen");
        if (reqPort == port)
           return  i;
        i++;
    }
    i = 0;
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string host = find_header((*it).attributes, "host");
        if (reqHost == host)
           return  i;
        i++;
    }
    i = 0;
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string server_name = find_header((*it).attributes, "server-name");
        if (reqHost == server_name)
            return i;
        i++;
    }
    return 0;
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

