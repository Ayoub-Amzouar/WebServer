NAME = webserv
CC = c++ -std=c++98
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

DIR_SRCS = ./srcs/

HEADERS = ./headers/webserv.hpp
SRC = parsing/parsing.cpp

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

all : $(NAME)

$(NAME) : $(SRCS)  $(HEADERS)
			@$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean :

fclean :  clean 
			@$(RM) $(NAME)

re:				fclean all

.PHONY:			all, clean, fclean, re