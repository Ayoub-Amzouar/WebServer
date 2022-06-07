/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:13:03 by mel-hadj          #+#    #+#             */
/*   Updated: 2022/06/07 15:33:15 by mel-hadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/webserv.hpp"
using namespace std;

std::string skip_spaces(std::string str)
{
    int i = 0;
    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\t')
            str.erase(i, 1);
        i++;
    }

    return str;
}

void add_location_attributes(Location &location, std::string line)
{
    std::map<std::string, std::string> pair;
    pair = extract_key_value(line);
    check_map(location.attributes.insert(std::pair<std::string, std::string>(pair.begin()->first, pair.begin()->second)));
}

void add_server_attributes(Server &server, std::string line,  std::ifstream &fin)
{
    Location location;
    std::map<std::string, std::string> pair;
     
    if (!line.compare("<location>"))
    {
        location.location_count++;
        while (getline(fin, line))
        {
            line = skip_spaces(line);
            if (line[0] == '#' || line.empty())
                continue;
            if (!line.compare("<location>"))
            {
                location.location_count++;
                break;
            }
            add_location_attributes(location, line);
        }
        if (!fin)
            syntax_error();
        server.locations.push_back(location);
    }
    else
    {
        pair = extract_key_value(line);
        // std::cout << "|" << pair.begin()->first << "|" << std::endl;
        check_map(server.attributes.insert(std::pair<std::string, std::string>(pair.begin()->first, pair.begin()->second)));
       
    }
        
     
}

void add_http_attributes(Http &http, std::string line, std::ifstream &fin)
{
    Server server;
    std::map<std::string, std::string> pair;
    
    if (!line.compare("<server>"))
    {
        server.server_count++;
        while (getline(fin, line))
        {
            line = skip_spaces(line);
             if (line[0] == '#' || line.empty())
                continue;
            if (!line.compare("<server>"))
            {
                server.server_count++;
                break;
            }
            add_server_attributes(server, line, fin);
        }
        if (!fin)
            syntax_error();
        http.servers.push_back(server);
    }
    else
    {
        pair = extract_key_value(line);
       check_map(http.attributes.insert(std::pair<std::string, std::string>(pair.begin()->first, pair.begin()->second)));
    }
}

Http parsing(char *str)
{
    string line;
    ifstream fin;
    Http http;
    
    fin.open(str);
    check_file(fin);
    while (fin)
    {
        getline(fin, line);
        line = skip_spaces(line);
        if (line[0] == '#' || line.empty())
            continue;
        if (!line.compare("<HTTP>") || http.http_count)
        {
            if (!line.compare("<HTTP>"))
                http.http_count++;
            else
                add_http_attributes(http, line, fin);
        }
        else
        {
            std::cout << "Syntax Error!\n";
            exit(1);
        }
    }
    fin.close();
    check_file_syntax();
    return http;
}
