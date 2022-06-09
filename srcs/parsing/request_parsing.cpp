/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_parsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:54:28 by mel-hadj          #+#    #+#             */
/*   Updated: 2022/06/09 15:52:08 by mel-hadj         ###   ########.fr       */
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
    std::string line;
    if (!pair["transfer-encoding"].compare("chunked"))
    {
    }
    else
    {
        while (getline(ss, line))
        {
        }
    }
}

std::map<std::string, std::string> Request::parse_request(std::string str)
{
    std::stringstream ss(str);
    std::map<std::string, std::string> tmp;
    std::map<std::string, std::string> pair;
    std::string line;
    bool entered = true;
    // pair = extract_key_value(str, ": ");
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
    //    std::cout << "******************************************************************************" << std::endl;

    //     for (std::map<std::string, std::string>::iterator it = pair.begin(); it != pair.end(); it++)
    //     {
    //         std::cout << it->first << "=" << it->second << std::endl;
    //     }

    //     std::cout << "******************************************************************************" << std::endl;

    return pair;
}
