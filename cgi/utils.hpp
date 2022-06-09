#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>
#include <vector>
#include <map>

std::string status_line(int code);
std::string content_type(std::string exten);
bool doesFileExist (const std::string&);
std::vector<std::string> parse_line(std::string str, std::string &delim);

class StatusCode
{
    std::map<int, std::string> _code;

public:
    StatusCode();
    std::string get_message(int code) const;
};

class ContentType
{
    std::map<std::string, std::string> _code;

public:
    ContentType();
    std::string get_mime(std::string extension) const;
};
#endif