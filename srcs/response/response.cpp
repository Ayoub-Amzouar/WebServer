#include "../../headers/webserv.hpp"

Response::Response(Http &http, char *env[]) : _http(http), _env(env)
{}

std::string Response::run(std::map<std::string, std::string> &header, std::string &body_string)
{
    int a = check_req_validity(header);
    if (a)
        return std::string("return response with a as status code");
    return std::string("default");
}

int Response::check_req_validity(const std::map<std::string, std::string> &header)
{
    std::string content_length = find_header(header, "Content-Length");
    std::string content_type = find_header(header, "Content-Type");
    std::string transfer_encoding = find_header(header, "Transfer-Encoding");
    std::string method = find_header(header, "method");
    std::string uri = find_header(header, "location");
    {                                                                       // URI
        if (uri.find_first_not_of(ALLOWED_CHARACTERS) != std::string::npos) // 400
            return 400;
        else if (uri.length() > 2048) // 414
            return 414;
    }
    { // POST
        if (method == "POST")
        {
            if (!content_type.empty() || !content_length.empty() || !transfer_encoding.empty())
                return 400;
            else if (transfer_encoding != "chunked")
                return 501;
        }
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

