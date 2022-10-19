NAME = ft_irc
SRCS = srcs/main.cpp srcs/handle_errors.cpp
OBJS_PATH = objs/main.o objs/handle_errors.o
CC = c++
FLAGS = -Wall -Werror -Wextra -std=c++98
OBJS = $(SRCS:.cpp=.o)

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
