#include "../includes/Server.hpp"

int main (int ac, char **av){
    Server server(ac, av);

    while (server.getStatus() == ON)
      server.sondage();
    //close(sockfd);
    return 0;
}