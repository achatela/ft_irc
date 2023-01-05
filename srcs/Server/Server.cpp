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
    if (gethostname(_hostname, 40) != 0){
        std::cout << "Gethostname failed" << std::endl;
        exit(1);
    }
    std::cout << "host name is " << _hostname << std::endl;
    handleErrors(ac, av);
    _server_listen = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (setsockopt(_server_listen, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &_opt, sizeof(_opt)) != 0){
        std::cout << "Setsockopt failed" << std::endl;
        exit(1);
    }
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_port); // remplacer par av[1]
    if (bind(_server_listen, (struct sockaddr*)&_address, sizeof(_address)) != 0){
        std::cout << "Bind failed" << std::endl;
        exit(1);
    }
    if (listen(_server_listen, 10) != 0){
        std::cout << "Listen failed" << std::endl;
        exit(1);
    }
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
    if (sock_fd < 0){
        std::cout << "Accept failed" << std::endl << "Cannot connect to the socket" << std::endl;
        return ;
    }
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
    

            // https://stackoverflow.com/questions/12170037/when-to-use-the-pollout-event-of-the-poll-c-function
    // std::cout << "stuck1" << std::endl;
    // if (getAtFd().size() >= 1){
    //     // Set les getPfds()[index].events a POLLOUT correspondant au int dans getAtFd
    //     for (std::vector<int>::iterator it = getAtFd().begin(); it != getAtFd().end(); it++){
    //         std::cout << "stuck2" << std::endl;
    //         for (int i = 1; i < getPfds().size(); i++){
    //             std::cout << "stuck3" << std::endl;
    //             if (*it == getPfds()[i].fd){
    //                 std::cout << "index fd + 1" << std::endl;
    //                 _index_fds.push_back(getPfds()[i].fd);
    //                 getPfds()[i].revents = POLLOUT;
    //             }
    //         }
    //     }
    // }
    std::cout << "AVANT POLL" << std::endl;
    if (!(poll(&getPfds()[0], getPfds().size(), -1) > 0)){
        // std::cout << "ret" << std::endl;
        // for (int i = 0; i < _index_fds.size(); i++){
        //     std::cout << "stuck4" << std::endl;
        //     getPfds()[_index_fds[i]].revents = POLLIN;
        // }
        // _index_fds.clear();
        std::cout << "POLL RETURND" << std::endl;
        return;
    }
    std::cout << "QPRES POLL" << std::endl;
    // if (getAtFd().size() >= 1){
    //     std::cout << "in if" << std::endl;
    //     std::cout << getUsers().at(_index_fds[0]).getToSend().empty() << std::endl;
    //     int j = 0;
    //     // Send, recuperer le retour de send et enlever le nombre de caracteres correspondant
    //     for (int i = 0; i < _index_fds.size(); i++){
    //         while (!getUsers().at(_index_fds[i]).getToSend().empty()){
    //             std::cout << "stuc5k" << std::endl;
    //             std::string tmp(getUsers().at(_index_fds[i]).getToSend().begin(), (getUsers().at(_index_fds[i]).getToSend().begin() + getUsers().at(_index_fds[i]).getToSend().find("\r\n") + 2));
    //             if (DEBUG)
    //                 std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << getUsers().at(_index_fds[i]).getFdToSend()[0] << "] " << BLUE << tmp << RESET;
    //             j = send(getUsers().at(_index_fds[i]).getFdToSend()[0], tmp.c_str(), tmp.length(), 0);
    //             if (j == -1)
    //                 break;
    //             if (j == tmp.length()){
    //                 getUsers().at(_index_fds[i]).getFdToSend().erase(getUsers().at(_index_fds[i]).getFdToSend().begin());
    //                 getUsers().at(_index_fds[i]).getToSend().erase(getUsers().at(_index_fds[i]).getToSend().begin(), (getUsers().at(_index_fds[i]).getToSend().begin() + getUsers().at(_index_fds[i]).getToSend().find("\r\n") + 2));
    //             }
    //         }
    //     }
    //     for (int i = 0; i < _index_fds.size(); i++){
    //         std::cout << "stuck6" << std::endl;
    //         if (getUsers().at(_index_fds[i]).getToSend().empty()){
    //             getUsers().at(_index_fds[i]).getToSend().clear();
    //             getAtFd().erase(std::find(getAtFd().begin(), getAtFd().end(), _index_fds[i]));
    //         }
    //         // getPfds()[_index_fds[i]].revents = POLLIN;
    //     }
    //     _index_fds.clear();
    //     // Si la chaine a envoye est empty, pop le fd correspondant dans getAtFd
    //     // Reset les getPfds(index).events a POLLIN
    // }
    std::cout << "DEBUT" << std::endl;
    if (getPfds()[0].revents == POLLIN){
        addPfd();
    }

    if (getPfds().size() > 1)
    {
        std::vector<pollfd>::iterator it_end = getPfds().end();
        for (std::vector<pollfd>::iterator it = getPfds().begin(); it != it_end; it++)
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
fix:
                    std::vector<Channel>::iterator it3 = this->getChannels().begin();
                    size_t k = 0;
                    std::vector<Channel>::iterator chan_end = getChannels().end();
                    for(; it3 != chan_end; it3++){
                        k = 0;
                        size_t size_it3 = it3->getFdList().size();
                        while (k < size_it3){
                            if (it3->getFdList()[k] == it->fd){
                                _command_functions["PART"]("PART " + it3->getChannelName() + "\r\n", it->fd, *this);
                                goto fix;
                            }
                            k++;
                        }
                    }
                    close(it->fd);
                    it = getPfds().erase(it);
                    getUsers().erase(it2);
                    break;
                }
                else{
                    int j = it - getPfds().begin();
                    handleRequests(server_reply, getPfds()[j].fd);

                    if (getAtFd().size() >= 1){
                        // Set les getPfds()[index].events a POLLOUT correspondant au int dans getAtFd
                        std::vector<int>::iterator it_end = getAtFd().end();
                        for (std::vector<int>::iterator it = getAtFd().begin(); it != it_end; it++){
                            size_t pfds_size = getPfds().size();
                            for (unsigned long i = 1; i < pfds_size; i++){
                                if (*it == getPfds()[i].fd){
                                    _index_fds.push_back(getPfds()[i].fd);
                                    getPfds()[i].revents = POLLOUT;
                                }
                            }
                        }
                    }
                  
                    if (getAtFd().size() >= 1){
                        int j = 0;
                        // Send, recuperer le retour de send et enlever le nombre de caracteres correspondant
                        size_t index_fds_size = _index_fds.size();
                        for (unsigned long i = 0; i < index_fds_size; i++){
                            while (!getUsers().at(_index_fds[i]).getToSend().empty()){
                                std::string tmp(getUsers().at(_index_fds[i]).getToSend().begin(), (getUsers().at(_index_fds[i]).getToSend().begin() + getUsers().at(_index_fds[i]).getToSend().find("\r\n") + 2));
                                if (DEBUG)
                                    std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << getUsers().at(_index_fds[i]).getFdToSend()[0] << "] " << BLUE << tmp << RESET;
                                j = send(getUsers().at(_index_fds[i]).getFdToSend()[0], tmp.c_str(), tmp.length(), 0);
                                if (j == -1)
                                    break;
                                else if (size_t(j) == tmp.length()){
                                    getUsers().at(_index_fds[i]).getFdToSend().erase(getUsers().at(_index_fds[i]).getFdToSend().begin());
                                    getUsers().at(_index_fds[i]).getToSend().erase(getUsers().at(_index_fds[i]).getToSend().begin(), (getUsers().at(_index_fds[i]).getToSend().begin() + getUsers().at(_index_fds[i]).getToSend().find("\r\n") + 2));
                                }
                            }
                        }
                        for (unsigned long i = 0; i < index_fds_size; i++){
                            if (getUsers().at(_index_fds[i]).getToSend().empty()){
                                getUsers().at(_index_fds[i]).getToSend().clear();
                                getAtFd().erase(std::find(getAtFd().begin(), getAtFd().end(), _index_fds[i]));
                            }
                            // getPfds()[_index_fds[i]].revents = POLLIN;
                        }
                        _index_fds.clear();
                        // Si la chaine a envoye est empty, pop le fd correspondant dans getAtFd
                        // Reset les getPfds(index).events a POLLIN
                    }
                    memset(server_reply, 0, 512);
    std::cout << "FIN" << std::endl;
                    return ;
                }
            }
        }
        std::map<int, User>::iterator it_end2 = getUsers().end();
        for (std::map<int, User>::iterator it = getUsers().begin(); it != it_end2; it++){
            if (it->second.getIsConnected() == false){
                std::vector<pollfd>::iterator it2_end = getPfds().end();
                for(std::vector<pollfd>::iterator it2 = getPfds().begin(); it2 != it2_end; it2++){
                    if (it2->fd == it->first){
                        close(it2->fd);
                        getPfds().erase(it2);
                        memset(server_reply, 0, 512);
                        getUsers().erase(it);
    std::cout << "FIN" << std::endl;
                        return ;
                    }
                }
            }
        }
    }
    std::cout << "FIN" << std::endl;
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
        std::string toSend4(":" + user.getFullHostname() + " 004 " + user.getNickname() + " :ClownRC 1.0 iwo Oovimnptkl\r\n");
        send(fd, toSend4.c_str(), toSend4.length(), 0);
        std::stringstream stream2;
        stream2 << _Users.size() - atoi(getInvisibleUsers().c_str());
        std::string toSend5(":" + user.getFullHostname() + " 251 " + user.getNickname() + " :" + stream2.str() + " user(s) and " + getInvisibleUsers() + " invisible on 1 server(s)\r\n");
        send(fd, toSend5.c_str(), toSend5.length(), 0);
        std::string toSend6(":" + user.getFullHostname() + " 252 " + user.getNickname() + " " + getOperators() + " :operator(s) online\r\n");
        send(fd, toSend6.c_str(), toSend6.length(), 0);
        std::string toSend7(":" + user.getFullHostname() + " 253 " + user.getNickname() + " 0 :unknown connection(s)\r\n");
        send(fd, toSend7.c_str(), toSend7.length(), 0);
        std::stringstream stream;
        stream << getChannels().size();
        std::string toSend8(":" + user.getFullHostname() + " 254 " + user.getNickname() + " " + stream.str() + " :channel(s) formed\r\n");
        send(fd, toSend8.c_str(), toSend8.length(), 0);
        stream2.str("");
        stream2 << _Users.size();
        std::string toSend9(":" + user.getFullHostname() + " 255 " + user.getNickname() + " :I have " + stream2.str() + " clients and 0 server(s)\r\n");
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
    }
}

void Server::handleRequests(char *request, int fd){
    try{
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
            }
            getUsers().at(fd).clearBuffer();
        }
    }
    catch (std::exception &e){
        e.what();
    }
}


std::string Server::getInvisibleUsers(){
    size_t i = 0;
    std::map<int, User>::iterator it_end = _Users.end();
    for (std::map<int, User>::iterator it = _Users.begin(); it != it_end; it++){
        if (it->second.getUserMode().find("i") != std::string::npos){
            i++;
        }
    }
    std::stringstream stream;
    stream << i;
    return stream.str();
}

std::string Server::getOperators(){
    size_t i = 0;
    std::map<int, User>::iterator it_end = _Users.end();
    for (std::map<int, User>::iterator it = _Users.begin(); it != it_end; it++){
        if (it->second.getUserMode().find("o") != std::string::npos){
            i++;
        }
    }
    std::stringstream stream;
    stream << i;
    return stream.str();
}