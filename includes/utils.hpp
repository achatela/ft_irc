#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <cstdlib>
# include <netinet/in.h>
# include <unistd.h>
# include <vector>
# include <poll.h>

# define ON 0
# define OFF 1

int handle_errors(int ac, char **av);
int create_socket(void);

#endif /* UTILS_HPP */