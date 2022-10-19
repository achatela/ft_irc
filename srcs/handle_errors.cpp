#include "../includes/utils.hpp"


int handle_errors(int ac, char **av){
    (void)av;
    if (ac != 3){
        std::cerr << "Format is: ./exec <port> <password>" << std::endl;
        return (1);
    }
    return 0;
}