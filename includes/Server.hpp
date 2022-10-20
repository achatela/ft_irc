#ifndef SERVER_HPP
# define SERVER_HPP

# include "utils.hpp"

class Server{

    private:
        int _opt;
        int _server_listen;
        int _port;
        struct sockaddr_in _address;
        std::vector<pollfd> _pfds;
        bool _status;
        std::string _password;

    public:
        Server();
        Server(int ac, char **av);
        ~Server();

        bool getStatus() {return _status;};

        void handle_errors(int ac, char **av);
        void sondage(); //nom a change
};

#endif