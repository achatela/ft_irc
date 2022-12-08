#include "../../includes/Command.hpp"
#include "../../includes/Server.hpp"

void Command::reply(int fd, std::string toSend){
    send(fd, toSend.c_str(), toSend.length(), 0);
    if (DEBUG)
        std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend << RESET;
}

void Command::ACCEPT(std::string, int fd, Server &){
    reply(fd, "Unknown command: ACCEPT\r\n");
};

void Command::ADMIN(std::string, int fd, Server & server){
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 256 " + server.getUsers().at(fd).getNickname() + " ClownRC :Administrative info\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 257 " + server.getUsers().at(fd).getNickname() + " :You're on ClownRC, our server is hosted in France and is accesible with the following url FAUT QUON LA SET\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 258 " + server.getUsers().at(fd).getNickname() + " :If you need any information relating our project fell free to contact us\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 259 " + server.getUsers().at(fd).getNickname() + " :<achatela@student.42.fr>, <hcarpent@student.42.fr>\r\n");
};

void Command::AWAY(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 2);
    std::string away_msg(buffer.substr(0, buffer.find("\r\n")));

    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 306 " + server.getUsers().at(fd).getNickname() + " :You have been marked as begin away\r\n");
    server.getUsers().at(fd).setIsAway(true);
    server.getUsers().at(fd).setAwayMsg(away_msg);
};


void Command::BAN(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};

void Command::DIE(std::string, int fd, Server & server){
    if (server.getUsers().at(fd).getUserMode().find('o') == std::string::npos){
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 481 " + server.getUsers().at(fd).getNickname() + " :Permission Denied- You're not an IRC operator\r\n");
        return;
    }
    server.setStatus(OFF);
};

void Command::INFO(std::string, int fd, Server & server){
    std::string debug_str;
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371" + server.getUsers().at(fd).getNickname() + " :------------------INFO------------------\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :Server name ClownRC / URL A DEFINE\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :Version : 1.0\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371" + server.getUsers().at(fd).getNickname() + " :Made by the two original clowns:\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :- achatela <achatela@student.42.fr>\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :- hcarpent <hcarpent@student.42.fr>\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :Thanks for using ClownRC !\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :End of /INFO list\r\n");
};


void Command::INVITE(std::string, int fd,  Server &){
    reply(fd, "Unknown command: INVITE\r\n");
}


void Command::ISO(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};


void Command::JOIN(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name(buffer.substr(0, buffer.find("\r\n")));
    std::vector<Channel>::iterator it = server.getChannels().begin();
    for (; it != server.getChannels().end(); it++){
        if (it->getChannelName() == chan_name){
            for (std::vector<int>::iterator ite = it->getFdList().begin(); ite != it->getFdList().end(); ite++){
                reply(*ite, ":" + server.getUsers().at(fd).getFullHostname() + " JOIN :" + chan_name + "\r\n"); // envoyer le putain
            }
            break;
        }
    }
    if (it == server.getChannels().end()){
        server.getChannels().push_back(Channel());
        server.getChannels().back().setChannelName(chan_name);
        it = server.getChannels().end() - 1;
        it->getUserMode()[fd] += "o";
    }
    else
        it->getUserMode()[fd] += "w";
    it->pushFdList(fd); // protéger si l'user n'a pas les droits
    it->getUserList().push_back(server.getUsers().at(fd).getNickname());
    std::string msg = "@";
    for (std::vector<std::string>::iterator ite = it->getUserList().begin() ; ite != it->getUserList().end(); ite++){
        msg += *ite;
        if (it->getUserList().end() - ite != 1){
            msg += " ";
        }
    }
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 353 " + server.getUsers().at(fd).getNickname() + " = " + chan_name + " :" + msg + "\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 366 " + server.getUsers().at(fd).getNickname() + " " + chan_name + " :End of /NAMES list\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " JOIN " + chan_name + "\r\n");
};


