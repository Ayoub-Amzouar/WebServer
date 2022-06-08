#include "status_code.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <string>

std::string status_line(int code)
{
    static const StatusCode s;
    std::string exist = s.get_message(code);
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

bool doesFileExist(const std::string &name)
{
    std::ifstream f(name.c_str());
    return f.good();
}

std::vector<std::string> parse_line(std::string str, std::string &delim)
{
    std::vector<std::string> strings;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delim)) != std::string::npos)
    {
        token = str.substr(0, pos);
        strings.push_back(token);
        str.erase(0, pos + delim.length());
    }
    return strings;
}