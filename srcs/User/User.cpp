#include "../../includes/User.hpp"

User::User(int fd) : _fd(fd) {
    char client_reply[4096];
    char *client_infos;

    sleep(1);
    recv(_fd, client_reply, 4096, 0);
    client_infos = strtok(client_reply, "\n");
    while (client_infos != NULL) {
        if (strstr(client_infos, "PASS") != NULL)
            _password = std::string(client_infos + 5);
        else if (strstr(client_infos, "NICK") != NULL)
            _nickname = std::string(client_infos + 5);
        else if (strstr(client_infos, "USER") != NULL)
        {
            _username = std::string(strtok(client_infos, ":") + 5);
            _real_name = std::string(strtok(NULL, ":"));
        }
        client_infos = strtok(NULL, "\n");
    }
    std::cout << "password: " << _password << std::endl;
    std::cout << "nickname: " << _nickname << std::endl;
    std::cout << "username: " << _username << std::endl;
    std::cout << "real name: " << _real_name << std::endl;
}
        
User::~User(){};