void Command::KICK(std::string buffer, int fd,  Server & server){
    //
    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name =  buffer.substr(0, buffer.find(' '));
    buffer.erase(0, buffer.find(' ') + 1);
    std::string nickname =  buffer.substr(0, buffer.find(' '));
    std::vector<Channel>::iterator it = server.getChannels().begin();

    for (; it != server.getChannels().end(); it++){
        if (it->getChannelName() == chan_name)
            break;
    }
    if (it == server.getChannels().end()){// a check
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 401 " + server.getUsers().at(fd).getNickname() + " " + nickname + " :No such nick/channel\r\n");
        return;
    }

    std::vector<std::string>::iterator it2 = it->getUserList().begin();
    for (; it2 != it->getUserList().end(); it2++){
        if (*it2 == nickname)
            break;
    }
    if (it2 == it->getUserList().end()){// a check
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 401 " + server.getUsers().at(fd).getNickname() + " " + nickname + " :No such nick/channel\r\n");
        return;
    }

    if (server.getUsers().at(fd).getUserMode().find("o") == std::string::npos && it->getUserMode().at(fd).find("o") == std::string::npos){ // check if he's chan op too
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 482 " + server.getUsers().at(fd).getNickname() + " " + chan_name + " :You're not channel operator\r\n");
        return ;
    }

    std::vector<int>::iterator it3 = it->getFdList().begin();
    for (; it3 != it->getFdList().end(); it3++){
        reply(*it3, ":" + server.getUsers().at(fd).getFullHostname() + " KICK " + chan_name + " " + nickname + " :\r\n");
    }
    it2 = it->getUserList().begin();
    it3 = it->getFdList().begin();
    for (; it2 != it->getUserList().end(); it2++, it3++){
        if (*it2 == nickname){
            it->getUserList().erase(it2);
            it->getFdList().erase(it3);
            break;
        }
    }
    if (it->getUserList().empty())
        server.getChannels().erase(it);

};


void Command::KICKBAN(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};


void Command::KILL(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string nickname =  buffer.substr(0, buffer.find(' '));
    buffer.erase(0, buffer.find(' ') + 1);
    if (buffer == ":\r\n"){
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 461 " + server.getUsers().at(fd).getNickname() + " KILL :Not enough parameters\r\n");
        return;
    }
    if (server.getUsers().at(fd).getUserMode().find('o') == std::string::npos){
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 481 " + server.getUsers().at(fd).getNickname() + " :Permission Denied- You're not an IRC operator\r\n");
        return;
    }
    for (std::map<int, User>::iterator it = server.getUsers().begin(); it != server.getUsers().end(); it++){
        if (it->second.getNickname() == nickname){
            reply(it->first, ":" + server.getUsers().at(fd).getFullHostname() + " KILL " + buffer);
            reply(it->first, ":" + it->second.getFullHostname() + " QUIT " + buffer);
            for (std::vector<pollfd>::iterator it2 = server.getPfds().begin(); it2 != server.getPfds().end(); it2++){
                if (it2->fd == it->first){
                    close(it2->fd);
                    server.getPfds().erase(it2);
                    server.getUsers().erase(it);
                    return;
                }
            }
        }
    }
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 401 " + server.getUsers().at(fd).getNickname() + " " + nickname + " :No such nick/channel\r\n");
};

void Command::LINKS(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};


