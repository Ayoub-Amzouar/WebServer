#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>
#include <vector>
#include <map>

std::string status_line(int code);
bool doesFileExist (const std::string&);
std::vector<std::string> parse_line(std::string str, std::string &delim);

class StatusCode
{
    std::map<int, std::string> _code;

public:
    StatusCode();
    std::string get_message(int code) const;
};

#endif