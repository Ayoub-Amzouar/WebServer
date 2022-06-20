#pragma once

//  #include "webserv.hpp"
//  #include "utils.hpp"
//  #include "parsing.hpp"
class Http;

#define ALLOWED_CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%"

struct Response
{
private:
    // char**  _env;
    Http    &_http;
    std::vector<ErrorPage> _serversErrors;

private:
    std::string		find_header(const std::map<std::string, std::string> &, const std::string &);
    int				check_req_validity(const std::map<std::string, std::string> &);
    int             getServer(Http &, std::map<std::string, std::string> &);
    int				maxBodySize(Server &, std::map<std::string, std::string> &);
    int             getLocation(Server &server, std::map<std::string, std::string> &request);
    std::string		get_method(const ErrorPage&, const Location&, const std::map<std::string, std::string> &);
	std::string		post_method(const ErrorPage&, const Location &, const std::map<std::string, std::string> &, const std::string &);
	std::string		delete_method(const ErrorPage&, const Location &, const std::map<std::string, std::string> &);

public:
    // Response(Http &http, char *env[]);
    Response(Http &http);
    std::string run(std::map<std::string, std::string> &headers, std::string &body_string);
};
