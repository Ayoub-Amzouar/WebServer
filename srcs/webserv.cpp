#include "../headers/webserv.hpp"
// initializing static member values

int Http::http_count = 0;
int Server::server_count = 0;
int Location::location_count = 0;

void	get_request( int accept_fd )
{
	static std::vector<struct pollfd>	ufds;
	char								buffer[3000];
	std::string							res;
	int									ready_fd;

	if (accept_fd > 0)
	{
		struct pollfd	ufd;

		ufd.fd = accept_fd;
		ufd.events = POLLIN;
		ufd.revents = 0;
		ufds.push_back(ufd);
	}

	if (!ufds.empty()) {

		bzero(buffer, 3000);
		poll(&ufds[0], ufds.size(), -1);

		for (size_t i = 0; i < ufds.size(); i++) {
			if (ufds[i].revents == POLLIN)
			{
				ready_fd = ufds[i].fd;
				int ret = recv(ready_fd, buffer, 3000, 0);
				if (ret != -1 || ret  != 0) {}
					// fill in the request
			}
			i++;
		}
	}
}

int		main(int argc, char **argv)
{
    if (argc > 1)
    {
        Http http = parsing(argv[1]);
        // std::cout << http.servers[0].locations[0].attributes["path"] << std::endl;
        ft_socket	*sock = new ft_socket[http.servers.size()];
		int			index = 0;

		for (int i = 0; i < http.servers.size(); i++)
			sock[i] = ft_socket(std::stoi(http.servers[0].attributes["listen"]), INADDR_ANY);

        while (1)
        {
			get_request(sock[index].accept_connections());
            // std::cout << RED << "\n######## connection has occurred ########" << RESET << std::endl;

			// request = request(sock[index]);
			// if (request != "NON")
			// {
			// 	std::cerr << request;
			// 	sock.response("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\n" + request);
			// 	break ;
			// }
			// request.clear();

			index = (index + 1) % http.servers.size();
		}
    }
    else
	{
		std::cout << "No file found : ./webserv [configfile]\n";
 		return 1;
    }
    return 0;
}