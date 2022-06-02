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

	ft_socket( void );
	ft_socket( const ft_socket& );
	ft_socket&	operator=( const ft_socket& );
public:
	ft_socket(int domain, int type, int protocol, in_port_t port, in_addr_t ip);
	~ft_socket( void );

	void	accept_connections( void );

	int					getSockFd( void ) const;
	int					getAcceptFd( void ) const;
	struct sockaddr_in	getServerAddr( void ) const;
	struct sockaddr_in	getClientAddr( void ) const;

};