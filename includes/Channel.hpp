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
        std::map <int, User > _Users;
        std::map <std::string, std::string> _Users_modes;

    public:

        Channel(){;};
        ~Channel(){;};

        std::vector <int> &getFdList(){return _fd_list;};
        std::vector <std::string> &getUserList(){return _user_list;};
        std::string getChannelName(){return _channel_name;};
        void setChannelName(std::string name){_channel_name = name;};
        std::string getChannelMode(){return _channel_mode;};
        void setChannelMode(std::string name){_channel_mode = name;};
};

#endif