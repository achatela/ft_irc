NAME = ircserv

SRCFILES = main.cpp Server/Server.cpp User/User.cpp Command/Command.cpp
SOURCE = ./srcs/
SRCS = ${addprefix ${SOURCE},${SRCFILES}}

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

OBJSFILES = $(SRCFILES:.cpp=.o)
OBJS = $(SRCS:.cpp=.o)
OBJS_PATH = ${addprefix ${SOURCE},${OBJSFILES}}

%.o: %.cpp includes/utils.hpp includes/Server.hpp includes/User.hpp includes/Command.hpp
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) #$(OBJS_PATH) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	
clean:
	rm -f $(OBJS_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

debugflags:
	$(eval CXXFLAGS=-D DEBUG)

debug: fclean debugflags all

.PHONY: all clean fclean re
