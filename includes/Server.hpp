#ifndef SERVER_HPP
# define SERVER_HPP

# include "utils.hpp"
# include "Command.hpp"

class Server{

    private:
        int _opt;
        bool _status;
        struct sockaddr_in _address;
        int _addrlen;
        int _server_listen;
        int _port;

        std::map<std::string, void (*) (std::string buffer, int fd, std::map<int, User > & Users)> _command_functions;
        std::vector<pollfd > _pfds;
        std::string _password;

        char _hostname[1024];
        std::map<int, User > _Users;

    public:
        Server();
        Server(int ac, char **av);
        ~Server();

        bool getStatus() {return _status;};

        void handleErrors(int ac, char **av);
        void handleRequests(char *request, int j);

        void sondage(); //nom a change
        void addPfd();
};

#endif