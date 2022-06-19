#pragma once

#include "webserv.hpp"

struct Cgi
{
private:
    std::string     _path;
    char**          _env;
    std::string     _cgi_out_file;
    std::string     _response_file;
    bool            _error;
    std::string     _file;

private:
    int     cgi_status_code(void);
    int     execute(std::string);
    void    error(std::string);
    void    fileInOut(std::string, std::string);
    void    generate_response(int);
    void    send_response(int);
    std::string get_file(std::string);
    std::map<std::string, std::string>  parse_cgi_output(void);

public:
    Cgi(std::string &cgi_name, char *env[]);
    std::string POST(std::string uri, std::string body_file, std::string root);
    std::string GET(std::string uri, std::string root);
    // std::string DELETE();
};