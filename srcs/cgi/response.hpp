#ifndef _RESPONSE_HPP_
#define _RESPONSE_HPP_

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <map>
#include <utility>

struct Response
{
private:
    char** _env;

private:


public:
    Response(char *env[]);
    std::string run(std::string cgiExnt, std::string cgiName, std::string root, std::string method, std::string uri, std::string reqBody);
};

#endif