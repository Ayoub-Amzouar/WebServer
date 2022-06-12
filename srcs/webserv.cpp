#include "../headers/webserv.hpp"
// initializing static member values

int Http::http_count = 0;
int Server::server_count = 0;
int Location::location_count = 0;

int main(int argc, char **argv, char **env)
{
    if (argc > 1)
    {
        Http http = parsing(argv[1]);
        // std::cout << http.servers[0].locations[1].attributes["method2"] << std::endl;
        // std::cout << http.servers[0].locations[0].attributes["path"] << std::endl;
        ft_socket sock(std::stoi(http.servers[0].attributes["listen"]), INADDR_ANY);

        Response response(http, env);
        while (1)
        {
            sock.accept_connections();
            std::cout << RED << "\n######## connection has occurred ########" << RESET << std::endl;

            std::cout << sock.request() << std::endl;
            // response.run(;
            // sock.response("");
        }
    }
    else
    {
        std::cout << "No file found : ./webserv [configfile]\n";
        return 1;
    }
    return 0;
}