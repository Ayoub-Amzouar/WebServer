#include "SocketClass.hpp"
#include <iostream>
#include "../cgi/cgi.hpp"
#include "../cgi/utils.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>

#define RED "\033[1;31m"
#define RESET "\033[0m"

bool DoesFileExist (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

int		main(int ac, char *av[], char *env[])
{
	ft_socket	sock(8080, INADDR_ANY);
	(void)ac;
	(void)av;

	while (1)
	{
		std::string paths(getenv("PATH"));
		sock.accept_connections();
		std::cout << RED << "\n######## connection has occurred ########" << RESET << std::endl;;

		std::string cgiName("php-cgi");
		Cgi cgi(cgiName, env);

		std::string request = sock.request();
		
		std::stringstream ss(request);
		std::string to;
		std::getline(ss, to, '\n');

		std::string del(" ");
		std::vector<std::string> firstLine = parse_line(to,del); 
		std::string response;
		if (firstLine[0] == "GET")
			response = cgi.GET(firstLine[1], 1234, "/goinfre/ynoam/wordpress");
		else if (firstLine[0] == "POST")
			response = cgi.POST(firstLine[1], 1234, "", "/goinfre/ynoam/wordpress");
		else
			std::cout << "METHOD NOT SEPORTED" << std::endl;

		sock.response(response);
	}
	return (0);
}