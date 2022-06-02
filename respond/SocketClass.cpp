#include "SocketClass.hpp"
#include <iostream>

ft_socket::ft_socket(int domain, int type, int protocol, in_port_t port, in_addr_t ip)
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

void	ft_socket::accept_connections( void )
{
	if ((accept_fd = accept(sock_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen)) < 0)
	{
		std::cerr << "error: accept failed\n"; 
		exit(EXIT_FAILURE);        
	}
}