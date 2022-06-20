#include "../../maps/parsing.hpp"

std::map<std::string, std::string> utils::extract_key_value(std::string line, std::string delm)
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

std::string utils::get_file_name_by_time()
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


std::string utils::Response::find_in_map(const std::map<std::string, std::string> &map, const std::string &str)
{
    std::map<std::string, std::string>::const_iterator end = map.end();
    std::map<std::string, std::string>::const_iterator it = map.find(str);
    if (it != end)
        return std::string("");
    return it->second;
}

void utils::check_file(std::ifstream &fin)
{
    if (!fin.is_open())
    {
        std::cout << "Can't open file\n";
        exit(1);
    }
    if (fin.peek() == EOF)
    {
         std::cout << "Empty file\n";
        exit(1);
    }
}
// void check_file_data(Http http)
// {
//     // if (http.servers)
//     // {
        
//     // }
// }

void utils::syntax_error()
{
    std::cout << "Syntax Error!\n";
    exit(1);
}
void utils::check_file_syntax()
{
    Http http;
    Server server;
    Location location;

    if (http.http_count != 2 || server.server_count % 2 != 0 || location.location_count % 2 != 0)
        syntax_error();
}

void utils::check_map(std::pair<std::map<std::string, std::string>::iterator,bool> ret)
{
    if (ret.second==false)
        syntax_error();
}

std::string utils::skip_spaces(std::string str)
{
    int i = 0;
    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\t')
            str.erase(i, 1);
        i++;
    }

    return str;
}