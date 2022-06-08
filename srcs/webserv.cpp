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
        Request request;
        std::cout << http.servers[0].locations[0].attributes["path"] << std::endl;
        ft_socket sock(std::stoi(http.servers[0].attributes["listen"]), INADDR_ANY);

        while (1)
        {
            sock.accept_connections();
            std::cout << RESET << "\n######## connection established ########" << RESET << std::endl;
            request.parse_request(sock.request());
            sock.response("");
        }
    }
    else
    {
        std::cout << "No file found : ./webserv [configfile]\n";
        return 1;
    }
    return 0;
}