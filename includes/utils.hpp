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

# define ON 0
# define OFF 1

# define AUTHORIZED 0
# define FORBIDDEN 1

# define COMMANDS "PING", "PONG", "MODE"
# define COMMAND_SIZE 3

int handle_errors(int ac, char **av);
int create_socket(void);

#endif /* UTILS_HPP */