void Command::LIST(std::string buffer, int fd,  Server & server){
    //Format is fullhostname 322 username #chan_name (nb users) :(topic)
    //then fullhostname 323 username :End of /LIST

    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name(buffer.substr(0, buffer.find(" ")));
    std::string cmp_name(chan_name.substr(0, chan_name.find("\r\n")));
    std::stringstream stream;

    if ((chan_name[0] == '\r' && chan_name[1] == '\n') || buffer.size() != chan_name.size()){
        for (std::vector<Channel>::iterator it = server.getChannels().begin(); it != server.getChannels().end(); it++){
            stream << it->getFdList().size();
            reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 322 " + server.getUsers().at(fd).getUsername() + " " + it->getChannelName() + " " + stream.str() + " " + it->getTopic() + "\r\n");
        }
    }
    else{
        for (std::vector<Channel>::iterator it = server.getChannels().begin(); it != server.getChannels().end(); it++){
            std::cout << "channel name = " << it->getChannelName() << " cmp_name = " << cmp_name << std::endl;
            if (it->getChannelName() == cmp_name){
                stream << it->getFdList().size();
                reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 322 " + server.getUsers().at(fd).getUsername() + " " + it->getChannelName() + " " + stream.str() + " " + it->getTopic() + "\r\n");
                break;
            }
        }
    }
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 323 " + server.getUsers().at(fd).getUsername() + " :End of /LIST\r\n");
};

void Command::MAP(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};

void Command::MODE(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp(buffer.substr(0, buffer.find(" ")));
    if (buffer.find(' ') != std::string::npos)
        buffer.erase(0, buffer.find(' ') + 1);
    if (tmp[0] == '#'){
        std::string flags(buffer.substr(0, buffer.find(" ")));
        size_t space_num = 0;
        Channel check;
        int j = getChannel(tmp, server.getChannels());
        if (j == -1){
            return ;
        }
        else
            check = server.getChannels().at(j);
        if (flags[0] != '#'){
            buffer.erase(0, buffer.find(' ') + 1);
            if (buffer.substr(0, buffer.find(' ')) == "+b")
                check.getBanList().push_back(buffer.substr(0, buffer.find("\r\n")));
            size_t i = 0;
            for(; buffer[i] != '\r'; i++){
                if (buffer[i] == ' ' && buffer[i + 1] != '+')
                    space_num++;
            }
            std::cout << buffer <<std::endl;
            std::string username[space_num + 1];
            i = 0;
            for (; i <= space_num; i++){
                username[i] += buffer.substr(0, buffer.find(" "));
                buffer.erase(0, buffer.find(' ') + 1);
            }
            i = 0;
            std::string tmp_send;
            for(; i <= space_num; i++){
                if (username[i][0] == '+')
                    break;
                if (!check.isInUserList(username[i])){
                    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 441 " + server.getUsers().at(fd).getNickname() + " " + tmp + " :User not on the channel\r\n");
                }
                else{
                    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 324 " + server.getUsers().at(fd).getNickname() + " " + tmp + " +" + flags[i + 1] + " " + username[i] + "\r\n");
                }
            }
            if (i < flags.size() - 1){
                ;
            }
        }
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 324 " + server.getUsers().at(fd).getNickname() + " " + tmp + " +n\r\n");
    }
    else{
        if (tmp != server.getUsers().at(fd).getNickname() && server.getUsers().at(fd).getUserMode().find('o') == std::string::npos){
            reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 502 " + server.getUsers().at(fd).getNickname() + " :Can't change mode for other users\r\n");
            return;
        }
        std::map<int, User>::iterator it = server.getUsers().begin();
        for (; it != server.getUsers().end(); it++){
            if (it->second.getNickname() == tmp)
                break;
        }
        if (it == server.getUsers().end()){
            reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 401 " + server.getUsers().at(fd).getNickname() + " " + tmp + " :No such nick/channel\r\n");
            return;
        }
        if (buffer.find(' ') != std::string::npos)
            buffer = buffer.substr(0, buffer.find(' '));
        if (buffer.find('\r') != std::string::npos)
            buffer = buffer.substr(0, buffer.find('\r'));
        if (buffer[0] != '+' && buffer[0] != '-')
            buffer = '+' + buffer;
        for (std::string::size_type i = 1; i < buffer.size(); i++)//effacer les doublon et trouver les modes inconnus
        {
            if (buffer[i] != 'w' && buffer[i] != 'i' && buffer[i] != 'o'){
                reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 501 " + server.getUsers().at(fd).getNickname() + " :Unknown MODE flag\r\n");
                return;
            }
            std::string::size_type j = i + 1;
            while (j < buffer.size())
            {
                if (buffer[i] == buffer[j])
                    buffer.erase(j, 1);
                else
                    ++j;
            }
        }
        if (buffer.find('o') != std::string::npos && server.getUsers().at(fd).getUserMode().find('o') == std::string::npos)
            buffer.erase(buffer.find('o'), 1);
        std::string mode = server.getUsers().at(fd).getUserMode();
        if (buffer[0] == '+'){
            for (std::string::size_type i = 1; i < buffer.size(); i++){//ajouter des modes
                if (mode.find(buffer[i]) == std::string::npos)
                    mode += buffer[i];
            }
        }
        else{
            for (std::string::size_type i = 1; i < buffer.size(); i++){//enlever des modes
                if (mode.find(buffer[i]) != std::string::npos)
                    mode.erase(mode.find(buffer[i]), 1);
            }
        }
        server.getUsers().at(fd).setUserMode(mode);
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 221 " + server.getUsers().at(fd).getNickname() + " +" + server.getUsers().at(fd).getUserMode() + "\r\n");
    }

};


