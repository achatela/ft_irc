NAME = ft_irc
SRCFILES = main.cpp Server/Server.cpp User/User.cpp
SOURCE = ./srcs/
OBJ = ./objs/
CXX = c++
SRCS = ${addprefix ${SOURCE},${SRCFILES}}
FLAGS = -Wall -Werror -Wextra -std=c++98
OBJSFILES = $(SRCFILES:.cpp=.o)
OBJS = $(SRCS:.cpp=.o)
OBJS_PATH = ${addprefix ${OBJ},${OBJSFILES}}

%.o: %.cpp includes/utils.hpp includes/Server.hpp includs/User.hpp
	$(CXX) $(FLAGS) -I.  -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) #$(OBJS_PATH) 
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME)
	mv ${OBJS} objs/

clean:
	rm -f $(OBJS_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
