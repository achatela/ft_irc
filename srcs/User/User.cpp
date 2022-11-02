#include "../../includes/User.hpp"

User::User(int fd, std::string password, char *hostname) : _hostname(hostname), _real_password(password), _fd(fd), _access(AUTHORIZED) {
    char client_reply[4096];
    char *client_infos;

    usleep(50000);
    recv(_fd, client_reply, 4096, 0);
    client_infos = strtok(client_reply, "\n");

    // Handle messages until we receive \r\n
    while (client_infos != NULL) {
        std::cout << client_infos << std::endl;
        if (strstr(client_infos, "PASS") != NULL){
            _password = std::string(client_infos + 5);
            if (_password[_password.length() - 1] == '\r')
                _password.pop_back();
            if (_password != _real_password)
                _access = FORBIDDEN;
            // std::cout << _password << std::endl;// debug
        }
        else if (strstr(client_infos, "NICK") != NULL){
            _nickname = std::string(client_infos + 5);
            if (_nickname[_nickname.length() - 1] == '\r')
                _nickname.pop_back();
            // Check if username is already existing code 433
            if (_nickname[0] == '\b' || _nickname[0] == '\r'
                || _nickname[0] == '@' || _nickname[0] == NULL || _nickname[0] == ' '){
                    _access = FORBIDDEN;
                    std::cout << "Wrong username format" << std::endl; //debug
            }
            // std::cout << _nickname << std::endl;// debug
        }
        else if (strstr(client_infos, "USER") != NULL)
        {
            _username = std::string(strtok(client_infos, ":") + 5);
            _real_name = std::string(strtok(NULL, ":"));
            if (_username[_username.length() - 1] == '\r')
                _username.pop_back();
            if (_real_name[_real_name.length() - 1] == '\r')
                _real_name.pop_back();
            // std::cout << _username << std::endl;// debug
            // std::cout << _real_name << std::endl;// debug
        }
        client_infos = strtok(NULL, "\n");
    }
    if (_password[0] == '\0' || _nickname[0] == '\0' || _real_name[0] == '\0'){
        _access = FORBIDDEN;
        std::cout << "missing informations" << std::endl; // debug
    }
    else if (_access == FORBIDDEN){
        std::cout << "Connection refused" << std::endl;
    }
    else{
        std::string toSend(":" + _hostname + " 001 " + _nickname +  " :Welcome to the Internet Relay Network " + _nickname + " ! " + _username + "@" + "\r\n" /*+ _hostname ?*/);
        send(_fd, toSend.c_str(), toSend.length(), 0);
        // std::cout << toSend << std::endl;
    }
}
        
User::~User(){};

void User::handleRequests(char *request){
    std::string req(request);

    std::cout << request << std::endl;
}