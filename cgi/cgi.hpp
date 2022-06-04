#ifndef _CGI_HPP_
#define _CGI_HPP_

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <map>

struct Cgi
{
private:
    std::string     _path;
    char**          _env;
    std::string     _file;
    bool            _error;

private:
    std::map<std::string, std::string> parse_cgi_output(void);
    std::vector<std::string> parse_uri(std::string);
    void error(std::string);
    void fileInOut(std::string, std::string);

public:
    Cgi(std::string, char **);
    int execute(char **, int );
};

#endif