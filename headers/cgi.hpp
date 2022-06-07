#ifndef _CGI_HPP_
#define _CGI_HPP_

#include "webserv.hpp"


struct Cgi
{
    private:
        std::string _path;
        char **_env; 

    public:
        Cgi(std::string path, char *env[]) : _path(path), _env(env) {}
        int execute(char *args[])
        {
            if (fork() == 0)
            {
                int fd = open("tmp.log", O_RDWR);
                dup2(fd, 1);
                execve(_path.c_str(), args, _env);
                perror("CGI path error");
                exit(1);
            }
            wait(NULL);
            return 0;
        }
};
#endif