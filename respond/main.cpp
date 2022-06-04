#include "SocketClass.hpp"
#include <iostream>

#define RED "\033[1;31m"
#define RESET "\033[0m"

int		main(void)
{
	ft_socket	sock(4444, INADDR_ANY);

	while (1)
	{
		sock.accept_connections();
		std::cout << RED << "\n######## connection has occurred ########" << RESET << std::endl;;

		std::cout << sock.request() << std::endl;
		sock.response("");
	}
	return (0);
}