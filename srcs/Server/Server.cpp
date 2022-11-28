#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"
#include <unistd.h>

Server::Server(void){};

Server::Server(int ac, char **av) : _opt(1), _status(ON), _addrlen(sizeof(_address)), _server_time(std::time(NULL)){
    Command _tmp;

    (void)_addrlen;
    _command_functions = _tmp.getCommand();
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

    //Check if fd < -1 et handle
    sock_fd = accept(_server_listen, (struct sockaddr*)&address, &addr_len);
    _pfds.push_back(pollfd());
    _pfds.back().fd = sock_fd;
    _pfds.back().events = POLLIN;
    _Users.insert(std::pair<int, User>(sock_fd, User(_password, address/*sock_fd, _password, _hostname*/))); // remove _hostname et changer par celui qu'on recoit dans USER
    //_command_functions["motd"]("motd\r\n", sock_fd, _Users, _channels);
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

    char server_reply[512];
    
    // std::cout << _Users.size() << std::endl;
    
    if (poll(&_pfds[0], _pfds.size(), 0) == -1){
        return;
    }
    if (_pfds[0].revents == POLLIN){
        addPfd();
    }
    if (_pfds.size() > 1)
    {
        for (std::vector<pollfd>::iterator it = _pfds.begin() + 1; it != _pfds.end(); it++)
        {
            if (it->revents == POLLIN)
            {
                if (recv(it->fd, server_reply, 512, MSG_DONTWAIT) == 0)
                {
                    std::cout << "devrait supprimer" << std::endl;
                    int i = it - _pfds.begin();
                    std::map<int, User>::iterator it2 = _Users.begin();
                    while (i - 1 > 0){
                        it2++;
                        i--;
                    }
                    it = _pfds.erase(it);
                    _Users.erase(it2);
                    break;
                }
                else{
                    int j = it - _pfds.begin();
                    handleRequests(server_reply, _pfds[j].fd);
                }
            }
            //std::cout << _pfds.size() << std::endl;
        }
    }
    //std::cout << "\terver_reply before reset = " << server_reply << std::endl;
    memset(server_reply, 0, 512);
}

void Server::checkInfo(User & user)
{
    if ((!user.getHostname().empty() && !user.getNickname().empty()
        && !user.getRealName().empty() && !user.getUsername().empty())
        && user.getPassword() == user.getRealPassword())
    {
        user.setAccess(AUTHORIZED);
        //send 001, 002, 003, 004 et motd
    }
}

void Server::handleRequests(char *request, int fd){
    try{
        _Users.at(fd).concatBuffer(request);
        while (_Users.at(fd).getBuffer().find("\r\n") != std::string::npos){
            if (DEBUG)
                std::cout << YELLOW << "Server" << GREEN " << " << CYAN << "[" << fd << "] " << GREEN << _Users.at(fd).getBuffer().substr(0, _Users.at(fd).getBuffer().find("\r\n") + 2) << RESET;
            std::string cmd = _Users.at(fd).getBuffer().substr(0, _Users.at(fd).getBuffer().find(' '));
            if (_Users.at(fd).getBuffer().find(' ') == std::string::npos)
                cmd = _Users.at(fd).getBuffer().substr(0, _Users.at(fd).getBuffer().find("\r\n"));
            try{
                if (_command_functions.at(cmd) != NULL)
                    _command_functions.at(cmd)(_Users.at(fd).getBuffer(), fd, _Users, _channels);
                if (_Users.at(fd).getAccess() == FORBIDDEN)
                    checkInfo(_Users.at(fd));
            }
            catch (std::exception &e){
                // std::cout << e.what() << std::endl;
                // std::cout << "Command doesn't exist" << std::endl;
            }
            _Users.at(fd).clearBuffer();
        }
    }
    catch (std::exception &e){
        e.what();
    }
}

