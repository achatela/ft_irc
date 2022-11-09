#ifndef USER_HPP
# define USER_HPP

# include "../includes/utils.hpp"

class User{

    class Server;
    class Command;

    private:
        std::string _hostname;
        std::string _real_password;
        int _fd;
        bool _access;
        std::string _nickname; // 9 maximum any octet except NUL, CR(\r), LF(\b), " " and "@"
        std::string _username;
        std::string _real_name;
        std::string _password;
        
        std::string _buffer;

    public:
        User(int fd, std::string password, char *hostname);
        ~User();

        std::string getBuffer(){return _buffer;};
        void setBuffer(std::string buf){_buffer = buf;};
        void concatBuffer(std::string buf){_buffer += buf;};

        bool getAccess(){return _access;};
};

#endif