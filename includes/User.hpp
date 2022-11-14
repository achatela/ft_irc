#ifndef USER_HPP
# define USER_HPP

# include "utils.hpp"

class User{

    class Server;
    class Command;

    private:
        bool _access;
        std::string _real_password;
        std::string _hostname;
        int _fd;
        std::string _nickname; // 9 maximum any octet except NUL, CR(\r), LF(\b), " " and "@"
        std::string _username;
        std::string _real_name;
        std::string _password;
        
        std::string _buffer;

    public:
        User();
        User(std::string password);
        ~User();

        std::string getBuffer(){return _buffer;};
        void setBuffer(std::string buf){_buffer = buf;};
        void concatBuffer(std::string buf){_buffer += buf;};
        void clearBuffer();

        std::string getHostname(){return _hostname;};
        void setHostname(std::string hostname){_hostname = hostname; return;};
        std::string getRealPassword(){return _real_password;};
        bool getAccess(){return _access;};
        void setAccess(bool access){_access = access; return;};
        std::string getNickname(){return _nickname;};
        void setNickname(std::string username){_nickname = username; return;};
        std::string getUsername(){return _username;};
        void setUsername(std::string username){_username = username; return;};
        std::string getRealName(){return _real_name;};
        void setRealName(std::string real_name){_real_name = real_name; return;};
        std::string getPassword(){return _password;};
        void setPassword(std::string password){_password = password; return;};
        void setRealPassword(std::string realPassword){_real_password = realPassword;};
};

#endif