#pragma once

#include "webserv.hpp"


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
    ErrorPage(std::string);
    std::string get_page(int code) const;
};

// class DefaultErrPage
// {
//     std::map<int, std::string> _code;
// public:
//     DefaultErrPage();
//     std::string get_body(int code) const;
// };

#define FT_FILE 0
#define FT_DIR  1

struct file_stats
{
    bool		w_perm;
    bool		r_perm;
    bool		x_perm;
    bool		exist;
    bool		type;

    file_stats () : w_perm(), r_perm(), x_perm() ,exist(), type() {}
};

class Utils
{

public:
    Utils();
    ~Utils();
    void static check_file(std::ifstream &fin);
    void static syntax_error(void);
    void static check_file_syntax(void);
    std::map<std::string, std::string> static extract_key_value(std::string line, std::string delm);
    void static check_map(std::pair<std::map<std::string, std::string>::iterator, bool> ret);
    std::string static find_in_map(const std::map<std::string, std::string> &map, const std::string &str);
    std::string static get_file_name_by_time(void);
    std::string static skip_spaces(std::string str);
    std::string static erasePathFromUri(std::string uri, std::string &location_path);
    std::pair<std::string, std::string> static parse_uri(std::string uri);
    std::string static content_length(size_t size);
    std::string static location(std::string &);
    std::string static cut_uri(std::string uri);
    std::vector<std::string> static parse_line(std::string str, std::string delim);
    bool static doesFileExist(const std::string &name);
    std::string static status_line(int code);
    std::string static content_type(std::string exten);
    std::string static status_code(int code);
    // @@@ ERROR PAGES
    std::string static defaultErrPage(int code);
    std::string static fileToStr(std::string &fileName);
    // @@@@ FILE PERMISSION
    file_stats	static get_file_stats ( std::string filename );
	std::string	static give_me_uri( const Location &location, const std::map<std::string, std::string> &request );
};

// std::string status_line(int code);
// std::string content_type(std::string exten);
// std::string content_length(size_t);
// std::string error_page(int code);
// std::string erasePathFromUri(std::string &uri, std::string &location_path);

// bool doesFileExist (const std::string&);
// std::vector<std::string> parse_line(std::string str, std::string delim);
// std::pair<std::string, std::string> parse_uri(std::string uri);
// std::string cut_uri(std::string uri);
// std::string defaultErrPage(int code);
// std::string fileToStr(std::string &);
// file_stats get_file_stats(std::string filename);
