#include "../headers/webserv.hpp"

int Http::http_count = 0;
int Server::server_count = 0;
int Location::location_count = 0;

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        Http http = parsing(argv[1]);
		Request		req;
        ft_socket	*sock = new ft_socket[http.servers.size()];
		int			index = 0;

		for (size_t i = 0; i < http.servers.size(); i++)
			sock[i] = ft_socket(std::stoi(http.servers[i].attributes["listen"]), http.servers[i].attributes);

        Response response(http);
        while (1)
        {
			req.get_request(sock[index].accept_connections(), response);
			index = (index + 1) % http.servers.size();
		}
    }
    else
	{
		std::cout << "No file found : ./webserv [configfile]\n";
 		return 1;
    }
    return 0;
}