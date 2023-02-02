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
CC = c++
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

DIR_SRCS = ./srcs/

HEADERS = ./headers/webserv.hpp
SRC = parsing/request_parsing.cpp parsing/file_parsing.cpp webserv.cpp  parsing/utils.cpp socket/SocketClass.cpp response/response.cpp cgi/utils.cpp cgi/cgi.cpp \
	response/get_method.cpp response/delete_method.cpp response/post_method.cpp

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

all : $(NAME)

$(NAME) : $(SRCS)
		@echo "compiling.."
		@$(CC) $(FLAGS) $(SRCS) -o $(NAME)
		@echo "Done."

clean :
		@echo "cleaning.."

fclean:	clean 
			@$(RM) $(NAME)

re:		fclean all
			

.PHONY:	all, clean, fclean, re