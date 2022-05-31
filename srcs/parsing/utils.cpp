#include "../../headers/parsing.hpp"

std::map<std::string, std::string> extract_key_value(std::string line)
{
    std::string key;
    std::string value;
    std::map<std::string, std::string> pair;
    size_t pos;

    pos = line.find('=');
    key = line.substr(0, pos);
    value = line.substr(pos + 1, line.length());
    pair.insert(std::pair<std::string, std::string>(key, value));
    return pair;
}
