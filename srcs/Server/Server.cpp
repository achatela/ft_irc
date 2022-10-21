#include "../../includes/Server.hpp"
#include <unistd.h>

Server::Server(void){};

Server::Server(int ac, char **av) : _opt(1), _status(ON){
    gethostname(_hostname, 40);
    std::cout << "host name is " << _hostname << std::endl;
    handleErrors(ac, av);
    _server_listen = socket(PF_INET, SOCK_STREAM, 0);
    setsockopt(_server_listen, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &_opt, sizeof(_opt));
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_port); // remplacer par av[1]
    bind(_server_listen, (struct sockaddr*)&_address, sizeof(_address));
    listen(_server_listen, 10); // check la doc 10 = file d'attente
    _pfds.push_back(pollfd());
    _pfds.back().fd = _server_listen;
    _pfds.back().events = POLLIN;
}

    
Server::~Server(){close(_server_listen);};

void Server::addPfd(){
    struct sockaddr_in address;
    int sock_fd;
    socklen_t addr_len = sizeof(address);

    sock_fd = accept(_server_listen, (struct sockaddr*)&address, &addr_len);
    _pfds.push_back(pollfd());
    _pfds.back().fd = sock_fd;
    _pfds.back().events = POLLIN;
	std::cout << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << "fd =" << sock_fd << std::endl;
}

void Server::handleErrors(int ac, char **av){

    if (ac != 3){
        std::cerr << "Format is: ./exec <port> <password>" << std::endl;
        exit(1);
    }
    _password = av[2];

    char *tmp;
    std::string number(av[1]);
    int ret = std::strtol(av[1], &tmp, 10);

    if (number.size() > 5 || ret == 0L || ret > 65536 || tmp[0] != '\0'){ // vérifier les ports inutilisables
        std::cerr << "Second argument as to be a valid number" << std::endl;
        exit(1);
    }
    _port = ret;
}

void Server::sondage(){

    
    if (poll(&_pfds[0], _pfds.size(), 1000) == -1){
        return;
    }
    //std::cout << _pfds.size() << std::endl;
    if (_pfds[0].revents == POLLIN){
        addPfd();
    }
}