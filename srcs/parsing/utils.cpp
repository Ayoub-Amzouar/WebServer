#include "../../headers/webserv.hpp"

std::map<std::string, std::string> Utils::extract_key_value(std::string line, std::string delm)
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


std::pair<std::string, std::string> Utils::parse_uri(std::string uri)
{
    int pos;
    pos = uri.find("?");
    if (pos == -1)
        return make_pair(uri, std::string(""));
    return make_pair(uri.substr(0, pos), uri.substr(pos + 1));
}

std::string Utils::content_length(size_t size)
{
    std::string c("Content-Length: ");
    return c + std::to_string(size);
}

    std::string  Utils::cut_uri(std::string uri)
{
    if (uri.empty())
        return std::string("");
    size_t found = uri.find_last_of("/");
    if (found == std::string::npos)
        return std::string("");
    if (uri[found] == *(uri.end() - 1))
        uri.erase(found, 1);
    else
        uri.erase(found + 1, uri.length() - 1);
    return uri;
}


std::vector<std::string>  Utils::parse_line(std::string str, std::string delim)
{
    std::vector<std::string> strings;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delim)) != std::string::npos)
    {
        if (pos != 0)
        {
            token = str.substr(0, pos);
            strings.push_back(token);
        }
        str.erase(0, pos + delim.length());
    }
    if(!str.empty())
        strings.push_back(str);
    return strings;
}

bool Utils::doesFileExist(const std::string &name)
{
    std::ifstream f(name.c_str());
    return f.good();
}

std::string Utils::status_line(int code)
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

std::string Utils::content_type(std::string exten)
{
    static const ContentType s;
    std::string exist = s.get_mime(exten);
    if (!exist.empty())
    {
        std::string cntnt_type("Content-Type: ");
        cntnt_type.append(exist);
        return cntnt_type;
    }
    else
        return std::string();
}


std::string Utils::defaultErrPage(int code)
{
    static const StatusCode s;
    std::string exist = s.get_message(code);
    if (!exist.empty())
    {
        std::string status;
        status.append(std::to_string(code));
        status.append(" ");
        status.append(exist);
        return "<html><head><title>" + status + "</title></head><body><center><h1>" + status + "</h1></center><hr><center>WebServ</center></body></html>";
    }
    else
        return std::string();
}

file_stats     Utils::get_file_stats ( std::string filename )
{
    struct stat        fs;
    int                r;
    file_stats        res;

    if (stat(filename.c_str(), &fs) < 0)
        return (res);

    res.exist = 1;

    res.perm = (fs.st_mode & S_IRUSR) ? 4 : 0;
    res.perm += (fs.st_mode & S_IWUSR) ? 2 : 0;
    res.perm += (fs.st_mode & S_IXUSR) ? 1 : 0;

    if (S_ISDIR(fs.st_mode))
        res.type = FT_DIR;
    else if (S_ISREG(fs.st_mode))
        res.type = FT_FILE;

    return (res);
}


std::string Utils::fileToStr(std::string &fileName)
{
    std::ifstream   in;

    in.open(fileName);
    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}
std::string Utils::erasePathFromUri(std::string &uri, std::string &location_path)
{
    uri.erase(0, location_path.length());
    return uri;
}

std::string Utils::get_file_name_by_time()
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


std::string Utils::find_in_map(const std::map<std::string, std::string> &map, const std::string &str)
{
    std::map<std::string, std::string>::const_iterator end = map.end();
    std::map<std::string, std::string>::const_iterator it = map.find(str);
    if (it == end)
        return std::string("");
    return it->second;
}

void Utils::check_file(std::ifstream &fin)
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

void Utils::syntax_error()
{
    std::cout << "Syntax Error!\n";
    exit(1);
}
void Utils::check_file_syntax()
{
    Http http;
    Server server;
    Location location;

    if (http.http_count != 2 || server.server_count % 2 != 0 || location.location_count % 2 != 0)
        syntax_error();
}

void Utils::check_map(std::pair<std::map<std::string, std::string>::iterator,bool> ret)
{
    if (ret.second==false)
        syntax_error();
}

std::string Utils::skip_spaces(std::string str)
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