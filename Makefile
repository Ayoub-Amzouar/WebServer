NAME = webserv
CC = c++ -std=c++98
FLAGS = -Wall -Wextra -Werror
RM = rm -rf 
HEADERS = webserv.hpp
SRC = parsing.hpp

all : $(NAME)

$(NAME) : $(SRC) $(HEADERS)
			@$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean :

fclean :  clean 
			@$(RM) $(NAME)

re:				fclean all

.PHONY:			all, clean, fclean, re