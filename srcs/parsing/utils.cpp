#include "../../headers/parsing.hpp"

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

std::string get_file_name_by_time()
{
    struct timeval time_now;
    std::stringstream stream;  
    std::string time;

    gettimeofday(&time_now, nullptr);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    stream<<msecs_time;
    time = stream.str();
    time = "/tmp/" + time;
    return time;
}