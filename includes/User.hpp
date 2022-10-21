#ifndef USER_HPP
# define USER_HPP

#include "../includes/utils.hpp"

class User{

    class Server;

    private:
        bool _access = FORBIDDEN;
        std::string _nickname; // 9 maximum
        std::string _username;
        std::string _real_name;
        std::string _password;
        int _fd;

    public:
        User(int fd);
        ~User();
};

#endif