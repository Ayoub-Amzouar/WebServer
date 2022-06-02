#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

class 	ft_socket
{
	int					sock_fd;
	struct sockaddr_in	address;
public:
	ft_socket(int domain, int type, int protocol, in_port_t port, in_addr_t ip);
};