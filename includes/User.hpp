#ifndef USER_HPP
# define USER_HPP

#include "../includes/utils.hpp"
#include "../includes/User.hpp"

class User{

    class Server;

    private:
        bool _access = FORBIDDEN;
        std::string _nickname; // 9 maximum
        std::string _username;
        std::string _real_name;

    public:
        User();
        ~User();
};

#endif