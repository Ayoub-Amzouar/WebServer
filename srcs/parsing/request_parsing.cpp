/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_parsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:54:28 by mel-hadj          #+#    #+#             */
/*   Updated: 2022/06/14 20:10:23 by mel-hadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/webserv.hpp"

void parse_request_line(std::map<std::string, std::string> &pair, std::string line)
{
    std::map<std::string, std::string> tmp;
    std::string value1;
    std::string value2;
    size_t pos;

    tmp = extract_key_value(line, " ");
    value1 = tmp.begin()->first;
    pos = tmp.begin()->second.find(" ");
    value2 = tmp.begin()->second.substr(0, pos);
    pair.insert(std::pair<std::string, std::string>("method", value1));
    pair.insert(std::pair<std::string, std::string>("location", value2));
}

void parse_request_body(std::map<std::string, std::string> pair, std::string line, std::stringstream &ss)
{
    // std::string line;
    // if (!pair["Transfer-Encoding"].compare("chunked"))
    // {
    // }
    // else
    // {
    //     while (getline(ss, line))
    //     {
    //     }
    // }
}

void Request::parse_request(std::string str, Request_Data &request)
{
    std::stringstream ss(str);
    std::map<std::string, std::string> tmp;
    std::map<std::string, std::string> pair;
    std::string line;
    bool entered = true;
    while (getline(ss, line))
    {
        if (entered)
        {
            parse_request_line(pair, line);
            entered = false;
        }
        else
        {
            if (line.find('\r') == 0)
            {
                continue;
            }
            line.erase(line.length() - 1);
            tmp = extract_key_value(line, ": ");
            pair.insert(std::pair<std::string, std::string>(tmp.begin()->first, tmp.begin()->second));
        }
    }
       std::cout << "******************************************************************************" << std::endl;

        for (std::map<std::string, std::string>::iterator it = pair.begin(); it != pair.end(); it++)
        {
            std::cout << it->first << "=" << it->second << std::endl;
        }

        std::cout << "******************************************************************************" << std::endl;

    request.attributes = pair;
}

void	Request::get_request( int accept_fd )
{
	Request_Data	req;
	char			buffer[3000];
	std::string		res;
	int				ready_fd;

	if (accept_fd > 0)
	{
		struct pollfd	ufd;

		ufd.fd = accept_fd;
		ufd.events = POLLIN;
		ufd.revents = 0;
		ufds.push_back(ufd);
	}

	if (!ufds.empty()) {

		bzero(buffer, 3000);
		poll(&ufds[0], ufds.size(), -1);

		for (size_t i = 0; i < ufds.size(); i++) {
			if (ufds[i].revents == POLLIN)
			{
				ready_fd = ufds[i].fd;
				int ret = recv(ready_fd, buffer, 3000, 0);
				if (ret > 0)
				{
					if (!request_table.count(ready_fd))
					{
						request_table.insert(std::make_pair(ready_fd, req));
						parse_request(buffer, request_table[ready_fd]);
					} else if (!request_table[ready_fd].is_finished)
						parse_request(buffer, request_table[ready_fd]);
					else {
						// response(request_table[ready_fd]);
					}
				}
			}
			i++;
		}
	}
}