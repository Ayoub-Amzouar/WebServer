#include "SocketClass.hpp"
#include <iostream>

ft_socket::ft_socket(int domain, int type, int protocol, in_port_t port, in_addr_t ip)
{
	sock_fd = socket(domain, type, protocol);

	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = ip;

	if (bind(sock_fd, (const struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "error:  bind failed\n"; 
		return ;
	}
}