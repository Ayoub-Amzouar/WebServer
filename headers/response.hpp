#pragma once

#include "webserv.hpp"

#define ALLOWED_CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%"

struct Response
{
private:
    char** _env;
    Http    &_http;

private:
    std::string find_header(const std::map<std::string, std::string> &,const std::string&);
	int check_req_validity(const std::map<std::string, std::string> &header);

public:
    Response(Http &http, char *env[]);
    std::string run(std::map<std::string, std::string> &headers, std::string &body_string);
};
