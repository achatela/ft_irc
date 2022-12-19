#ifndef USER_HPP
# define USER_HPP

# include "utils.hpp"

class User{

    class Server;
    class Command;

    private:
        bool _access;
        std::string _real_password;
        std::string _host;
        std::string _hostname;
        std::string _domain_name;
        int _fd;
        std::string _nickname; // 9 maximum any octet except NUL, CR(\r), LF(\b), " " and "@"
        std::string _username;
        std::string _real_name;
        std::string _password;
        std::string _hostaddr;
        std::string _buffer;
        bool        _isAway;
        bool        _isConnected;
        std::string _usermode;
        std::string _awayMsg;

        // a chaque append a _toSend, ajouter le fd au vector; quand on envoie, send(get.atuser(machin).getFdToSend[0], _toSend.find.("\r\n"), .length.previousArg);
        std::string         _toSend;
        std::vector<int>    _fdToSend;

    public:
        User();
        User(std::string password, struct sockaddr_in address);
        ~User();

        std::string &getToSend(){return _toSend;}
        std::vector<int> &getFdToSend(){return _fdToSend;}

        std::string getBuffer(){return _buffer;};
        void setBuffer(std::string buf){_buffer = buf;};
        void concatBuffer(std::string buf){_buffer += buf;};
        void clearBuffer();

        void setIsConnected(bool status){_isConnected = status;};
        bool getIsConnected(){return _isConnected;};

        std::string getFullHostname(){
            std::string ret(_nickname + "!" + _username + "@" + _hostname);
            return ret;
        }
        std::string getFullInfo(){
            std::string ret(_username + "!" + _username + "@" + _hostname);
            return ret;
        }
        std::string getHost(){return _host;};
        void setHost(std::string host){_host = host; return;};
        std::string getHostname(){return _hostname;};
        void setHostname(std::string hostname){_hostname = hostname; return;};
        std::string getDomainName(){return _domain_name;};
        void setDomainName(std::string domain_name){_domain_name = domain_name; return;};
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
        void setIsAway(bool status){_isAway = status;};
        bool getIsAway(){return _isAway;};
        void setUserMode(std::string mode){_usermode = mode;};
        std::string getUserMode(){return _usermode;};
        void setAwayMsg(std::string msg){_awayMsg = msg;};
        std::string getAwayMsg(){return _awayMsg;};

        std::string getUserHost(){
            std::string ret;
        
            ret += ":" + _nickname + "="; 
            if (_isAway == true)
                ret += "-";
            else
                ret += "+";
            if (_usermode.find("o") == std::string::npos)
                ret += "~";
            else
                ret += "*";
            ret += _username + "@" + _hostname;
            return ret;
        };

        // bool operator!= (User &tmp){return (getFullInfo() == tmp.getFullInfo());}
};

#endif