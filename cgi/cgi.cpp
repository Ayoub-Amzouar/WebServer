#include "cgi.hpp"
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <map>

Cgi::Cgi(std::string path, char *env[])
: _path(path)
, _env(env)
{}

int Cgi::execute(char *args[])
{
    if (fork() == 0)
    {
        std::string filename("tmp.log");
        std::ofstream file;
        file.open(filename);
        file << code_and_reason(200) << std::endl;
        file.close();

        int fd = open(filename.c_str(), O_RDWR | O_APPEND);
        dup2(fd, 1);
        execve(_path.c_str(), args, _env);
        perror("CGI path error");
        exit(1);
    }
    wait(NULL);
    return 0;
}
std::string Cgi::code_and_reason(int code)
{
    std::string exist = _status_code.get_message(code);
    if (!exist.empty())
    {
        std::string status("HTTP1.1 ");
        status.append(std::to_string(code));
        status.append(" ");
        status.append(exist);
        return status;
    }
    else
        return std::string();
}