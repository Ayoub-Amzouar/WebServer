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
        ft_socket sock(std::stoi(http.servers[0].attributes["listen"]), INADDR_ANY);
		std::string req;

        while (1)
        {
            sock.accept_connections();
            // std::cout << RED << "\n######## connection has occurred ########" << RESET << std::endl;

            // std::cout << sock.request() << std::endl;
			req = sock.request();
			if (req != "NON")
			{
				std::cerr << req;
				// sock.response("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");
				// break ;
			}
			req.clear();
		}
    }
    else
	{
		std::cout << "No file found : ./webserv [configfile]\n";
 		return 1;
    }
    return 0;
}