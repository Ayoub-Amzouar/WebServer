#pragma once

#include "webserv.hpp"

/*
	1) write both send and receive functions
	2) make a structure for content-types
	3) maybe constructor parameters can have a default value instead of always specify them
*/

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
	
	void		response( const std::string& );
	std::string request( void );

	int					getSockFd( void ) const;
	struct sockaddr_in	getServerAddr( void ) const;
	struct sockaddr_in	getClientAddr( void ) const;

};