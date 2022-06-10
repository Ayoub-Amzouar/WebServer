#include "../../headers/webserv.hpp"
#include <fcntl.h>


ft_socket::ft_socket(in_port_t port, in_addr_t ip) : ready_fd()
{
	sock_fd = socket(PF_INET, SOCK_STREAM, 0);

	if (fcntl(sock_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << "error: fcntl failed\n"; 
		exit(EXIT_FAILURE); 
	}

	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htons(ip);

	if (bind(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		std::cerr << "error: bind failed\n"; 
		exit(EXIT_FAILURE); 
	}

	if (listen(sock_fd, 10) < 0)
	{
		std::cerr << "error: listen failed\n"; 
		exit(EXIT_FAILURE); 
	}
}

ft_socket::~ft_socket( void )
{
	close(sock_fd);
	for (std::vector<struct pollfd>::iterator b = ufds.begin(); b != ufds.end(); b++)
		close(b->fd);
}

void	ft_socket::accept_connections( void )
{
	int		accept_fd;

	accept_fd = accept(sock_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen);
	if (accept_fd != -1) {
		struct pollfd	ufd;

		ufd.fd = accept_fd;
		ufd.events = POLLIN;
		ufd.revents = 0;
		ufds.push_back(ufd);
	}
}

void		ft_socket::response( const std::string& val )
{
	if (ready_fd)
		send(ready_fd, val.c_str(), val.length(), 0);
}

std::string	ft_socket::request( void )
{
	char		buffer[300000];
	std::string	res;
	size_t		i = 0;

	if (!ufds.empty()) {
		poll(&ufds[0], ufds.size(), -1);
		while (i < ufds.size()) {
			if (ufds[i].revents == POLLIN)
			{
				ready_fd = ufds[i].fd;
				while (recv(ready_fd, buffer, 300000, 0) > 0)
				{
					std::cout << "hey\n";
					res += buffer;
				}
				return (res);
			}
			i++;
		}
	}
	return ("NON");
}

int					ft_socket::getSockFd( void ) const { return (sock_fd); }

struct sockaddr_in	ft_socket::getServerAddr( void ) const { return (server_addr); }

struct sockaddr_in	ft_socket::getClientAddr( void ) const { return (client_addr); }