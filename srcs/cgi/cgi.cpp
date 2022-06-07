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
#include <cstdlib>
#include <utility>

Cgi::Cgi(std::string path, char *env[])
: _path(path)
, _env(env)
, _cgi_out_file(std::tmpnam(NULL))
, _response_file(std::tmpnam(NULL))
, _error(false)
{}

void Cgi::error(std::string e)
{
    std::cerr << "CGI: " << e << std::endl;
}

std::pair<std::string, std::string> Cgi::parse_uri(std::string uri)
{
    int pos;
    pos = uri.find("?");
    if (pos == -1)
        return make_pair(uri, std::string(""));
    return make_pair(uri.substr(0, pos), uri.substr(pos + 1));
}

void Cgi::fileInOut(std::string in_file , std::string out_file)
{
    std::ifstream   in;
    std::ofstream   out;
    std::string     line;

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

std::map<std::string, std::string> Cgi::parse_cgi_output(void)
{
    std::fstream f;
    f.open(_cgi_out_file);
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

int Cgi::execute(std::string cgi_file, std::string body_file)
{
    if (fork() == 0)
    {
        int output_fd, fd;
        if ((output_fd = open(_cgi_out_file.c_str(), O_RDWR | O_TRUNC | O_CREAT, 0666) == -1))
            error("can't open output_file for cgi.");

        if (!body_file.empty())
        {
            // int fd;
            if ((fd = open(body_file.c_str(), O_RDWR)) == -1)
                error("can't open body file for cgi.");
            dup2(fd, STDIN_FILENO);
        }
        dup2(fd, STDOUT_FILENO);
        char *args[3];
        args[0] = (char *)_path.c_str();
        args[1] = (char *)cgi_file.c_str();
        args[2] = NULL;
        execve(_path.c_str(), args, _env);
        error("path to cgi executable not correct.");
        exit(1);
    }
    wait(NULL);
    return 0;
}

int Cgi::cgi_status_code(void)
{
    std::map<std::string, std::string> out = parse_cgi_output();
    std::map<std::string, std::string>::iterator it = out.find("Status");
    if (it != out.end())
    {
        const std::string &line = it->second;
        return std::stoi(line.substr(0, line.find(" ")));
    }
    else // default
        return 0;
}

void Cgi::generate_response(int code)
{
    std::ofstream out;
    out.open(_response_file, std::ios::trunc);
    out << status_line(code) << std::endl;
    out.close();
    fileInOut(_cgi_out_file, _response_file);
}
void Cgi::send_response(int fd)
{
    std::ifstream in;
    in.open(_response_file);
    std::string line;
    while (in)
    {
        getline(in, line);
        line.push_back('\n');
        write(fd, line.c_str(), line.length());
    }
    in.close();
}

int Cgi::GET(int fd)
{
    std::pair<std::string, std::string> parsed_uri = parse_uri(uri);

    setenv("QUERY_STRING", (parsed_uri.second).c_str(), true);
    setenv("REQUEST_METHOD", "GET", true);
    execute((parsed_uri.first).c_str(), body_file);
    int cgi_code = cgi_status_code();
    if (cgi_code == 0) // no status by cgi.
        generate_response(0);
    else
        generate_response(cgi_code);
    send_response(write_socket);
    return 0;
}

int Cgi::POST(std::string uri, int write_socket, std::string body_file)
{
    std::pair<std::string, std::string> parsed_uri = parse_uri(uri);

    setenv("QUERY_STRING", (parsed_uri.second).c_str(), true);
    setenv("REQUEST_METHOD", "POST", true);
    std::cout << parsed_uri.first << std::endl;
    std::cout << parsed_uri.second << std::endl;
    // execute((parsed_uri.first).c_str(), body_file);
    int cgi_code = cgi_status_code();
    if (cgi_code == 0) // no status by cgi.
        generate_response(0);
    else
        generate_response(cgi_code);
    send_response(write_socket);
    return 0;
}


