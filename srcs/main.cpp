#include "utils.hpp"

int main (int ac, char **av){
    int sockfd;

    if (handle_errors(ac, av) == 1)
        return 1;
    sockfd = create_socket();
    std::cout << sockfd << std::endl;
    close(sockfd);
    return 0;
}