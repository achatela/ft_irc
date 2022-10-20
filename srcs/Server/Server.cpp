#include "../../includes/Server.hpp"

Server::Server(void){};

Server::Server(int ac, char **av) : _opt(1), _status(ON){
    handle_errors(ac, av);
    _server_listen = socket(PF_INET, SOCK_STREAM, 0);
    //sethostname("test", 5);
    setsockopt(_server_listen, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &_opt, sizeof(_opt));
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(6667); // remplacer par av[1]
    bind(_server_listen, (struct sockaddr*)&_address, sizeof(_address));
    listen(_server_listen, 10); // check la doc 10 = file d'attente
}

    
Server::~Server(){close(_server_listen);};

void Server::handle_errors(int ac, char **av){

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
}

void Server::sondage(){

    std::cout << _password;
    if (poll(&_pfds[0], _pfds.size(), 1000) == -1){
        return;
    }
}