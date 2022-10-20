NAME = ft_irc
SRCFILES = main.cpp handle_errors.cpp create_sock.cpp
SOURCE = ./srcs/
OBJ = ./objs/
CC = c++
SRCS = ${addprefix ${SOURCE},${SRCFILES}}
FLAGS = -Wall -Werror -Wextra -std=c++98
OBJSFILES = $(SRCFILES:.cpp=.o)
OBJS = $(SRCS:.cpp=.o)
OBJS_PATH = ${addprefix ${OBJ},${OBJSFILES}}

%.o: %.cpp includes/utils.hpp
	$(CC) $(FLAGS) -I./includes -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) #$(OBJS_PATH) 
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	mv ${OBJS} objs/

clean:
	rm -f $(OBJS_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
