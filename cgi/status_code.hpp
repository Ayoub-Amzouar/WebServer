#ifndef _STATUS_HPP_
#define _STATUS_HPP_


class StatusCode
{
    std::map<int, std::string> _code;

public:
    StatusCode();
    std::string get_message(int code) const;
};

#endif