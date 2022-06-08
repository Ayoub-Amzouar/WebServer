#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>
#include <vector>

std::string status_line(int code);
bool doesFileExist (const std::string&);
std::vector<std::string> parse_line(std::string str, std::string &delim);

#endif