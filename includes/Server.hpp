#ifndef SERVER_HPP
# define SERVER_HPP

# include "utils.hpp"
#include "User.hpp"

class Server{

    private:
        int _opt;
        int _server_listen;
        int _port;
        struct sockaddr_in _address;
        int addrlen = sizeof(_address);
        std::vector<pollfd> _pfds;
        bool _status;
        std::string _password;
        char _hostname[1024];
        std::map<int, User> _Users;

    public:
        Server();
        Server(int ac, char **av);
        ~Server();

        bool getStatus() {return _status;};

        void handleErrors(int ac, char **av);
        void sondage(); //nom a change
        void addPfd();
};

#endif