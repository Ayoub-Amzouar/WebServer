#include "SocketClass.hpp"
#include <iostream>
#include <unistd.h>

ft_socket::ft_socket(int domain, int type, int protocol, in_port_t port, in_addr_t ip) : accept_fd()
{
	sock_fd = socket(domain, type, protocol);

	server_addr.sin_family = domain;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = ip;

	if (bind(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		std::cerr << "error: bind failed\n"; 
		return ;
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
	if (accept_fd != 0)
		close(accept_fd);
}

void	ft_socket::accept_connections( void )
{
	if (accept_fd != 0)
		close(accept_fd);
	if ((accept_fd = accept(sock_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen)) < 0)
	{
		std::cerr << "error: accept failed\n"; 
		exit(EXIT_FAILURE);        
	}
}

int					ft_socket::getSockFd( void ) const { return (sock_fd); }

int					ft_socket::getAcceptFd( void ) const { return (accept_fd); }

struct sockaddr_in	ft_socket::getServerAddr( void ) const { return (server_addr); }

struct sockaddr_in	ft_socket::getClientAddr( void ) const { return (client_addr); }