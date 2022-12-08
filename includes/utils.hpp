#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <cstdlib>
# include <netinet/in.h>
# include <unistd.h>
# include <vector>
# include <map>
# include <poll.h>
# include <arpa/inet.h>
# include <cstring>
# include <string>
# include <netdb.h>
# include <ctime>
#include <unistd.h>
# include <sstream>
#include <bits/stdc++.h>

# define ON 0
# define OFF 1
# define REBOOT 2

#ifndef DEBUG
    #define DEBUG 0
#endif

# define AUTHORIZED 0
# define FORBIDDEN 1

#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"
#define MAGENTA "\033[0;35m"

/*# define COMMANDS "PING", "PONG", "MODE"*/
# define COMMAND_SIZE 3

int handle_errors(int ac, char **av);
int create_socket(void);

#endif /* UTILS_HPP */