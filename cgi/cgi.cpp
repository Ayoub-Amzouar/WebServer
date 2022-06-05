#include "cgi.hpp"
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include "utils.hpp"
#include <map>
#include <vector>

Cgi::Cgi(std::string path, char *env[])
: _path(path)
, _env(env)
, _file(std::tmpnam(NULL))
, _error(false)
{}

void Cgi::error(std::string e)
{
    std::cerr << "CGI: " << e << std::endl;
}

int Cgi::execute(char *args[], int fd)
{
    std::vector<std::string> querys = parse_uri(std::string(args[1]));
    if (fork() == 0)
    {
        int fd = open(_file.c_str(), O_RDWR | O_TRUNC | O_CREAT, 0666);
        // int fd = open(_file.c_str(), O_RDWR | O_APPEND | O_CREAT, 0666);
        if (fd== -1)
            error("can't open " + _file + ".");
        dup2(fd, 1);
        execve(_path.c_str(), args, _env);
        error("path to executable not correct.");
        exit(1);
    }
    wait(NULL);
    std::map<std::string, std::string> out = parse_cgi_output();
    std::map<std::string, std::string>::iterator it = out.find("Status");

    std::string fl("tmp/response.log");
    int code;

    {
        if (it != out.end())
        {
            const std::string &line = it->second;
            code = std::stoi(line.substr(0, line.find(" ")));
        }
        else // 200
            code = 200;

        std::ifstream in;
        in.open(_file, std::ios::app);
        std::ofstream out;
        out.open(fl);
        out << status_line(code) << std::endl;
        out.close();
        fileInOut(_file, fl);
    }
    {
        std::ifstream in;
        in.open(fl);
        std::string line;
        while (in)
        {
            getline(in, line);
            line.push_back('\n');
            write(fd, line.c_str(), line.length());
        }
        in.close();
    }
    return 0;
}

std::vector<std::string> Cgi::parse_uri(std::string uri)
{
    std::vector<std::string> query;
    int pos;
    pos = uri.find("?");
    if (pos == -1)
        return query;
    uri.erase(0, pos + 1);
    // std::cout << "***************** uri = " << uri << " **************"<< std::endl;
    while ((pos = uri.find("&")) != std::string::npos)
    {
        query.push_back(uri.substr(0, pos));
        uri.erase(0, pos + 1);
    }
    query.push_back(uri);
    return query;
}

std::map<std::string, std::string> Cgi::parse_cgi_output(void)
{
    std::fstream f;
    f.open(_file);
    if (!f.is_open())
        error("can't open random file.");
    std::string line;
    std::map<std::string, std::string> data;
    while(f)
    {
        getline(f, line);
        if (line.empty())
            break;
        int pos = line.find(":");
        if (pos != -1)
            data[line.substr(0, pos)] = line.substr(pos + 2);
    }
    f.close();
    return data;
}

void Cgi::fileInOut(std::string in_file , std::string out_file)
{
    std::ifstream in;
    std::ofstream out;
    std::string line;

    in.open(in_file);
    out.open(out_file, std::ios::app);
    while (in)
    {
        getline(in, line);
        out << line << std::endl;
    }
    in.close();
    out.close();
}