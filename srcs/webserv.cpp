#include "../headers/webserv.hpp"
// initializing static member values

int Http::http_count = 0;
int Server::server_count = 0;
int Location::location_count = 0;

int main(int argc, char **argv, char **env)
{
    if (argc > 1)
    {
        Http http = parsing(argv[1]);
		Request		req;
        // std::cout << http.servers[0].locations[0].attributes["path"] << std::endl;
        ft_socket	*sock = new ft_socket[http.servers.size()];
		int			index = 0;

		for (size_t i = 0; i < http.servers.size(); i++)
			sock[i] = ft_socket(std::stoi(http.servers[i].attributes["listen"]), http.servers[i].attributes); // change stoi it's c++ feature

        Response response(http);
        while (1)
        {
			req.get_request(sock[index].accept_connections(), response);

            // response.run(;
			// request = request(sock[index]);
			// if (request != "NON")
			// {
			// 	sock.response("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\n" + request);
			// 	break ;
			// }
			// request.clear();

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