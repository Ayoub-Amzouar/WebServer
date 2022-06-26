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

std::string Utils::location(std::string redirection)
{
    return "Location: " + redirection;
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

std::string Utils::cut_uri(std::string uri)
{
    if (uri.empty())
        return std::string();
    size_t found = uri.find_last_of("/");
    if (found == std::string::npos)
        return std::string();
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

std::string Utils::status_code(int code)
{
    static const StatusCode s;
    std::string exist = s.get_message(code);
    if (!exist.empty())
    return exist;
    else
        return std::string();
}
std::string Utils::status_line(int code)
{
    std::string exist = Utils::status_code(code);
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

    res.r_perm = (fs.st_mode & S_IRUSR) ? true : false;
    res.w_perm = (fs.st_mode & S_IWUSR) ? true : false;
    res.x_perm = (fs.st_mode & S_IXUSR) ? true : false;

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
    in.close();
    return sstr.str();
}
std::string Utils::erasePathFromUri(std::string uri, std::string &location_path)
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

std::string		Utils::give_me_uri( const Location &location, const std::map<std::string, std::string> &request )
{
	std::string							path = Utils::find_in_map(location.attributes, "path");
	std::string							uri = Utils::find_in_map(request, "location");
	std::pair<std::string, std::string>	split_uri = Utils::parse_uri(uri);

	uri = Utils::erasePathFromUri(split_uri.first, path);

	return (Utils::find_in_map(location.attributes, "root") + '/' + uri);
}

std::string Utils::getFileExtension(std::string file_name)
{
    size_t found = file_name.find_last_of(".");
    if (found == std::string::npos)
        return std::string();
    file_name.erase(0, found + 1);
    return file_name;
}

void			Utils::send_response_message( int fd, std::string &response_message )
{
	size_t		len = response_message.length();
	size_t		send_ret;

	if ( (send_ret = send(fd, response_message.c_str(), len, 0)) != -1 )
	{
		response_message = response_message.substr(send_ret);
		len = response_message.length();
	}
}

bool			Utils::is_slash_at_end( std::string uri )
{
	if (uri[uri.size() - 1] == '/')
		return (true);
	return (false);
}

bool			Utils::is_location_has_cgi( Location location, std::string uri, bool type )
{
	if (type == FT_DIR)
	{
		if (!Utils::find_in_map(location.attributes, "cgi").empty())
		{
			if (!Utils::find_in_map(location.attributes, "cgi-ext").empty() && !Utils::find_in_map(location.attributes, "index").empty())
			{
				std::vector<std::string>	line_splitted = Utils::parse_line(Utils::find_in_map(location.attributes, "index"), ".");
				std::string 				index_ext = line_splitted[line_splitted.size() - 1];
				if (index_ext == Utils::find_in_map(location.attributes, "cgi-ext"))
					return (true);
			}
		}
	}
	else if (type == FT_FILE)
	{
		if (!Utils::find_in_map(location.attributes, "cgi").empty())
		{
			if (!Utils::find_in_map(location.attributes, "cgi-ext").empty())
			{
				std::vector<std::string>	line_splitted = Utils::parse_line(uri, "/");
				std::string 				file_ext = line_splitted[line_splitted.size() - 1];

				line_splitted = Utils::parse_line(uri, ".");
				file_ext = line_splitted[line_splitted.size() - 1];
				if (file_ext == Utils::find_in_map(location.attributes, "cgi-ext"))
					return (true);
			}
		}
	}
	return (false);
}

std::string		Utils::run_cgi(const Location &location, const std::map<std::string, std::string> &request, const std::string &body_file, std::string uri)
{
	std::map<std::string, std::string>	cgiMap;
	std::string							cgiName = Utils::find_in_map(location.attributes, "cgi");

	cgiMap["method"] = "GET";
	cgiMap["root"] = Utils::find_in_map(location.attributes, "root");
	cgiMap["Content-Type"] =  Utils::find_in_map(request, "content_type");
	cgiMap["Content-Length"] = Utils::find_in_map(request, "content_length");
	cgiMap["body_file"] = body_file;
	cgiMap["uri"] = uri;
	// TODO: try to find the passed args to cgi;
	Cgi php(cgiName);
	std::string cgi_res = php.run(cgiMap);

	return (cgi_res);
}