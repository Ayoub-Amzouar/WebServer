// #include "../../headers/parsing.hpp"
#include "../../headers/webserv.hpp"

void check_file(std::ifstream &fin)
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

void syntax_error()
{
    std::cout << "Syntax Error!\n";
    exit(1);
}
void check_file_syntax()
{
    Http http;
    Server server;
    Location location;

    if (http.http_count != 2 || server.server_count % 2 != 0 || location.location_count % 2 != 0)
        syntax_error();
}

void check_map(std::pair<std::map<std::string, std::string>::iterator,bool> ret)
{
    if (ret.second==false)
        syntax_error();
}