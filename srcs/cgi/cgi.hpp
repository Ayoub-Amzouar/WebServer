#ifndef _CGI_HPP_
#define _CGI_HPP_

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <map>
#include <utility>

struct Cgi
{
private:
    std::string     _path;
    char**          _env;
    std::string     _cgi_out_file;
    std::string     _response_file;
    bool            _error;

private:
    int     cgi_status_code(void);
    int     execute(std::string, std::string);
    void    error(std::string);
    void    fileInOut(std::string, std::string);
    void    generate_response(int);
    void    send_response(int);
    std::string get_file(std::string);
    std::map<std::string, std::string>  parse_cgi_output(void);
    std::pair<std::string, std::string> parse_uri(std::string);

public:
    Cgi(std::string, char **);
    int POST(std::string uri, int socket_write, std::string body_file);
    int GET(int fd);
    // std::string DELETE();
};

#endif