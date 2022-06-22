/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:14:09 by mel-hadj          #+#    #+#             */
/*   Updated: 2022/06/19 11:53:47 by mel-hadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include "webserv.hpp"

class Location
{
    public :
        static int location_count;
        std::map<std::string, std::string> attributes;
};

class Server
{
    public :
        static int server_count;    
        std::vector<Location> locations;
        std::map<std::string, std::string> attributes;
};

class  Http
{
    public :
        static int http_count;    
        std::vector<Server> servers;
        std::map<std::string, std::string> attributes;
};

class Request_Data
{
public:
	std::map<std::string, std::string>	attributes;
	std::string							file_name;
	std::string							response;
	bool								is_finished;
	bool								is_error;
};

struct Response;

class Request
{
		std::map<int, Request_Data>	request_table;
		std::vector<struct pollfd>	ufds;
    public :
        Request (void);
        void	 parse_request(std::string str, Request_Data &request);
        void     get_request(int accept_fd, Response& response);
        int      check_req_validity(const std::map<std::string, std::string> &request);

};


Http  parsing(char *str);
// void check_file(std::ifstream &fin);
// void syntax_error();
// void check_file_syntax();
// std::map<std::string, std::string> extract_key_value(std::string line, std::string delm);
// void check_map(std::pair<std::map<std::string, std::string>::iterator,bool> ret);
// std::string get_file_name_by_time();