void Command::MOTD(std::string, int fd, Server & server){
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 375 " + server.getUsers().at(fd).getNickname() + " :- ClownRC Message of the day\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :-           achatela                                hcarpent\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⣼⡟⠋⣀⣼⣾⣶⣶⣦⣤⣤⣴⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡘⢹⠄           ⣼⡟⠋⣀⣼⣾⣶⣶⣦⣤⣤⣴⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡘⢹⠄\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⡟⠄⢰⣿⣿⣿⣿⣿⣿⣿⠈⠈⣿⣿⣿⣿⡋⠉⣻⣿⣿⣿⣿⣿⣿⣿⡄⠘⣇           ⡟⠄⢰⣿⣿⣿⣿⣿⣿⣿⠈⠈⣿⣿⣿⣿⡋⠉⣻⣿⣿⣿⣿⣿⣿⣿⡄⠘⣇\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⠁⠄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⢵⣽⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠄⢹           ⠁⠄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⢵⣽⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠄⢹\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⠄⢀⣾⣿⣿⣿⣿⣿⣿⣿⡿⠋⣿⣿⣿⣿⣿⠉⠻⠿⣿⣿⣿⣿⣿⣿⣿⣇⠄           ⠄⢀⣾⣿⣿⣿⣿⣿⣿⣿⡿⠋⣿⣿⣿⣿⣿⠉⠻⠿⣿⣿⣿⣿⣿⣿⣿⣇⠄\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⠄⢰⣿⣿⡿⠿⠟⠋⠉⠄⠄⠈⣿⣿⣿⣿⡏⢀⣤⣤⣄⣀⣀⣀⡈⠉⢻⣿⠄           ⠄⢰⣿⣿⡿⠿⠟⠋⠉⠄⠄⠈⣿⣿⣿⣿⡏⢀⣤⣤⣄⣀⣀⣀⡈⠉⢻⣿⠄\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⡄⢸⣯⣥⡴⠒⢊⡁ 🧿 ⢸⣿⣿⣿⣿⣦⠈⠁ 🧿 ⣆⠈⣁⣈⣿⣿⡴         ⡄⢸⣯⣥⡴⠒⢊⡁ ⭕ ⢸⣿⣿⣿⣿⣦⠈⠁ ⭕ ⣆⠈⣁⣈⣿⣿⡴\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⣿⢸⣿⣿⣿⣿⣶⣶⣿⣶⣡⣼⣿⣿⣿⣿⣿⢿⣆⣤⣾⣬⣭⣵⣶⣿⣿⣿⣿           ⣿⢸⣿⣿⣿⣿⣶⣶⣿⣶⣡⣼⣿⣿⣿⣿⣿⢿⣆⣤⣾⣬⣭⣵⣶⣿⣿⣿⣿\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⠄⢻⡟⣩⣾⣿⣿⣿⠏⠿⡿⢿⡿⠿⠯⠎⠉⠙⠻⣿⣿⣿⡿⢖⣀⣀⠄⣼⠄           ⠄⢻⡟⣩⣾⣿⣿⣿⠏⠿⡿⢿⡿⠿⠯⠎⠉⠙⠻⣿⣿⣿⡿⢖⣀⣀⠄⣼⠄\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⢀⠘⣷⣿⢿⣿⣿⣿⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢸⣿⠿⠟⠋⠁⣴⣿⠏⠄           ⢀⠘⣷⣿⢿⣿⣿⣿⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢸⣿⠿⠟⠋⠁⣴⣿⠏⠄\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⠄⠄⠘⣿⣷⣌⠙⠻⢿⣷⣶⣤⣤⣤⣀⣠⡤⠞⡋⡍⠄⠂⠄⠄⣼⣿⠃⠄⠄           ⠄⠄⠘⣿⣷⣌⠙⠻⢿⣷⣶⣤⣤⣤⣀⣠⡤⠞⡋⡍⠄⠂⠄⠄⣼⣿⠃⠄⠄\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⠄⠄⠄⠄⢸⣿⣦⠄⠘⣿⡁⣾⣹⡍⣁⠐⡆⡇⠁⡌⠄⠄⠄⣰⣿⠇⠄⠄⠄           ⠄⠄⠄⠄⢸⣿⣦⠄⠘⣿⡁⣾⣹⡍⣁⠐⡆⡇⠁⡌⠄⠄⠄⣰⣿⠇⠄⠄⠄\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⠄⠄⠄⠄⠄⠈⣿⣿⣷⡹⢹⠸⢣⢈⠘⡇⠘⠈⠄⠁⠄⠄⣼⣿⣿⠃⣰⠄⠄           ⠄⠄⠄⠄⠄⠈⣿⣿⣷⡹⢹⠸⢣⢈⠘⡇⠘⠈⠄⠁⠄⠄⣼⣿⣿⠃⣰⠄⠄\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⠄⠄⠄⠄⠄⣷⠘⣿⣿⣷⡀⠄⠸⢿⣿⡏⣾⠓⠃⠄⠄⢀⡟⣿⠏⣰⣿⣷⠄           ⠄⠄⠄⠄⠄⣷⠘⣿⣿⣷⡀⠄⠸⢿⣿⡏⣾⠓⠃⠄⠄⢀⡟⣿⠏⣰⣿⣷⠄\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⠄⠄⣠⣿⣿⣿⣷⠙⣿⣿⣷⡀⠄⠈⠄⠄⠄⠄⠄⠄⣠⡞⣼⡿⢀⣿⣿⣿⣷           ⠄⠄⣠⣿⣿⣿⣷⠙⣿⣿⣷⡀⠄⠈⠄⠄⠄⠄⠄⠄⣠⡞⣼⡿⢀⣿⣿⣿⣷\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- ⠄⣼⣿⣿⣿⣿⣿⣷⠈⠿⣝⣿⣿⣦⣤⣭⣥⣤⣤⣶⣾⠿⠋⢀⣼⣿⣿             ⠄⣼⣿⣿⣿⣿⣿⣷⠈⠿⣝⣿⣿⣦⣤⣭⣥⣤⣤⣶⣾⠿⠋⢀⣼⣿⣿\r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 372 " + server.getUsers().at(fd).getNickname() + " :- \r\n");
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 376 " + server.getUsers().at(fd).getNickname() + " :End of /MOTD command\r\n");
};


