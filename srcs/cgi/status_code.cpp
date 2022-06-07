#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <map>
#include "status_code.hpp"

StatusCode::StatusCode()
{
    _code[100] = "Continue";
    _code[101] = "Switching Protocols";
    _code[200] = "OK";
    _code[201] = "Created";
    _code[202] = "Accepted";
    _code[203] = "Non-Authoritative Information";
    _code[204] = "No Content";
    _code[205] = "Reset Content";
    _code[206] = "Partial Content";
    _code[300] = "Multiple Choices";
    _code[301] = "Moved Permanently";
    _code[302] = "Found";
    _code[303] = "See Other";
    _code[304] = "Not Modified";
    _code[305] = "Use Proxy";
    _code[307] = "Temporary Redirect";
    _code[400] = "Bad Request";
    _code[401] = "Unauthorized";
    _code[402] = "Payment Required";
    _code[403] = "Forbidden";
    _code[404] = "Not Found";
    _code[405] = "Method Not Allowed";
    _code[406] = "Not Acceptable";
    _code[407] = "Proxy Authentication Required";
    _code[408] = "Request Time-out";
    _code[409] = "Conflict";
    _code[410] = "Gone";
    _code[411] = "Length Required";
    _code[412] = "Precondition Failed";
    _code[413] = "Request Entity Too Large";
    _code[414] = "Request-URI Too Large";
    _code[415] = "Unsupported Media Type";
    _code[416] = "Requested range not satisfiable";
    _code[417] = "Expectation Failed";
    _code[500] = "Internal Server Error";
    _code[501] = "Not Implemented";
    _code[502] = "Bad Gateway";
    _code[503] = "Service Unavailable";
    _code[504] = "Gateway Time-out";
    _code[505] = "HTTP Version not supported";
}

std::string StatusCode::get_message(int code) const
{
    std::map<int, std::string>::const_iterator end = _code.end();
    std::map<int, std::string>::const_iterator exist;
    exist = _code.find(code);
    if (exist != end)
        return exist->second;
    else
        return std::string();
}
