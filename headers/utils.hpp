#pragma once

#include "webserv.hpp"

std::string status_line(int code);
std::string content_type(std::string exten);
bool doesFileExist (const std::string&);
std::vector<std::string> parse_line(std::string str, std::string delim);
std::pair<std::string, std::string> parse_uri(std::string uri);
std::string cut_uri(std::string uri);

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
class ErrorPage
{
    std::map<int, std::string> _code;
public:
    ErrorPage(std::string &);
    std::string get_page(int code) const;
};
#define FT_FILE 0
#define FT_DIR  1

struct file_stats
{
    short        perm;
    bool        exist;
    short        type;
};

class Utils
{

public:
    Utils();
    ~Utils();
    void static check_file(std::ifstream &fin);
    void static syntax_error();
    void static check_file_syntax();
    std::map<std::string, std::string> static extract_key_value(std::string line, std::string delm);
    void static check_map(std::pair<std::map<std::string, std::string>::iterator, bool> ret);
    std::string find_in_map(const std::map<std::string, std::string> &map, const std::string &str);
    std::string static get_file_name_by_time();
    std::string static skip_spaces(std::string str);
};



