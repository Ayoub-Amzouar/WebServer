#include "../../headers/webserv.hpp"
#include <fcntl.h>


ft_socket::ft_socket(in_port_t port, in_addr_t ip) : accept_fd()
{
	sock_fd = socket(PF_INET, SOCK_STREAM, 0);

	if (fcntl(sock_fd, F_GETFL, O_NONBLOCK) < 0)
	{
		std::cerr << "error: fcntl failed\n"; 
		return ;
	}

	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htons(ip);

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

void		ft_socket::response( const std::string& val )
{
	send(accept_fd, val.c_str(), val.length(), 0);
}

std::string	ft_socket::request( void )
{
	char		buffer[30000];
	std::string	res;

	/*ssize_t recv_val = */recv(accept_fd, buffer, 30000, 0);
	res = buffer;

	return (res);
}

int					ft_socket::getSockFd( void ) const { return (sock_fd); }

int					ft_socket::getAcceptFd( void ) const { return (accept_fd); }

struct sockaddr_in	ft_socket::getServerAddr( void ) const { return (server_addr); }

struct sockaddr_in	ft_socket::getClientAddr( void ) const { return (client_addr); }