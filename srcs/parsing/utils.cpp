// #include "../../headers/parsing.hpp"
#include "../../headers/webserv.hpp"

std::map<std::string, std::string> extract_key_value(std::string line, std::string delm)
{
  std::string key;
  std::string value;
  std::map<std::string, std::string> pair;
  size_t pos;
  size_t skip = 1;

  if (!delm.compare(": "))
    skip = 2;
  pos = line.find(delm);
  key = line.substr(0, pos);
  value = line.substr(pos + skip, line.length());
  pair.insert(std::pair<std::string, std::string>(key, value));
  return pair;
}
