#ifndef USER_HPP
# define USER_HPP

#include "../includes/utils.hpp"

class User{

    class Server;

    private:
        bool _access;
        std::string _nickname; // 9 maximum any octet except NUL, CR(\r), LF(\b), " " and "@"
        std::string _username;
        std::string _real_name;
        std::string _password;
        std::string _real_password;
        std::string _hostname;
        int _fd;
        //char[4096] _buffer; (to keep string until \r\n)

    public:
        User(int fd, std::string password, char *hostname);
        ~User();
        void handleRequests(char *request);
};

#endif