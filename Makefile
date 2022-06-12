# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-hadj <mel-hadj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/04 13:00:30 by mel-hadj          #+#    #+#              #
#    Updated: 2022/06/07 15:42:33 by mel-hadj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv
CC = c++ -std=c++98
# FLAGS = -Wall -Wextra -Werror
RM = rm -rf

DIR_SRCS = ./srcs/

HEADERS = ./headers/webserv.hpp
SRC = parsing/parsing.cpp webserv.cpp parsing/check_errors.cpp  parsing/utils.cpp cgi/cgi.cpp cgi/status_code.cpp \
		cgi/utils.cpp socket/socket.cpp response/response.cpp

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

all : $(NAME)

$(NAME) : $(SRCS)  $(HEADERS)
			@echo "compiling.."
			@$(CC) $(FLAGS) $(SRCS) -o $(NAME)
			@echo "Done."

clean :
			@echo "cleaning.."

fclean :  clean 
			@$(RM) $(NAME)

re:				fclean all
			

.PHONY:			all, clean, fclean, re