void Command::PRIVMSG(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp_user(buffer.substr(0, buffer.find(' ')));
    buffer.erase(0, buffer.find(" :") + 2);
    std::string tmp_msg(buffer.substr(0, buffer.find("\r\n")));

    std::map<int, User>::iterator it = server.getUsers().begin();

    if (tmp_user[0] != '#'){
        while (it != server.getUsers().end()){
            if (it->second.getNickname() == tmp_user)
                break;
            it++;
        }
        if (it == server.getUsers().end()){
            reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 401 " + server.getUsers().at(fd).getNickname() + " " + tmp_user + " :No such nick/channel\r\n");
        }
    }

    if (tmp_user[0] == '#'){
        std::vector<Channel>::iterator it = server.getChannels().begin();

        while (it != server.getChannels().end()){
            if (it->getChannelName() == tmp_user)
                break;
            it++;
        }
        if (it == server.getChannels().end()){
            reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 401 " + server.getUsers().at(fd).getNickname() + " " + tmp_user + " :No such nick/channel\r\n");
            return ;
        }
        std::vector<std::string>::iterator it2 = it->getUserList().begin();
        for (; it2 != it->getUserList().end(); it2++){
            if (*it2 == server.getUsers().at(fd).getNickname())
                break;
        }
        if (it2 == it->getUserList().end()){
            reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 404 " + server.getUsers().at(fd).getNickname() + " " + tmp_user + " :Cannot send to channel\r\n");
            return;
        }
        for (std::vector<int>::iterator ite = it->getFdList().begin(); ite != it->getFdList().end(); ite++){
            if (*ite != fd)
                reply(*ite, ":" + server.getUsers().at(fd).getFullHostname() + " PRIVMSG " + tmp_user + " :" + tmp_msg + "\r\n");
        }
    }
    else {//if (buffer[0] != 1){
        for (std::map<int, User>::iterator it = server.getUsers().begin(); it != server.getUsers().end(); it++){
            if (it->second.getNickname() == tmp_user){
                if (server.getUsers().at(it->first).getIsAway() == true){
                    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 301 " + server.getUsers().at(fd).getNickname() + " :" + server.getUsers().at(it->first).getAwayMsg() + "\r\n");
                }
                reply(it->first, ":" + server.getUsers().at(fd).getFullHostname() + " PRIVMSG " + tmp_user + " :" + tmp_msg + "\r\n");
                break ;
            }
        }
    }
};



