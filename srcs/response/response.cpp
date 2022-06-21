#include "../../headers/webserv.hpp"

// Response::Response(Http &http, char *env[]) : _http(http), _env(env)
Response::Response(Http &http) : _http(http)
{
    std::vector<ErrorPage> errors;
    for (std::vector<Server>::iterator it = _http.servers.begin(); it != _http.servers.end(); it++)
    {
        errors.push_back(ErrorPage(Utils::find_in_map((*it).attributes, "error-pages")));
    }
    _serversErrors = errors;
}

std::string Response::run(std::map<std::string, std::string> &request, std::string &body_file)
{
    // is_req_well_formed
    {
    // std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        ErrorPage err("");
        int reqValdity = check_req_validity(request);
        // std::cout << "REQUEST VALID"<<reqValdity << std::endl;
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

        // TODO: location have redirection like: return 301 /home/index.html
        // Syntax:	return code [text];
        //          return code URL;
        //          return URL;
        // Default:	—
        // Context:	server, location, if

        // return       301 https://example.com$request_uri;
        // return       301 $scheme://www.new-name.com$request_uri;
        // return (301 | 302 | 303 | 307) url;
        // return 401 "Access denied because token is expired or invalid";


        std::string redirect =  Utils::find_in_map(location.attributes, "return");
        if (!redirect.empty())
        {
            std::string redirect_ret = redirection(redirect);
            if (!redirect_ret.empty())
                return redirect_ret;
        }
		// allowded methods in location
        std::string methods =  Utils::find_in_map(location.attributes, "methods");
        std::string reqMethod =  Utils::find_in_map(request, "method");
        if (!methods.empty() && !reqMethod.empty())
        {
            std::vector<std::string> method =  Utils::parse_line(methods, ",");
            std::vector<std::string>::iterator end = std::find(method.begin(), method.end(), reqMethod);
            if (end == method.end())
                return err.get_page(405);
        }
        // if (reqMethod == "GET")
        //     return get_method(err, location, request, body_file);
        // else if (reqMethod == "POST")
        //     return post_method(err, location, request, body_file);
        // else if (reqMethod == "DELETE")
        //     return delete_method(err, location, request, body_file);
    return err.get_page(404);
    }
}

int Response::getLocation(Server &server, std::map<std::string, std::string> &request)
{
    std::string location =  Utils::find_in_map(request, "location");
    std::pair<std::string, std::string> uri_pair =  Utils::parse_uri(location);
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
        uri = Utils::cut_uri(uri);
    }
    return -1;
}

int Response::maxBodySize(Server &server, std::map<std::string, std::string> &request)
{
    std::string method =  Utils::find_in_map(request, "method");
    std::string content_length =  Utils::find_in_map(request, "Content-Length");
    std::string max_body_size =  Utils::find_in_map(server.attributes, "max-body-size");
    if (method == "POST" && !max_body_size.empty() && std::stol(max_body_size) < std::stol(content_length))
        return 413;
    return 0;
}

int Response::getServer(Http &http, std::map<std::string, std::string> &request)
{
    std::vector<std::string> field =  Utils::parse_line(request["Host"], ":");
    std::string reqHost = field[0];
    std::string reqPort = field[1].empty() ? "80" : field[1]; // 80 is the default port if the host header doesn't have one.

    int i = 0;
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string port =  Utils::find_in_map((*it).attributes, "listen");
        std::string host =  Utils::find_in_map((*it).attributes, "host");
        std::string server_name =  Utils::find_in_map((*it).attributes, "server-name");
        if ((reqHost == server_name || reqHost == host) && reqPort == port)
            return i;
        i++;
    }
    i = 0;
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string port =  Utils::find_in_map((*it).attributes, "listen");
        if (reqPort == port)
           return  i;
        i++;
    }
    i = 0;
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string host =  Utils::find_in_map((*it).attributes, "host");
        if (reqHost == host)
           return  i;
        i++;
    }
    i = 0;
    for (std::vector<Server>::iterator it = (http.servers).begin(); it != (http.servers).end(); it++)
    {
        std::string server_name =  Utils::find_in_map((*it).attributes, "server-name");
        if (reqHost == server_name)
            return i;
        i++;
    }
    return 0;
}
std::string Response::redirection(std::string &redirect_str)
{
    int array[] = {301, 302, 303, 307};
    std::vector<int> redirect_codes(array, array + sizeof(array) / sizeof(int));

    std::vector<std::string> parse = Utils::parse_line(redirect_str, "|");
    if ((parse[0]).empty() || (parse[1]).empty())
        return std::string();

    int int_code = std::stoi(parse[0]);
    std::string status_line = Utils::status_line(int_code);
    std::string location_line = Utils::location(parse[1]);

    for(std::vector<int>::iterator it = redirect_codes.begin(); it != redirect_codes.end(); it++)
    {
        if (int_code == *it)
            return status_line + "\n" + location_line + "\n\n";
    }
    return std::string();
}

int Response::check_req_validity(const std::map<std::string, std::string> &request)
{
    std::string content_length =  Utils::find_in_map(request, "Content-Length");
    std::string content_type =  Utils::find_in_map(request, "Content-Type");
    std::string transfer_encoding =  Utils::find_in_map(request, "Transfer-Encoding");
    std::string method =  Utils::find_in_map(request, "method");
    std::string uri =  Utils::find_in_map(request, "location");
    std::string host =  Utils::find_in_map(request, "Host");
    std::cout << "******************************" << std::endl;
    std::cout << content_length << std::endl;
    std::cout << content_type << std::endl;
    std::cout << transfer_encoding << std::endl;
    std::cout << method << std::endl;
    std::cout << uri << std::endl;
    std::cout << host << std::endl;
    std::cout << "******************************" << std::endl;
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
