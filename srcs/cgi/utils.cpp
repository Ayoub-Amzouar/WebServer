#include "status_code.hpp"
#include <string>

std::string status_line(int code)
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