void Command::NAMES(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};
void Command::NCTCP(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};


void Command::NOTICE(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp_user(buffer.substr(0, buffer.find(' ')));

    std::map<int, User>::iterator it = server.getUsers().begin();

    while (it != server.getUsers().end()){
        if (it->second.getNickname() == tmp_user)
            break;
        it++;
    }
    reply(it->first, ":" + server.getUsers().at(fd).getFullHostname() + " NOTICE " + buffer + "\r\n");
};

void Command::NOTIFY(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;}; // notify list empty

void Command::OPER(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    buffer.erase(0, buffer.find(' ') + 1);
    if (buffer == "admin\r\n"){
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 381 " + server.getUsers().at(fd).getNickname() + " :You are now an IRC operator\r\n");
        std::string mode = server.getUsers().at(fd).getUserMode();
        if (server.getUsers().at(fd).getUserMode().find('o') == std::string::npos)
            server.getUsers().at(fd).setUserMode(server.getUsers().at(fd).getUserMode() + 'o');
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 221 " + server.getUsers().at(fd).getNickname() + " +" + server.getUsers().at(fd).getUserMode() + "\r\n");
    }
    else
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 464 " + server.getUsers().at(fd).getNickname() + " :Password incorrect\r\n");
};


void Command::PART(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string serv_name(buffer.substr(0, buffer.find("\r\n")));

    std::vector<Channel>::iterator it = server.getChannels().begin();
    for (; it != server.getChannels().end(); it++){
        if (it->getChannelName() == serv_name)
            break;
    }
    if (it == server.getChannels().end()){
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 401 " + server.getUsers().at(fd).getNickname() + " " + serv_name + " :No such nick/channel\r\n");
        return ;
    }
    for (std::vector<int>::iterator ite = it->getFdList().begin(); ite != it->getFdList().end(); ite++){
        reply(*ite, ":" + server.getUsers().at(fd).getFullHostname() + " PART " + serv_name + "\r\n");
    }
    std::vector <int> tmp_fd = it->getFdList();
    std::vector <std::string> tmp_user = it->getUserList();
    for (size_t i = 0; i < tmp_fd.size(); i++){
        if (tmp_fd[i] == fd){
            it->getFdList().erase(it->getFdList().begin() + i);
            it->getUserList().erase(it->getUserList().begin() + i);
            break;
        }
    }
    if (it->getFdList().empty())
        server.getChannels().erase(it);
};


