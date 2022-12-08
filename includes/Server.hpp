#ifndef SERVER_HPP
# define SERVER_HPP

# include "utils.hpp"
# include "Command.hpp"
# include "Channel.hpp"

class Server{

    private:
        int _opt;
        bool _status;
        struct sockaddr_in _address;
        int _addrlen;
        int _server_listen;
        int _port;

        // std::map<std::string, void (*) (std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels)> _command_functions;
        std::map<std::string, void (*) (std::string buffer, int fd, Server & server)> _command_functions;
        std::vector<pollfd > _pfds;
        std::string _password;

        char _hostname[1024];
        std::map<int, User > _Users;

        std::vector <Channel> _channels;
        std::time_t _server_time;

    public:
        Server();
        Server(int ac, char **av);
        ~Server();

        bool getStatus() {return _status;};

        void handleErrors(int ac, char **av);
        void handleRequests(char *request, int j);

        std::string getPassword(){return _password;};

        void sondage(); //nom a change
        void addPfd();
        void checkInfo(User & user, int fd);

        std::map<int, User>& getUsers(){return _Users;}
        std::vector<pollfd>& getPfds(){return _pfds;}
        std::vector<Channel>& getChannels(){return _channels;}

        std::string getInvisibleUsers();
        std::string getOperators();

        void setStatus(bool toSet){_status = toSet;}

};

#endif