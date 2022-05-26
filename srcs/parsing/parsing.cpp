/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:13:03 by mel-hadj          #+#    #+#             */
/*   Updated: 2022/05/26 20:38:04 by mel-hadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/webserv.hpp"
using namespace std;

Http  parsing(char *str)
{
   
    string line;
    ifstream fin;
    fin.open(str);
    Http http;
    vector<Server> server_vec;
    vector<Location> location_vec;
    
    // check if the file opend successfully
    if (!fin.is_open())
    {
        cout << "Can't open file\n";
        exit(1);
    }
    if (!fin.peek())
    {
         cout << "Empty file\n";
        exit(1);
    }
    while (fin) {
        // Read a Line from File
        getline(fin, line);
        if (line.compare("#"))
            continue;
        cout << line << endl;
    }
 
    // Close the file
    fin.close();
 
return http;
}