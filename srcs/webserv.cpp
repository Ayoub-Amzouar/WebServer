#include "../headers/webserv.hpp"
// initializing static member values

int Http::http_count = 0;
int Server::server_count = 0;
int Location::location_count = 0;

int main(int argc, char **argv)
{
    if (argc > 1)
    { 
        Http http = parsing(argv[1]);
        std::cout << http.servers[0].locations[0].attributes["path"] << std::endl;
        // Server server;
        // Location location;
        // std::cout << location.location_count << std::endl;
        // std::cout << server.server_count << std::endl;
 
    }
    else
    {
        std::cout << "No file found : ./webserv [configfile]\n";
        return 1;
    }
    return 0;
}