void Command::PING(std::string buffer, int fd, Server & server ){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string toSend(":" + server.getUsers().at(fd).getFullHostname() + " PONG :" + buffer);
    send(fd, toSend.c_str(), toSend.length(), 0);
    if (DEBUG)
        std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend << RESET;
};

void Command::QUIT(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string leave_msg(buffer.substr(0, buffer.find("\r\n")));

    server.getUsers().at(fd).setIsConnected(false);
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " QUIT :QUIT " + leave_msg + "\r\n");
};

void Command::REHASH(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;}; // ??

void Command::RESTART(std::string , int , Server & server){
    (void)server;
};

void Command::SCONNECT(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};
void Command::SERVLIST(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};
void Command::SETHOST(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};
void Command::SILENCE(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};
void Command::SQUERY(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};
void Command::SQUIT(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};
void Command::STATS(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};


void Command::TIME(std::string , int fd, Server & server){
    std::time_t time = std::time(NULL);
    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 391 " + server.getUsers().at(fd).getNickname() + " ClownRC :" + std::asctime(std::localtime(&time)) + "\r\n");
};

void Command::TOPIC(std::string buffer, int fd,  Server & server){

    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name(buffer.substr(0, buffer.find(" ")));
    buffer.erase(0, buffer.find(' ') + 1);

    std::string toFind = chan_name;
    if (chan_name[0] != '#'){
        std::string toFind = "#" + chan_name;
    }  
    std::vector<Channel>::iterator it = server.getChannels().begin();

    while (it != server.getChannels().end()){
        if (it->getChannelName() == toFind)
            break;
        it++;
    }
    if (it == server.getChannels().end()){
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 442 " + server.getUsers().at(fd).getNickname() + " " + chan_name + " :You're not on that channel\r\n");
        return;
    }

    reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " TOPIC " + chan_name + " " + buffer);
    it->clearTopic();
    it->setTopic(buffer);
};


void Command::TRACE(std::string , int , Server & server){
    (void)server;
};

void Command::UNBAN(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};
void Command::UNSILENCE(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};

void Command::USERHOST(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};



void Command::WALLOPS(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string msg(buffer.substr(0, buffer.find(" ")));
    if (server.getUsers().at(fd).getUserMode().find("o") == std::string::npos){
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 481 " + server.getUsers().at(fd).getNickname() + " :Permission Denied- You're not an IRC operator\r\n");
        return ;
    }

    for (std::map<int, User>::iterator it = server.getUsers().begin(); it != server.getUsers().end(); it++){
        if (it->second.getUserMode().find("w") != std::string::npos)
            reply(it->first, ":" + server.getUsers().at(fd).getFullHostname() + " WALLOPS " + msg);
    }
};


void Command::WHO(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp(buffer.substr(0, buffer.find("\r\n")));

    if (tmp[0] == '#'){
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 315 " + server.getUsers().at(fd).getNickname() + " " + server.getUsers().at(fd).getUsername() + " :End of /WHO list\r\n");
    }
};


