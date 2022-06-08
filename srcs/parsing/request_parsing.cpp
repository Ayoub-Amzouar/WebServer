/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_parsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:54:28 by mel-hadj          #+#    #+#             */
/*   Updated: 2022/06/08 13:02:40 by mel-hadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/webserv.hpp"

std::map<std::string, std::string> Request::parse_request(std::string str)
{
    std::stringstream ss(str);
    std::map<std::string, std::string> pair;
    std::string line;
    pair = extract_key_value(str, ": ");
    while (getline(ss, line))
    {
       line.erase(line.length() - 1);
       std::cout << line << std::endl;
       pair = extract_key_value(line, ": ");
       std::cout << pair.begin()->first << "  " << pair.begin()->second << std::endl;
    }
    
    // std::cout << pair.begin()->first << "  " << pair.begin()->second << std::endl;
 

    return pair;
}
