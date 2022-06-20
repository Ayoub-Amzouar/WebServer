/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:13:59 by mel-hadj          #+#    #+#             */
/*   Updated: 2022/06/19 11:11:49 by mel-hadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_H
#define WEBSERV_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <string>
#include <sstream>
#include <sys/stat.h>
#include <dirent.h>
#include <algorithm>
#include <stdio.h>
#include <fcntl.h>
#include <poll.h>
#include <sstream>
#include <sys/time.h>


#include "parsing.hpp"
#include "SocketClass.hpp"

#include "cgi.hpp"
#include "utils.hpp"
#include "response.hpp"


#define RED "\033[1;31m"
#define RESET "\033[0m"




#endif