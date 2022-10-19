NAME = ft_irc
SRCFILES = main.cpp handle_errors.cpp
SOURCE = ./srcs/
OBJ = ./objs/
CC = c++
SRCS = ${addprefix ${SOURCE},${SRCFILES}}
FLAGS = -Wall -Werror -Wextra -std=c++98
OBJSFILES = $(SRCFILES:.cpp=.o)
OBJS = $(SRCS:.cpp=.o)
OBJS_PATH = ${addprefix ${OBJ},${OBJSFILES}}

%.o: %.cpp 
	$(CC) $(FLAGS) -I./ -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	mkdir objs
	mv ${OBJS} objs/

clean:
	rm -f $(OBJS_PATH)

fclean: clean
	rm -f $(NAME)
	rm -rf objs

re: fclean all

.PHONY: all clean fclean re
