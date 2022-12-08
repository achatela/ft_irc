#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "utils.hpp"
# include "User.hpp"
# include <map>
# include <string>

class User;
class Channel{


    private:
        std::string _channel_name;
        std::string _channel_mode;
        std::vector <int> _fd_list;
        std::vector <std::string> _user_list;
        std::vector <std::string> _ban_list;
        std::map <int, User > _Users;
        std::map <int, std::string> _Users_modes;
        std::string         _topic;

    public:

        Channel() : _channel_mode("n"), _ban_list(10, "ee"){;};
        ~Channel(){;};

        void pushFdList(int fd){_fd_list.push_back(fd);};

        std::vector <int> &getFdList(){return _fd_list;};
        std::vector <std::string> &getUserList(){return _user_list;};
        std::vector <std::string> &getBanList(){return _ban_list;};
        std::map <int, std::string>& getUserMode(){return _Users_modes;}
        std::string getChannelName(){return _channel_name;};
        void setChannelName(std::string name){_channel_name = name;};
        std::string getChannelMode(){return _channel_mode;};
        void setChannelMode(std::string name){_channel_mode = name;};

        bool isInUserList(std::string name){
            size_t i = 0;
            for (;i < _user_list.size(); i++){
                if(_user_list[i] != name)
                    break ;
            }
            if (_user_list[i] == name)
                return true;
            return false;
        }

        std::string getTopic(){return _topic;};
        void setTopic(std::string buffer){_topic = buffer;}
        void clearTopic(){_topic.clear();};
};

#endif