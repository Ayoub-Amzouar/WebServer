#ifndef _CGI_HPP_
#define _CGI_HPP_

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <map>
#include "status_code.hpp"

struct Cgi
{
private:
    std::string _path;
    char **_env;
    const StatusCode _status_code;

public:

    Cgi(std::string path, char *env[]);
    int execute(char *args[]);
    std::string code_and_reason(int code);
};
#endif