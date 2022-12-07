#include "../../includes/Server.hpp"
#include "../../includes/User.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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
    getPfds().push_back(pollfd());
    getPfds().back().fd = _server_listen;
    getPfds().back().events = POLLIN;
}

Server::~Server(){close(_server_listen);};

void Server::addPfd(){
    struct sockaddr_in address;
    int sock_fd;
    socklen_t addr_len = sizeof(address);

    //Check if fd < -1 et handle
    sock_fd = accept(_server_listen, (struct sockaddr*)&address, &addr_len);
    getPfds().push_back(pollfd());
    getPfds().back().fd = sock_fd;
    getPfds().back().events = POLLIN;
    getUsers().insert(std::pair<int, User>(sock_fd, User(_password, address/*sock_fd, _password, _hostname*/))); // remove _hostname et changer par celui qu'on recoit dans USER
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
    
    // std::cout << getUsers().size() << std::endl;
    // if (getUsers().size() != getPfds().size() - 1){
    //     int find = open("osef.txt", O_RDONLY);

    //     for (std::vector<pollfd>::iterator it = getPfds().begin() + 1; it != getPfds().end(); it++){
    //         if (it->fd == find){
    //             getPfds().erase(it);
    //             close(find);
    //             return;
    //         }
    //     }
    // }
    
    if (poll(&getPfds()[0], getPfds().size(), 0) == -1){
        return;
    }
    if (getPfds()[0].revents == POLLIN){
        addPfd();
    }
    if (getPfds().size() > 1)
    {
        for (std::vector<pollfd>::iterator it = getPfds().begin(); it != getPfds().end(); it++)
        {
            if (it->revents == POLLIN)
            {
                if (recv(it->fd, server_reply, 512, MSG_DONTWAIT) == 0)
                {
                    int i = it - getPfds().begin();
                    std::map<int, User>::iterator it2 = getUsers().begin();
                    while (i - 1 > 0){
                        it2++;
                        i--;
                    }
                    close(it->fd);
                    it = getPfds().erase(it);
                    getUsers().erase(it2);
                    break;
                }
                else{
                    int j = it - getPfds().begin();
                    handleRequests(server_reply, getPfds()[j].fd);
                    memset(server_reply, 0, 512);
                    return ;
                }
            }
        }
        for (std::map<int, User>::iterator it = getUsers().begin(); it != getUsers().end(); it++){
            if (it->second.getIsConnected() == false){
                for(std::vector<pollfd>::iterator it2 = getPfds().begin(); it2 != getPfds().end(); it2++){
                    if (it2->fd == it->first){
                        close(it2->fd);
                        getPfds().erase(it2);
                        memset(server_reply, 0, 512);
                        getUsers().erase(it);
                        return ;
                    }
                }
            }
        }
    }
    //std::cout << "\terver_reply before reset = " << server_reply << std::endl;
    memset(server_reply, 0, 512);
}

void Server::checkInfo(User & user, int fd)
{
    if ((!user.getHostname().empty() && !user.getNickname().empty()
        && !user.getRealName().empty() && !user.getUsername().empty())
        && user.getPassword() == user.getRealPassword())
    {
        user.setAccess(AUTHORIZED);
        std::string toSend1(":" + user.getFullHostname() + " 001 " + user.getNickname() + " :Welcome to the Internet Relay Network " + user.getFullHostname() + "\r\n");
        send(fd, toSend1.c_str(), toSend1.length(), 0);
        std::string toSend2(":" + user.getFullHostname() + " 002 " + user.getNickname() + " :Your host is " + user.getHost() + "\r\n");
        send(fd, toSend2.c_str(), toSend2.length(), 0);
        std::string toSend3(":" + user.getFullHostname() + " 003 " + user.getNickname() + " :This server was created " + std::asctime(std::localtime(&_server_time)) + "\r\n");
        send(fd, toSend3.c_str(), toSend3.length(), 0);
        std::string toSend4(":" + user.getFullHostname() + " 004 " + user.getNickname() + " :ClownRC 1.0 aiwro Oovimnptkl\r\n");
        send(fd, toSend4.c_str(), toSend4.length(), 0);
        std::string toSend5(":" + user.getFullHostname() + " 251 " + user.getNickname() + " :There are X users and X invisible on X servers\r\n");
        send(fd, toSend5.c_str(), toSend5.length(), 0);
        std::string toSend6(":" + user.getFullHostname() + " 252 " + user.getNickname() + " X :operator(s) online\r\n");
        send(fd, toSend6.c_str(), toSend6.length(), 0);
        std::string toSend7(":" + user.getFullHostname() + " 253 " + user.getNickname() + " X :unknown connection(s)\r\n");
        send(fd, toSend7.c_str(), toSend7.length(), 0);
        std::stringstream stream;
        stream << getChannels().size();
        std::string toSend8(":" + user.getFullHostname() + " 254 " + user.getNickname() + " " + stream.str() + " :channels formed\r\n");
        send(fd, toSend8.c_str(), toSend8.length(), 0);
        std::string toSend9(":" + user.getFullHostname() + " 255 " + user.getNickname() + " :I have X clients and X servers\r\n");
        send(fd, toSend9.c_str(), toSend9.length(), 0);
        if (DEBUG){
            std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend1 << RESET;
            std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend2 << RESET;
            std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend3 << RESET;
            std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend4 << RESET;
            std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend5 << RESET;
            std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend6 << RESET;
            std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend7 << RESET;
            std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend8 << RESET;
            std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend9 << RESET;
        }
        _command_functions.at("motd")(getUsers().at(fd).getBuffer(), fd, *this);
        //send 001, 002, 003, 004 ... 255 et motd
    }
}

void Server::handleRequests(char *request, int fd){
    try{
        std::cout << request << std::endl;
        getUsers().at(fd).concatBuffer(request);
        while (getUsers().at(fd).getBuffer().find("\r\n") != std::string::npos){
            if (DEBUG)
                std::cout << YELLOW << "Server" << GREEN " << " << CYAN << "[" << fd << "] " << GREEN << getUsers().at(fd).getBuffer().substr(0, getUsers().at(fd).getBuffer().find("\r\n") + 2) << RESET;
            std::string cmd = getUsers().at(fd).getBuffer().substr(0, getUsers().at(fd).getBuffer().find(' '));
            if (getUsers().at(fd).getBuffer().find(' ') == std::string::npos)
                cmd = getUsers().at(fd).getBuffer().substr(0, getUsers().at(fd).getBuffer().find("\r\n"));
            try{
                if (_command_functions.at(cmd) != NULL)
                    _command_functions.at(cmd)(getUsers().at(fd).getBuffer(), fd, *this);
                if (getUsers().at(fd).getAccess() == FORBIDDEN)
                    checkInfo(getUsers().at(fd), fd);
            }
            catch (std::exception &e){
                // std::cout << e.what() << std::endl;
                // std::cout << "Command doesn't exist" << std::endl;
            }
            getUsers().at(fd).clearBuffer();
        }
    }
    catch (std::exception &e){
        e.what();
    }
}

