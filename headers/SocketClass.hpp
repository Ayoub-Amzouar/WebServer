#pragma once

#include "webserv.hpp"

class 	ft_socket
{
	int							sock_fd;
	struct sockaddr_in			server_addr;
	struct sockaddr_in			client_addr;
	socklen_t					addrlen;

public:
	ft_socket( void );
	ft_socket(in_port_t port, in_addr_t ip);
	ft_socket( const ft_socket& );
	ft_socket&	operator=( const ft_socket& );
	~ft_socket( void );

	int		accept_connections( void );
	
	int					getSockFd( void ) const;
	struct sockaddr_in	getServerAddr( void ) const;
	struct sockaddr_in	getClientAddr( void ) const;

};