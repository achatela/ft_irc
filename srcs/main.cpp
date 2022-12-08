#include "../includes/Server.hpp"

int main (int ac, char **av){
    Server *server = new Server(ac, av);

    while (server->getStatus() == ON || server->getStatus() == REBOOT){
      if (server->getStatus() == REBOOT){
        delete server;
        server = new Server(ac, av);
      }
        server->sondage();
    }
    delete server;
    return 0;
}