void Command::WHOIS(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp(buffer.substr(0, buffer.find(" ")));
    std::string toFind(tmp.substr(0, tmp.find("\r\n")));
    (void)fd;
    for (std::map<int, User>::iterator it = server.getUsers().begin(); it != server.getUsers().end(); it++){
        if (it->second.getUsername() == toFind){
            reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 311 " + server.getUsers().at(fd).getNickname() + " " + toFind + " " + it->second.getHostname() + " * :" + it->second.getRealName() + "\r\n");
            return;
        }
    }
};


void Command::WHOWAS(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};

void Command::PASS(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    server.getUsers().at(fd).setPassword(buffer.substr(0, buffer.find("\r\n")));
    return;
}


void Command::NICK(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    buffer = buffer.substr(0, buffer.find("\r\n"));
    if (buffer.find('\b') != std::string::npos || buffer.find('\r') != std::string::npos
        || buffer.find('@') != std::string::npos || buffer.find('\0') != std::string::npos || buffer.find(' ') != std::string::npos){
            reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " 432 " + server.getUsers().at(fd).getNickname() + " :Nickname " + buffer + " is invalid !\r\n");
            return ;
    }
    for (std::map<int, User >::iterator it = server.getUsers().begin() ; it != server.getUsers().end(); it++){
        if (it->second.getNickname() == buffer){
            reply(fd, ": 433 * " + buffer + " :Nickname is already in use\r\n");
            return ;
        }
    }
    if (server.getUsers().at(fd).getNickname().empty()){
        server.getUsers().at(fd).setNickname(buffer);
        reply(fd, ": NICK " + buffer + "\r\n");
    }
    else{
        reply(fd, ":" + server.getUsers().at(fd).getFullHostname() + " NICK :" + buffer + "\r\n");
        server.getUsers().at(fd).setNickname(buffer);
    }
    return;
}


void Command::USER(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    server.getUsers().at(fd).setUsername(buffer.substr(0, buffer.find(' ')));
    buffer.erase(0, buffer.find(' ') + 1);
    //c'est quoi ? <mode> ?
    buffer.erase(0, buffer.find(' ') + 1);
    //server.getUsers().at(fd).setHostname(buffer.substr(0, buffer.find(" :")));
    buffer.erase(0, buffer.find(" :") + 2);
    server.getUsers().at(fd).setRealName(buffer.substr(0, buffer.find("\r\n")));
    if (DEBUG){
       ;
    }
    return;
}

Command::Command(void){
    _commandsFilled["PING"] = PING;
    _commandsFilled["MODE"] = MODE;
    _commandsFilled["PASS"] = PASS;
    _commandsFilled["NICK"] = NICK;
    _commandsFilled["USER"] = USER;
    _commandsFilled["PRIVMSG"] = PRIVMSG;
    _commandsFilled["JOIN"] = JOIN;
    _commandsFilled["WHO"] = WHO;
    _commandsFilled["PART"] = PART;
    _commandsFilled["QUIT"] = QUIT;
    _commandsFilled["motd"] = MOTD;
    _commandsFilled["admin"] = ADMIN;
    _commandsFilled["info"] = INFO;
    _commandsFilled["AWAY"] = AWAY;
    _commandsFilled["ACCEPT"] = ACCEPT;
    _commandsFilled["NOTICE"] = NOTICE;
    _commandsFilled["time"] = TIME;
    _commandsFilled["die"] = DIE;
    _commandsFilled["restart"] = RESTART;
    _commandsFilled["TOPIC"] = TOPIC;
    _commandsFilled["LIST"] = LIST;
    _commandsFilled["trace"] = TRACE;
    _commandsFilled["WHOIS"] = WHOIS;
    _commandsFilled["OPER"] = OPER;
    _commandsFilled["kill"] = KILL;
    _commandsFilled["KICK"] = KICK;
    _commandsFilled["INVITE"] = INVITE;
    _commandsFilled["wallops"] = WALLOPS;
};

Command::~Command(void){

};