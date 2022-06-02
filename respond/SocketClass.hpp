#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

/*
	1) make accept independent function
	2) write getters for your private attributes
	3) write both send and receive functions
*/

class 	ft_socket
{
	int					sock_fd;
	int					accept_fd;
	struct sockaddr_in	server_addr;
	struct sockaddr_in	client_addr;
	socklen_t			addrlen;
public:
	ft_socket(int domain, int type, int protocol, in_port_t port, in_addr_t ip);

	void	accept_connections( void );
};