/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:13:59 by mel-hadj          #+#    #+#             */
/*   Updated: 2022/06/19 17:22:50 by mel-hadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef WEBSERV_H
// #define WEBSERV_H

#pragma once
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/time.h>
#include <dirent.h>
#include <algorithm>
#include <fcntl.h>
#include <sstream>
#include <arpa/inet.h>
#include <iterator>
#include <sys/types.h>
#include <sys/wait.h>



#include "SocketClass.hpp"
#include "cgi.hpp"
#include "parsing.hpp"
#include "utils.hpp"
#include "response.hpp"


#define RED "\033[1;31m"
#define RESET "\033[0m"




// #endif