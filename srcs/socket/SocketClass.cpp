#include "../../headers/webserv.hpp"
#include <fcntl.h>

ft_socket::ft_socket( void ) {}

ft_socket::ft_socket(in_port_t port, in_addr_t ip)
{
	sock_fd = socket(PF_INET, SOCK_STREAM, 0);
	int var = 1;

	if (fcntl(sock_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << "error: fcntl failed\n"; 
		exit(EXIT_FAILURE); 
	}

	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htons(ip);

	setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &var, sizeof(int));
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

ft_socket::ft_socket( const ft_socket& val )
{
	*this = val;
}

ft_socket&	ft_socket::operator=( const ft_socket& rop )
{

	sock_fd = rop.sock_fd;
	server_addr = rop.server_addr;
	client_addr = rop.client_addr;
	addrlen = rop.addrlen;

	return (*this);
}

ft_socket::~ft_socket( void )
{
	// close(sock_fd);
	// for (std::vector<struct pollfd>::iterator b = ufds.begin(); b != ufds.end(); b++)
	// 	close(b->fd);
}

int		ft_socket::accept_connections( void )
{
	return (accept(sock_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen));
}

// void		ft_socket::response( const std::string& val )
// {
// 		// send(ready_fd, val.c_str(), val.length(), 0);
// }

// std::string	ft_socket::request( void )
// {
// 	char		buffer[3000];

// 	bzero(buffer, 3000);
// 	std::string	res;
// 	size_t		i = 0;

// 	if (!ufds.empty()) {
// 		poll(&ufds[0], ufds.size(), -1);
// 		while (i < ufds.size()) {
// 			if (ufds[i].revents == POLLIN)
// 			{
// 				ready_fd = ufds[i].fd;
// 				int ret = recv(ready_fd, buffer, 3000, 0);
// 				if (ret == -1 || ret  == 0)
// 					return "";
// 				return (std::string(buffer, ret));
// 			}
// 			i++;
// 		}
// 	}
// 	return ("NON");
// }

int					ft_socket::getSockFd( void ) const { return (sock_fd); }

struct sockaddr_in	ft_socket::getServerAddr( void ) const { return (server_addr); }

struct sockaddr_in	ft_socket::getClientAddr( void ) const { return (client_addr); }