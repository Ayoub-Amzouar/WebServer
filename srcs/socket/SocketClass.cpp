#include "../../headers/webserv.hpp"

ft_socket::ft_socket( void ) {}

std::string ft_socket::get_host_ip(std::map<std::string, std::string> server)
{
	std::string host;
	
	host = Utils::find_in_map(server, "host");
	host = host.empty() ? "127.0.0.1" : host;
	return (host);
}

ft_socket::ft_socket(in_port_t port, std::map<std::string, std::string> server)
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
	if (inet_pton(PF_INET, get_host_ip(server).c_str(), &server_addr.sin_addr.s_addr) <= 0)
	{
		std::cerr << "error: inet_pton failed\n"; 
		exit(EXIT_FAILURE); 
    }

	setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &var, sizeof(int));
	if (bind(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		std::cerr << "error: bind failed\n"; 
		exit(EXIT_FAILURE); 
	}

	if (listen(sock_fd, 1024) < 0)
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

int					ft_socket::getSockFd( void ) const { return (sock_fd); }

struct sockaddr_in	ft_socket::getServerAddr( void ) const { return (server_addr); }

struct sockaddr_in	ft_socket::getClientAddr( void ) const { return (client_addr); }