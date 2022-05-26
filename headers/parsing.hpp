/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:14:09 by mel-hadj          #+#    #+#             */
/*   Updated: 2022/05/26 20:36:57 by mel-hadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "webserv.hpp"


class Location
{
    std::map<std::string, std::string> attributes;
};

class Server
{
    std::vector<Location> locations;
    // std::string listen;
    // std::string sever_name;
    std::map<std::string, std::string> attributes;
};

class  Http{
    
    std::vector<Server> servers;
    std::string error_pages;
};


Http  parsing(char *str);
#endif