# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/04 13:00:30 by mel-hadj          #+#    #+#              #
#    Updated: 2022/06/19 17:23:19 by mel-hadj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv
CC = c++ -std=c++98
# FLAGS = -Wall -Wextra -Werror
RM = rm -rf

DIR_SRCS = ./srcs/

HEADERS = ./headers/webserv.hpp
# <<<<<<< HEAD
# <<<<<<< HEAD
# SRC = parsing/parsing.cpp webserv.cpp parsing/check_errors.cpp  parsing/utils.cpp cgi/cgi.cpp cgi/status_code.cpp \
# 		cgi/utils.cpp socket/socket.cpp response/response.cpp
# =======
SRC = parsing/request_parsing.cpp parsing/file_parsing.cpp webserv.cpp  parsing/utils.cpp socket/SocketClass.cpp response/response.cpp cgi/utils.cpp cgi/cgi.cpp
# >>>>>>> origin/mohamed/parsing
# =======
# SRC = parsing/parsing.cpp webserv.cpp parsing/check_errors.cpp  parsing/utils.cpp cgi/cgi.cpp cgi/status_code.cpp \
# 		cgi/utils.cpp socket/socket.cpp response/response.cpp socket/SocketClass.cpp

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

all : $(NAME)

$(NAME) : $(SRCS)  $(HEADERS)
			@echo "compiling.."
			@$(CC)  -fsanitize=address -g $(FLAGS) $(SRCS) -o $(NAME)
			@echo "Done."

clean :
			@echo "cleaning.."

fclean :  clean 
			@$(RM) $(NAME)

re:				fclean all
			

.PHONY:			all, clean, fclean, re