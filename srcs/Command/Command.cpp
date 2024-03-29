#include "../../includes/Command.hpp"
#include "../../includes/Server.hpp"

void Command::reply(int atFd, Server & server, int fd, std::string toSend){
    server.getUsers().at(atFd).getToSend() += toSend;
    server.getUsers().at(atFd).getFdToSend().push_back(fd);
    if (std::find(server.getAtFd().begin(), server.getAtFd().end(), atFd) == server.getAtFd().end())
        server.getAtFd().push_back(atFd);
    // send(fd, toSend.c_str(), toSend.length(), 0);
}

void Command::ACCEPT(std::string, int fd, Server & server){
    reply(fd, server, fd, "Unsupported command: ACCEPT\r\n");
};

void Command::ADMIN(std::string, int fd, Server & server){
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 256 " + server.getUsers().at(fd).getNickname() + " ClownRC :Administrative info\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 257 " + server.getUsers().at(fd).getNickname() + " :You're on ClownRC, our server is hosted in France and is accesible with the following url " + server.getHostname() + "\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 258 " + server.getUsers().at(fd).getNickname() + " :If you need any information relating our project fell free to contact us\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 259 " + server.getUsers().at(fd).getNickname() + " :<achatela@student.42.fr>, <hcarpent@student.42.fr>\r\n");
};

void Command::AWAY(std::string buffer, int fd, Server & server){
    bool empty = false;
    if (buffer.size() == 6)
        empty = true;
    buffer.erase(0, buffer.find(' ') + 2);
    std::string away_msg(buffer.substr(0, buffer.find("\r\n")));

    if (!empty){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 306 " + server.getUsers().at(fd).getNickname() + " :You have been marked as begin away\r\n");
        server.getUsers().at(fd).setIsAway(true);
        server.getUsers().at(fd).setAwayMsg(away_msg);
        return ;
    }
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 305 " + server.getUsers().at(fd).getNickname() + " :You are no longer marked as being away\r\n");
    server.getUsers().at(fd).setIsAway(false);
    server.getUsers().at(fd).getAwayMsg().clear();
};


void Command::DIE(std::string, int fd, Server & server){
    if (server.getUsers().at(fd).getUserMode().find('o') == std::string::npos){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 481 " + server.getUsers().at(fd).getNickname() + " :Permission Denied- You're not an IRC operator\r\n");
        return;
    }
    server.setStatus(OFF);
};

void Command::INFO(std::string, int fd, Server & server){
    std::string debug_str;
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371" + server.getUsers().at(fd).getNickname() + " :------------------INFO------------------\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :Server name ClownRC / URL A DEFINE\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :Version : 1.0\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371" + server.getUsers().at(fd).getNickname() + " :Made by the two original clowns:\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :- achatela <achatela@student.42.fr>\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :- hcarpent <hcarpent@student.42.fr>\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 371 " + server.getUsers().at(fd).getNickname() + " :Thanks for using ClownRC !\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 374 " + server.getUsers().at(fd).getNickname() + " :End of /INFO list\r\n");
};

void Command::INVITE(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string nickname = buffer.substr(0, buffer.find(" "));
    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name(buffer);
    chan_name.erase(chan_name.end() - 2, chan_name.end());
    int fd_invited;
    std::map<int, User>::iterator it = server.getUsers().begin();
    for (; it != server.getUsers().end(); it++){
        if (nickname == it->second.getNickname()){
            fd_invited = it->first;
            break;
        }
    }
    if (it == server.getUsers().end()){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 401 " + server.getUsers().at(fd).getNickname() + " " + nickname + " :No such nick/channel\r\n");
        return ;
    }

    std::vector<Channel>::iterator it_chan = server.getChannels().begin();
    std::vector<Channel>::iterator it_chan_end = server.getChannels().end();
    for (; it_chan != it_chan_end; it_chan++){
        if (it_chan->getChannelName() == chan_name)
            break;
    }
    if (it_chan == it_chan_end){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 401 " + server.getUsers().at(fd).getNickname() + " " + nickname + " :No such nick/channel\r\n");
        return ;
    }

    std::vector<int>::iterator it_fd = it_chan->getFdList().begin();
    std::vector<int>::iterator it_fd_end = it_chan->getFdList().end();
    for (; it_fd != it_fd_end; it_fd++){
        if (*it_fd == fd)
            break;
    }
    if (it_fd == it_fd_end){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 442 " + server.getUsers().at(fd).getNickname() + " " + chan_name + " :You are not on channel\r\n");
        return ;
    }

    std::vector<std::string>::iterator it_userIn = it_chan->getUserList().begin();
    std::vector<std::string>::iterator it_userIn_end = it_chan->getUserList().end();
    for (; it_userIn != it_userIn_end; it_userIn++){
        if (*it_userIn == nickname){
            reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 443 " + server.getUsers().at(fd).getNickname() + " " + nickname + " " + chan_name + " :User is already on channel\r\n");
            return;
        }
    }

    reply(fd, server, fd_invited, ":" + server.getUsers().at(fd).getFullHostname() + " INVITE " + nickname + " " + chan_name + "\r\n");
    std::vector<int>::iterator it_fd_end2 = it_chan->getFdList().end();
    for (std::vector<int>::iterator it_fd = it_chan->getFdList().begin(); it_fd != it_fd_end2; it_fd++){
        reply(fd, server, *it_fd, ":" + server.getUsers().at(fd).getFullHostname() + " 341 " + server.getUsers().at(fd).getNickname() + " " + chan_name + " " + nickname + "\r\n");
    }

    it_chan->getPending().push_back(nickname);
}


void Command::ISO(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 2);
    std::string tmp(buffer.substr(0, buffer.find(" ")));
    std::string toFind(tmp.substr(0, tmp.find("\r\n")));

    std::map<int, User>::iterator it_end = server.getUsers().end();
    for (std::map<int, User>::iterator it = server.getUsers().begin(); it != it_end; it++){
        if (it->second.getNickname() == toFind){
            reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 303 " + server.getUsers().at(fd).getNickname() + " :" + toFind + "\r\n");
        }
    }
};

void Command::JOIN(std::string buffer, int fd,  Server & server){
    // No ERR_BADCHANNELKEY because we don't handle +k channel mode
    // No ERR_CHANNELISFULL because we don't handle +l channel mode
    if (buffer.size() <= 7){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 461 " + server.getUsers().at(fd).getNickname() + " KILL :Not enough parameters\r\n");
        return ;
    }
    std::string fullHostName = server.getUsers().at(fd).getFullHostname();
    std::string nickname = server.getUsers().at(fd).getNickname();
    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name(buffer.substr(0, buffer.find("\r\n")));
    std::vector<Channel>::iterator it = server.getChannels().begin();
    std::vector<Channel>::iterator it_end = server.getChannels().end();

    for (; it != it_end; it++){
        if (it->getChannelName() == chan_name){
            if (it->getChannelMode().find('i') != std::string::npos){

                std::list<std::string>::iterator it_pend = it->getPending().begin();
                std::list<std::string>::iterator it_pend_end = it->getPending().end();

                for (; it_pend != it_pend_end; it_pend++){
                    if (*it_pend == nickname)
                        break;
                }
                if (it_pend == it_pend_end){
                    reply(fd, server, fd, ":" + fullHostName + " 473 " +  nickname + " " + chan_name + " :You are not invited on this channel\r\n");
                    return;
                }
                it->getPending().erase(it_pend);
            }

            std::string username = server.getUsers()[fd].getUsername();
            std::vector<std::string>::iterator it2_end = it->getBanList().end();

            for (std::vector<std::string>::iterator it2 = it->getBanList().begin(); it2 != it2_end; it2++){
                if ("*!*" + username + "@*" + server.getUsers()[fd].getDomainName() + "\r\n" == *it2){
                    reply(fd, server, fd, ":" + fullHostName + " 474 " +  nickname + " " + chan_name + " :You are banned from this channel\r\n");
                    return;
                }
            }

            std::vector<int>::iterator ite_end = it->getFdList().end();
            for (std::vector<int>::iterator ite = it->getFdList().begin(); ite != ite_end; ite++){
                reply(fd, server, *ite, ":" + fullHostName + " JOIN :" + chan_name + "\r\n");
            }
            break;
        }
    }
    if (it == server.getChannels().end()){
        server.getChannels().push_back(Channel());
        server.getChannels().back().setChannelName(chan_name);
        it = server.getChannels().end() - 1;
        it->getUserMode()[fd] += "o";
        it->getChannelMode() += "n";
    }
    else
        it->getUserMode()[fd] += "w";
    if (server.getUsers().at(fd).getUserMode().find("o") != std::string::npos)
        it->getUserMode()[fd] += "o";
    // for (std::vector<std::string>::iterator it2 = it->getBanList().begin(); it2 != it->getBanList().end(); it2++){
    //     if ("*!*" + server.getUsers()[fd].getUsername() + "@*" + server.getUsers()[fd].getDomainName() + "\r\n" == *it2){
    //         reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 474 " +  server.getUsers().at(fd).getNickname() + " " + chan_name + " :You are banned from this channel\r\n");
    //         return;
    //     }
    // }
    it->pushFdList(fd);
    it->getUserList().push_back(nickname);
    std::string msg = "";
    std::vector<int>::iterator it2 = it->getFdList().begin();
    std::vector<std::string>::iterator ite_end = it->getUserList().end();

    for (std::vector<std::string>::iterator ite = it->getUserList().begin() ; ite != ite_end; ite++){
        if (it->getUserMode().at(*it2).find("o") != std::string::npos)
            msg += "@";
        msg += *ite;
        if (ite_end - ite != 1){
            msg += " ";
        }
        it2++;
    }
    reply(fd, server, fd, ":" + fullHostName + " 353 " + nickname + " = " + chan_name + " :" + msg + "\r\n");
    reply(fd, server, fd, ":" + fullHostName + " 366 " +nickname + " " + chan_name + " :End of /NAMES list\r\n");
    reply(fd, server, fd, ":" + fullHostName + " JOIN " + chan_name + "\r\n");
};


void Command::KICK(std::string buffer, int fd,  Server & server){
    //
    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name =  buffer.substr(0, buffer.find(' '));
    buffer.erase(0, buffer.find(' ') + 1);
    std::string nickname =  buffer.substr(0, buffer.find(' '));
    std::vector<Channel>::iterator it = server.getChannels().begin();
    std::vector<Channel>::iterator it_end = server.getChannels().end();
    std::string nickname2 = server.getUsers().at(fd).getNickname();
    std::string hostname = server.getUsers().at(fd).getFullHostname();

    for (; it != it_end; it++){
        if (it->getChannelName() == chan_name)
            break;
    }
    if (it == it_end){// a check
        reply(fd, server, fd, ":" + hostname + " 401 " + nickname2 + " " + nickname + " :No such nick/channel\r\n");
        return;
    }

    std::vector<std::string>::iterator it2 = it->getUserList().begin();
    std::vector<std::string>::iterator it_end2 = it->getUserList().end();
    for (; it2 != it_end2; it2++){
        if (*it2 == nickname)
            break;
    }
    if (it2 == it_end2){// a check
        reply(fd, server, fd, ":" + hostname + " 401 " + nickname2 + " " + nickname + " :No such nick/channel\r\n");
        return;
    }

    if (server.getUsers().at(fd).getUserMode().find("o") == std::string::npos && it->getUserMode().at(fd).find("o") == std::string::npos){ // check if he's chan op too
        reply(fd, server, fd, ":" + hostname + " 482 " + nickname2 + " " + chan_name + " :You're not channel operator\r\n");
        return ;
    }

    std::vector<int>::iterator it3 = it->getFdList().begin();
    for (; it3 != it->getFdList().end(); it3++){
        reply(fd, server, *it3, ":" + hostname + " KICK " + chan_name + " " + nickname + " :\r\n");
    }
    it2 = it->getUserList().begin();
    it3 = it->getFdList().begin();
    for (; it2 != it_end2; it2++, it3++){
        if (*it2 == nickname){
            it->getUserList().erase(it2);
            it->getFdList().erase(it3);
            break;
        }
    }
    if (it->getUserList().empty())
        server.getChannels().erase(it);

};

void Command::KILL(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string nickname =  buffer.substr(0, buffer.find(' '));
    buffer.erase(0, buffer.find(' ') + 1);
    std::string hostname = server.getUsers().at(fd).getFullHostname();
    std::string nickname2 = server.getUsers().at(fd).getNickname();

    if (buffer == ":\r\n"){
        reply(fd, server, fd, ":" + hostname + " 461 " + nickname2 + " KILL :Not enough parameters\r\n");
        return;
    }
    if (server.getUsers().at(fd).getUserMode().find('o') == std::string::npos){
        reply(fd, server, fd, ":" + hostname + " 481 " + nickname2 + " :Permission Denied- You're not an IRC operator\r\n");
        return;
    }

    std::map<int, User>::iterator it_end = server.getUsers().end();

    for (std::map<int, User>::iterator it = server.getUsers().begin(); it != it_end; it++){
        if (it->second.getNickname() == nickname){
            reply(fd, server, it->first, ":" + hostname + " KILL " + buffer);
            reply(fd, server, it->first, ":" + it->second.getFullHostname() + " QUIT " + buffer);

            std::vector<pollfd>::iterator it2_end = server.getPfds().end();
            int fdToFind = it->first;
            for (std::vector<pollfd>::iterator it2 = server.getPfds().begin(); it2 != it2_end; it2++){
                if (it2->fd == fdToFind){
                    close(it2->fd);
                    server.getPfds().erase(it2);
                    server.getUsers().erase(it);
                    return;
                }
            }
        }
    }
    reply(fd, server, fd, ":" + hostname + " 401 " + nickname2 + " " + nickname + " :No such nick/channel\r\n");
};

void Command::LINKS(std::string, int fd,  Server & server){
    reply(fd, server, fd, "Unsupported command: LINKS\r\n");
};


void Command::LIST(std::string buffer, int fd,  Server & server){
    //Format is fullhostname 322 username #chan_name (nb users) :(topic)
    //then fullhostname 323 username :End of /LIST

    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name(buffer.substr(0, buffer.find(" ")));
    std::string cmp_name(chan_name.substr(0, chan_name.find("\r\n")));
    std::stringstream stream;
    std::string hostname = server.getUsers().at(fd).getFullHostname();
    std::string username = server.getUsers().at(fd).getUsername();

    if ((chan_name[0] == '\r' && chan_name[1] == '\n') || buffer.size() != chan_name.size()){
        std::vector<Channel>::iterator it_end = server.getChannels().end();
        for (std::vector<Channel>::iterator it = server.getChannels().begin(); it != it_end; it++){
            stream << it->getFdList().size();
            reply(fd, server, fd, ":" + hostname + " 322 " + username + " " + it->getChannelName() + " " + stream.str() + " " + it->getTopic() + "\r\n");
            stream.str("");
        }
    }
    else{
        std::vector<Channel>::iterator it = server.getChannels().begin();
        std::vector<Channel>::iterator it_end2 = server.getChannels().end();
        for (; it != it_end2; it++){
            if (it->getChannelName() == cmp_name){
                stream << it->getFdList().size();
                reply(fd, server, fd, ":" + hostname + " 322 " + username + " " + it->getChannelName() + " " + stream.str() + " " + it->getTopic() + "\r\n");
                break;
            }
        }
        if (it == it_end2){
            reply(fd, server, fd, ":" + hostname + " 402 " + username + " " + cmp_name + " :No such server\r\n");
            return ;
        }
    }
    reply(fd, server, fd, ":" + hostname + " 323 " + username + " :End of /LIST\r\n");
};

void Command::MAP(std::string, int fd,  Server & server){
    reply(fd, server, fd, "Unsupported command: MAP\r\n");
};

void Command::MODE(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp;

    std::string hostname = server.getUsers().at(fd).getFullHostname();
    std::string nickname = server.getUsers().at(fd).getNickname();

    if (buffer.find(" ") == std::string::npos)
        tmp = buffer.substr(0, buffer.find("\r\n"));
    else
        tmp = buffer.substr(0, buffer.find(" "));
    if (buffer.find(' ') != std::string::npos)
        buffer.erase(0, buffer.find(' ') + 1);


    if (tmp[0] == '#'){
        std::string flags(buffer.substr(0, buffer.find(" ")));
        size_t space_num = 0;

        std::vector<Channel>::iterator it = server.getChannels().begin();
        std::vector<Channel>::iterator it_end = server.getChannels().end();

        for (; it != it_end; it++){
            if (it->getChannelName() == tmp)
                break;
        }
        if (it == it_end)
            return ;

        std::string channelName = it->getChannelName();

        if (server.getUsers().at(fd).getUserMode().find("o") == std::string::npos){
            std::vector<std::string>::iterator it5 = it->getUserList().begin();
            std::vector<std::string>::iterator it5_end = it->getUserList().end();

            for(; it5 != it5_end; it5++){
                if (*it5 == nickname){
                    break;
                }
            }
            if (it5 == it5_end){
                reply(fd, server, fd, ":" + hostname + " 441 " + nickname + " " + it->getChannelName() + " :User not on the channel\r\n");
                return ;
            }
        }
        if (flags == buffer && (buffer.substr(0, buffer.find("\r\n")) != "+i" && buffer.substr(0, buffer.find("\r\n")) != "-i"))
        {
            reply(fd, server, fd, ":" + hostname + " 324 " + nickname + " " + tmp + " +" + it->getChannelMode() + "\r\n");
            return;
        }

        if (flags[0] != '#'){
            if (buffer.substr(0, buffer.find(' ')) == "+b"){
                std::string toFind = server.getUsers().at(fd).getUserMode();
                std::map<int, std::string>::iterator tmp_it = it->getUserMode().begin();
                std::map<int, User>::iterator tmp_it2;
                std::string flagban = buffer.substr(0, buffer.find("\r\n"));

                if (flagban[3] != '*'){
                    return ;
                }
                else if (toFind.find("o") == std::string::npos){

                    std::map<int, std::string>::iterator tmp_it_end = it->getUserMode().end();
                    for(; tmp_it != tmp_it_end; tmp_it++){
                        if (fd == tmp_it->first){
                            if (tmp_it->second.find("o") == std::string::npos){
                                reply(fd, server, fd, ":" + hostname + " 482 " + nickname + " " + channelName + " :You're not channel operator\r\n");
                                return ;
                            }
                        }
                    }
                }
                it->getBanList().push_back(buffer.substr(3, buffer.find("\r\n")));

                std::vector<int>::iterator it3_end = it->getFdList().end();

                for (std::vector<int>::iterator it3 = it->getFdList().begin(); it3 != it3_end; it3++){
                    reply(fd, server, *it3, ":" + hostname + " 324 " + nickname + " " + tmp + " " + flagban + "\r\n");
                }
                return;
            }
            
            else if (buffer.substr(0, buffer.find(' ')) == "+o"){
                std::string toFind = server.getUsers().at(fd).getUserMode();
                std::map<int, std::string>::iterator tmp_it = it->getUserMode().begin();
                std::map<int, User>::iterator tmp_it2;

                std::string flag_op = buffer.substr(0, buffer.find("\r\n"));

                if (toFind.find("o") == std::string::npos){
                    std::map<int, std::string>::iterator tmp_it_end2 = it->getUserMode().end();
                    for(; tmp_it != tmp_it_end2; tmp_it++){
                        if (fd == tmp_it->first){
                            if (tmp_it->second.find("o") == std::string::npos){
                                reply(fd, server, fd, ":" + hostname + " 482 " + nickname + " " + channelName + " :You're not channel operator\r\n");
                                return ;
                            }
                        }
                    }
                }

                std::string toPromote = buffer.substr(3, buffer.find("\r\n"));
                std::vector<std::string>::iterator it8 = it->getUserList().begin();
                toPromote.erase(toPromote.end() - 2, toPromote.end());
                int h = 0;
                std::vector<std::string>::iterator it8_end = it->getUserList().end();

                for (; it8 != it8_end; it8++){
                    if (*it8 == toPromote){
                        if (it->getUserMode().at(it->getFdList()[h]).find("o") == std::string::npos)
                            it->getUserMode().at(it->getFdList()[h]) += "o";
                        
                        std::vector<int>::iterator it3_end = it->getFdList().end();
                        for (std::vector<int>::iterator it3 = it->getFdList().begin(); it3 != it3_end; it3++){
                            reply(fd, server, *it3, ":" + hostname + " 324 " + nickname + " " + tmp + " " + flag_op + "\r\n");
                        }
                        return ;
                    }
                    h++;
                }
                reply(fd, server, fd, ":" + hostname + " 441 " + nickname + " " + toPromote + " :User not on the channel\r\n");
                return;
            }

            else if (buffer.substr(0, buffer.find(' ')) == "-o"){
                std::string toFind = server.getUsers().at(fd).getUserMode();
                std::map<int, std::string>::iterator tmp_it = it->getUserMode().begin();
                std::map<int, std::string>::iterator tmp_it_end3 = it->getUserMode().end();
                std::map<int, User>::iterator tmp_it2;
                std::string flag_op = buffer.substr(0, buffer.find("\r\n"));

                if (toFind.find("o") == std::string::npos){
                    for(; tmp_it != tmp_it_end3; tmp_it++){
                        if (fd == tmp_it->first){
                            if (tmp_it->second.find("o") == std::string::npos){
                                reply(fd, server, fd, ":" + hostname + " 482 " + nickname + " " + channelName + " :You're not channel operator\r\n");
                                return ;
                            }
                        }
                    }
                }

                std::string toRemove = buffer.substr(3, buffer.find("\r\n"));
                std::vector<std::string>::iterator it8 = it->getUserList().begin();
                toRemove.erase(toRemove.end() - 2, toRemove.end());
                int h = 0;
                std::vector<std::string>::iterator it8_end2 = it->getUserList().end();

                for (; it8 != it8_end2; it8++){
                    if (*it8 == toRemove){
                        if (it->getUserMode().at(it->getFdList()[h]).find("o") != std::string::npos)
                            it->getUserMode().at(it->getFdList()[h]).erase(it->getUserMode().at(it->getFdList()[h]).find("o"));
                        // std::cout << it->getUserMode().at(it->getFdList()[h]) << std::endl;

                        std::vector<int>::iterator it3_end2 = it->getFdList().end();
                        for (std::vector<int>::iterator it3 = it->getFdList().begin(); it3 != it3_end2; it3++){
                            reply(fd, server, *it3, ":" + hostname + " 324 " + nickname + " " + tmp + " " + flag_op + "\r\n");
                        }
                        return ;
                    }
                    h++;
                }
                reply(fd, server, fd, ":" + hostname + " 441 " + nickname + " " + toRemove + " :User not on the channel\r\n");
                return;
            }

            else if (buffer.substr(0, buffer.find("\r\n")) == "+i"){
                if (it->getUserMode().at(fd).find("o") == std::string::npos && server.getUsers().at(fd).getUserMode().find("o") == std::string::npos){
                    reply(fd, server, fd, ":" + hostname + " 482 " + nickname + " " + channelName + " :You're not channel operator\r\n");
                    return ;
                }
                if (it->getChannelMode().find("i") == std::string::npos)
                    it->getChannelMode() += "i";
                reply(fd, server, fd, ":" + hostname + " 324 " + nickname + " " + tmp + " +" + it->getChannelMode() + "\r\n");
                return;
            }

            else if (buffer.substr(0, buffer.find("\r\n")) == "-i"){
                if (it->getUserMode().at(fd).find("o") == std::string::npos && server.getUsers().at(fd).getUserMode().find("o") == std::string::npos){
                    reply(fd, server, fd, ":" + hostname + " 482 " + nickname + " " + channelName + " :You're not channel operator\r\n");
                    return ;
                }
                if (it->getChannelMode().find("i") != std::string::npos)
                    //Check if user is operator
                    it->getChannelMode().erase(it->getChannelMode().find("i"));
                reply(fd, server, fd, ":" + hostname + " 324 " + nickname + " " + tmp + " +" + it->getChannelMode() + "\r\n");
                return;
            }

            buffer.erase(0, buffer.find(' ') + 1);
            size_t i = 0;
            for(; buffer[i] != '\r'; i++){
                if (buffer[i] == ' ' && buffer[i + 1] != '+')
                    space_num++;
            }
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
                if (!it->isInUserList(username[i])){
                    reply(fd, server, fd, ":" + hostname + " 441 " + nickname + " " + tmp + " :User not on the channel\r\n");
                }
                else{
                    reply(fd, server, fd, ":" + hostname + " 324 " + nickname + " " + tmp + " +" + flags[i + 1] + " " + username[i] + "\r\n");
                }
            }
            if (i < flags.size() - 1){
                ;
            }
        }
        reply(fd, server, fd, ":" + hostname + " 324 " + nickname + " " + tmp + " +" + it->getChannelMode() + "\r\n");
    }
    else{
        if (tmp != nickname && server.getUsers().at(fd).getUserMode().find('o') == std::string::npos){
            reply(fd, server, fd, ":" + hostname + " 502 " + nickname + " :Can't change mode for other users\r\n");
            return;
        }
        std::map<int, User>::iterator it = server.getUsers().begin();
        std::map<int, User>::iterator it_end4 = server.getUsers().end();

        for (; it != it_end4; it++){
            if (it->second.getNickname() == tmp)
                break;
        }
        if (it == it_end4){
            reply(fd, server, fd, ":" + hostname + " 401 " + nickname + " " + tmp + " :No such nick/channel\r\n");
            return;
        }

        if (buffer.find(' ') != std::string::npos)
            buffer = buffer.substr(0, buffer.find(' '));
        if (buffer.find('\r') != std::string::npos)
            buffer = buffer.substr(0, buffer.find('\r'));
        if (buffer[0] != '+' && buffer[0] != '-')
            buffer = '+' + buffer;

        size_t buff_size = buffer.size();
        for (size_t i = 1; i < buff_size; i++)//effacer les doublon et trouver les modes inconnus
        {
            if (buffer[i] != 'w' && buffer[i] != 'i' && buffer[i] != 'o'){
                reply(fd, server, fd, ":" + hostname + " 501 " + nickname + " :Unknown MODE flag\r\n");
                return;
            }

            size_t j = i + 1;
            while (j < buff_size)
            {
                if (buffer[i] == buffer[j]){
                    buffer.erase(j, 1);
                    buff_size = buffer.size();
                }
                else
                    ++j;
            }
        }

        if (buffer.find('o') != std::string::npos && server.getUsers().at(fd).getUserMode().find('o') == std::string::npos)
            buffer.erase(buffer.find('o'), 1);
        std::string mode = server.getUsers().at(fd).getUserMode();
        buff_size = buffer.size();
        if (buffer[0] == '+'){
            for (size_t i = 1; i < buff_size; i++){//ajouter des modes
                if (mode.find(buffer[i]) == std::string::npos)
                    mode += buffer[i];
            }
        }
        else{
            for (size_t i = 1; i < buff_size; i++){//enlever des modes
                if (mode.find(buffer[i]) != std::string::npos)
                    mode.erase(mode.find(buffer[i]), 1);
            }
        }
        server.getUsers().at(fd).setUserMode(mode);
        reply(fd, server, fd, ":" + hostname + " 221 " + nickname + " +" + server.getUsers().at(fd).getUserMode() + "\r\n");
    }

};


void Command::MOTD(std::string, int fd, Server & server){
    std::string hostname = server.getUsers().at(fd).getFullHostname();
    std::string nickname = server.getUsers().at(fd).getNickname();

    reply(fd, server, fd, ":" + hostname + " 375 " + nickname + " :- ClownRC Message of the day\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :-           achatela                                hcarpent\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⣼⡟⠋⣀⣼⣾⣶⣶⣦⣤⣤⣴⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡘⢹⠄           ⣼⡟⠋⣀⣼⣾⣶⣶⣦⣤⣤⣴⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡘⢹⠄\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⡟⠄⢰⣿⣿⣿⣿⣿⣿⣿⠈⠈⣿⣿⣿⣿⡋⠉⣻⣿⣿⣿⣿⣿⣿⣿⡄⠘⣇           ⡟⠄⢰⣿⣿⣿⣿⣿⣿⣿⠈⠈⣿⣿⣿⣿⡋⠉⣻⣿⣿⣿⣿⣿⣿⣿⡄⠘⣇\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⠁⠄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⢵⣽⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠄⢹           ⠁⠄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⢵⣽⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠄⢹\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⠄⢀⣾⣿⣿⣿⣿⣿⣿⣿⡿⠋⣿⣿⣿⣿⣿⠉⠻⠿⣿⣿⣿⣿⣿⣿⣿⣇⠄           ⠄⢀⣾⣿⣿⣿⣿⣿⣿⣿⡿⠋⣿⣿⣿⣿⣿⠉⠻⠿⣿⣿⣿⣿⣿⣿⣿⣇⠄\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⠄⢰⣿⣿⡿⠿⠟⠋⠉⠄⠄⠈⣿⣿⣿⣿⡏⢀⣤⣤⣄⣀⣀⣀⡈⠉⢻⣿⠄           ⠄⢰⣿⣿⡿⠿⠟⠋⠉⠄⠄⠈⣿⣿⣿⣿⡏⢀⣤⣤⣄⣀⣀⣀⡈⠉⢻⣿⠄\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⡄⢸⣯⣥⡴⠒⢊⡁ 🧿 ⢸⣿⣿⣿⣿⣦⠈⠁ 🧿 ⣆⠈⣁⣈⣿⣿⡴         ⡄⢸⣯⣥⡴⠒⢊⡁ ⭕ ⢸⣿⣿⣿⣿⣦⠈⠁ ⭕ ⣆⠈⣁⣈⣿⣿⡴\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⣿⢸⣿⣿⣿⣿⣶⣶⣿⣶⣡⣼⣿⣿⣿⣿⣿⢿⣆⣤⣾⣬⣭⣵⣶⣿⣿⣿⣿           ⣿⢸⣿⣿⣿⣿⣶⣶⣿⣶⣡⣼⣿⣿⣿⣿⣿⢿⣆⣤⣾⣬⣭⣵⣶⣿⣿⣿⣿\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⠄⢻⡟⣩⣾⣿⣿⣿⠏⠿⡿⢿⡿⠿⠯⠎⠉⠙⠻⣿⣿⣿⡿⢖⣀⣀⠄⣼⠄           ⠄⢻⡟⣩⣾⣿⣿⣿⠏⠿⡿⢿⡿⠿⠯⠎⠉⠙⠻⣿⣿⣿⡿⢖⣀⣀⠄⣼⠄\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⢀⠘⣷⣿⢿⣿⣿⣿⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢸⣿⠿⠟⠋⠁⣴⣿⠏⠄           ⢀⠘⣷⣿⢿⣿⣿⣿⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢸⣿⠿⠟⠋⠁⣴⣿⠏⠄\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⠄⠄⠘⣿⣷⣌⠙⠻⢿⣷⣶⣤⣤⣤⣀⣠⡤⠞⡋⡍⠄⠂⠄⠄⣼⣿⠃⠄⠄           ⠄⠄⠘⣿⣷⣌⠙⠻⢿⣷⣶⣤⣤⣤⣀⣠⡤⠞⡋⡍⠄⠂⠄⠄⣼⣿⠃⠄⠄\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⠄⠄⠄⠄⢸⣿⣦⠄⠘⣿⡁⣾⣹⡍⣁⠐⡆⡇⠁⡌⠄⠄⠄⣰⣿⠇⠄⠄⠄           ⠄⠄⠄⠄⢸⣿⣦⠄⠘⣿⡁⣾⣹⡍⣁⠐⡆⡇⠁⡌⠄⠄⠄⣰⣿⠇⠄⠄⠄\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⠄⠄⠄⠄⠄⠈⣿⣿⣷⡹⢹⠸⢣⢈⠘⡇⠘⠈⠄⠁⠄⠄⣼⣿⣿⠃⣰⠄⠄           ⠄⠄⠄⠄⠄⠈⣿⣿⣷⡹⢹⠸⢣⢈⠘⡇⠘⠈⠄⠁⠄⠄⣼⣿⣿⠃⣰⠄⠄\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⠄⠄⠄⠄⠄⣷⠘⣿⣿⣷⡀⠄⠸⢿⣿⡏⣾⠓⠃⠄⠄⢀⡟⣿⠏⣰⣿⣷⠄           ⠄⠄⠄⠄⠄⣷⠘⣿⣿⣷⡀⠄⠸⢿⣿⡏⣾⠓⠃⠄⠄⢀⡟⣿⠏⣰⣿⣷⠄\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⠄⠄⣠⣿⣿⣿⣷⠙⣿⣿⣷⡀⠄⠈⠄⠄⠄⠄⠄⠄⣠⡞⣼⡿⢀⣿⣿⣿⣷           ⠄⠄⣠⣿⣿⣿⣷⠙⣿⣿⣷⡀⠄⠈⠄⠄⠄⠄⠄⠄⣠⡞⣼⡿⢀⣿⣿⣿⣷\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- ⠄⣼⣿⣿⣿⣿⣿⣷⠈⠿⣝⣿⣿⣦⣤⣭⣥⣤⣤⣶⣾⠿⠋⢀⣼⣿⣿             ⠄⣼⣿⣿⣿⣿⣿⣷⠈⠿⣝⣿⣿⣦⣤⣭⣥⣤⣤⣶⣾⠿⠋⢀⣼⣿⣿\r\n");
    reply(fd, server, fd, ":" + hostname + " 372 " + nickname + " :- \r\n");
    reply(fd, server, fd, ":" + hostname + " 376 " + nickname + " :End of /MOTD command\r\n");
};


void Command::PRIVMSG(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp_user(buffer.substr(0, buffer.find(' ')));
    buffer.erase(0, buffer.find(" :") + 2);
    std::string tmp_msg(buffer.substr(0, buffer.find("\r\n")));
    std::string hostname = server.getUsers().at(fd).getFullHostname();
    std::string nickname = server.getUsers().at(fd).getNickname();

    std::map<int, User>::iterator it = server.getUsers().begin();

    if (tmp_user[0] != '#'){
        std::map<int, User>::iterator it_end = server.getUsers().end();
        while (it != it_end){
            if (it->second.getNickname() == tmp_user)
                break;
            it++;
        }
        if (it == it_end){
            reply(fd, server, fd, ":" + hostname + " 401 " + nickname + " " + tmp_user + " :No such nick/channel\r\n");
        }
    }

    if (tmp_user[0] == '#'){
        std::vector<Channel>::iterator it = server.getChannels().begin();
        std::vector<Channel>::iterator it_end2 = server.getChannels().end();

        while (it != it_end2){
            if (it->getChannelName() == tmp_user)
                break;
            it++;
        }
        if (it == it_end2){
            reply(fd, server, fd, ":" + hostname + " 401 " + nickname + " " + tmp_user + " :No such nick/channel\r\n");
            return ;
        }
        
        std::vector<std::string>::iterator it2_end = it->getBanList().end();
        std::string domainName = server.getUsers()[fd].getDomainName();
        std::string username2 = server.getUsers()[fd].getUsername();
        for (std::vector<std::string>::iterator it2 = it->getBanList().begin(); it2 != it2_end; it2++){
            if ("*!*" + username2 + "@*" + domainName + "\r\n" == *it2){
                reply(fd, server, fd, ":" + hostname + " 404 " +  nickname + " " + it->getChannelName() + " :You are banned from this channel\r\n");
                return;
            }
        }
        std::vector<std::string>::iterator it2 = it->getUserList().begin();
        std::vector<std::string>::iterator it2_end2 = it->getUserList().end();
        for (; it2 != it2_end2; it2++){
            if (*it2 == nickname)
                break;
        }
        if (it2 == it2_end2){
            reply(fd, server, fd, ":" + hostname + " 404 " + nickname + " " + tmp_user + " :Cannot send to channel\r\n");
            return;
        }

        std::vector<int>::iterator ite_end = it->getFdList().end();
        for (std::vector<int>::iterator ite = it->getFdList().begin(); ite != ite_end; ite++){
            if (*ite != fd)
                reply(fd, server, *ite, ":" + hostname + " PRIVMSG " + tmp_user + " :" + tmp_msg + "\r\n");
        }
    }
    else {
        std::map<int,User>::iterator it_end5 = server.getUsers().end();
        for (std::map<int, User>::iterator it = server.getUsers().begin(); it != it_end5; it++){
            if (it->second.getNickname() == tmp_user){
                reply(fd, server, it->first, ":" + hostname + " PRIVMSG " + tmp_user + " :" + tmp_msg + "\r\n");
                if (server.getUsers().at(it->first).getIsAway() == true){
                    reply(fd, server, fd, ":" + hostname + " 301 " + nickname + " " + tmp_user + " :" + server.getUsers().at(it->first).getAwayMsg() + "\r\n");
                }
                break ;
            }
        }
    }
};


void Command::NOTICE(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp_user(buffer.substr(0, buffer.find(' ')));

    std::map<int, User>::iterator it = server.getUsers().begin();
    std::map<int, User>::iterator it_end = server.getUsers().end();

    while (it != it_end){
        if (it->second.getNickname() == tmp_user)
            break;
        it++;
    }
    if (it == it_end){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 401 " + server.getUsers().at(fd).getNickname() + " " + tmp_user + " :No such nick/channel\r\n");
        return ;
    }
    reply(fd, server, it->first, ":" + server.getUsers().at(fd).getFullHostname() + " NOTICE " + buffer + "\r\n");
};


void Command::OPER(std::string buffer, int fd,  Server & server){
    if (buffer.size() <= 7){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 461 " + server.getUsers().at(fd).getNickname() + " OPER :Not enough parameters\r\n");
        return ;
    }
    buffer.erase(0, buffer.find(' ') + 1);
    buffer.erase(0, buffer.find(' ') + 1);
    if (server.getUsers().at(fd).getNickname() != "achatela" && server.getUsers().at(fd).getNickname() != "hcarpent"){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 491 " + server.getUsers().at(fd).getNickname() + " :Your nickname is not valid !\r\n");
        return ;
    }
    if (buffer == "admin\r\n"){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 381 " + server.getUsers().at(fd).getNickname() + " :You are now an IRC operator\r\n");
        std::string mode = server.getUsers().at(fd).getUserMode();
        if (server.getUsers().at(fd).getUserMode().find('o') == std::string::npos)
            server.getUsers().at(fd).setUserMode(server.getUsers().at(fd).getUserMode() + 'o');
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 221 " + server.getUsers().at(fd).getNickname() + " +" + server.getUsers().at(fd).getUserMode() + "\r\n");
    }
    else
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 464 " + server.getUsers().at(fd).getNickname() + " :Password incorrect\r\n");
};


void Command::PART(std::string buffer, int fd,  Server & server){
    if (buffer.size() <= 7){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 462 " + server.getUsers().at(fd).getNickname() + " PART :Not enough parameters\r\n");
        return ;
    }
    buffer.erase(0, buffer.find(' ') + 1);
    std::string serv_name(buffer.substr(0, buffer.find("\r\n")));

    std::vector<Channel>::iterator it = server.getChannels().begin();
    std::vector<Channel>::iterator it_end = server.getChannels().end();
    for (; it != it_end; it++){
        if (it->getChannelName() == serv_name)
            break;
    }
    if (it == it_end){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 403 " + server.getUsers().at(fd).getNickname() + " " + serv_name + " :No such channel\r\n");
        return ;
    }
    std::vector <std::string>::iterator tmp_it2 = it->getUserList().begin();
    std::vector<int>::iterator tmp_it = it->getFdList().begin();
    std::vector<int>::iterator tmp_it_end = it->getFdList().end();
    std::string hostname = server.getUsers().at(fd).getFullHostname();

    for (; tmp_it < tmp_it_end; tmp_it++){
        if (*tmp_it == fd){
            reply(fd, server, *tmp_it, ":" + hostname + " PART " + serv_name + "\r\n");
            it->getFdList().erase(tmp_it);
            it->getUserList().erase(tmp_it2);
            if (it->getFdList().empty()){
                server.getChannels().erase(it);
                return ;
            }
            else{
                for(std::vector<int>::iterator it2 = it->getFdList().begin(); it2 != tmp_it_end; it2++){
                    reply(fd, server, *it2, ":" + hostname + " PART " + serv_name + "\r\n");
                }
            }
            return ;
        }
        tmp_it2++;
    }
    if (tmp_it == tmp_it_end){
        reply(fd, server, fd, ":" + hostname + " 442 " + server.getUsers().at(fd).getNickname() + " " + serv_name + " :You're not on that channel\r\n");
        return ;
    }
};


void Command::PING(std::string buffer, int fd, Server & server ){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string toSend(":" + server.getUsers().at(fd).getFullHostname() + " PONG :" + buffer);
    reply(fd, server, fd, toSend.c_str());
    if (DEBUG)
        std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend << RESET;
};

void Command::QUIT(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string leave_msg(buffer.substr(0, buffer.find("\r\n")));

no_segfault:

    std::vector<Channel>::iterator it = server.getChannels().begin();
    std::vector<Channel>::iterator it_end = server.getChannels().end();
    size_t i = 0;
    for(; it != it_end; it++){
        i = 0;
        size_t i_max = it->getFdList().size();
        while (i < i_max){
            if (it->getFdList()[i] == fd){
                PART("PART " + it->getChannelName() + "\r\n", fd, server);
                goto no_segfault;
            }
            i++;
        }
    }

    server.getUsers().at(fd).setIsConnected(false);
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " QUIT :QUIT " + leave_msg + "\r\n");
};

void Command::REHASH(std::string, int fd,  Server & server){
    reply(fd, server, fd, "Unsupported command: REHASH\r\n");
};

void Command::RESTART(std::string , int , Server & server){
    server.setStatus(REBOOT);
};

void Command::SCONNECT(std::string , int fd,  Server & server){
    reply(fd, server, fd, "Unsupported command: SCONNECT\r\n");
};


void Command::SERVLIST(std::string, int fd,  Server & server){
    reply(fd, server, fd, "Unsupported command: SERVLIST\r\n");
};


void Command::SETHOST(std::string, int fd,  Server & server){
    reply(fd, server, fd, "Unknown command: SETHOST\r\n");
};


void Command::SILENCE(std::string, int fd,  Server & server){
    reply(fd, server, fd, "Unsupported command: SILENCE\r\n");
};


void Command::SQUERY(std::string, int fd,  Server & server){
    reply(fd, server, fd, "Unsupported command: SQUERY\r\n");
};


void Command::SQUIT(std::string, int fd,  Server & server){
    // Not handled because we don't have server links
    reply(fd, server, fd, "Unsupported command: SQUIT\r\n");
};


void Command::STATS(std::string, int fd,  Server & server){
    reply(fd, server, fd, "Unsupported command: SQUIT\r\n");
};


void Command::TIME(std::string , int fd, Server & server){
    std::time_t time = std::time(NULL);
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 391 " + server.getUsers().at(fd).getNickname() + " ClownRC :" + std::asctime(std::localtime(&time)) + "\r\n");
};

void Command::TOPIC(std::string buffer, int fd,  Server & server){
    if (buffer.size() <= 8){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 462 " + server.getUsers().at(fd).getNickname() + " TOPIC :Not enough parameters\r\n");
        return;
    }
    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name(buffer.substr(0, buffer.find(" ")));
    buffer.erase(0, buffer.find(' ') + 1);

    std::string toFind = chan_name;
    if (chan_name[0] != '#'){
        toFind = "#" + chan_name;
    }  
    std::vector<Channel>::iterator it = server.getChannels().begin();

    while (it != server.getChannels().end()){
        if (it->getChannelName() == toFind)
            break;
        it++;
    }
    if (it == server.getChannels().end()){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 442 " + server.getUsers().at(fd).getNickname() + " " + chan_name + " :You're not on that channel\r\n");
        return;
    }
    std::vector<std::string>::iterator it2 = it->getUserList().begin();
    for (; it2 != it->getUserList().end(); it2++){
        if (*it2 == server.getUsers().at(fd).getNickname()){
            break;
        }
    }
    if (it2 == it->getUserList().end()){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 442 " + server.getUsers().at(fd).getNickname() + " " + chan_name + " :You're not on that channel\r\n");
        return ;
    }

    for (std::vector<int>::iterator it_fd = it->getFdList().begin(); it_fd != it->getFdList().end(); it_fd++){
        reply(fd, server, *it_fd, ":" + server.getUsers().at(fd).getFullHostname() + " TOPIC " + chan_name + " " + buffer);
    }
    it->clearTopic();
    it->setTopic(buffer);
};


void Command::TRACE(std::string , int fd, Server & server){
    reply(fd, server, fd, "Unsupported command: TRACE\r\n");
};

void Command::UNBAN(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};
void Command::UNSILENCE(std::string buffer, int fd,  Server & server){(void)buffer; (void)fd; (void)server;    return;};


void Command::USERHOST(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp(buffer.substr(0, buffer.find(" ")));
    std::string toFind(tmp.substr(0, tmp.find("\r\n")));
    std::string userhost;
    std::string hostname = server.getUsers().at(fd).getFullHostname();
    std::string nickname = server.getUsers().at(fd).getNickname();
    std::map<int, User>::iterator it_end = server.getUsers().end();

    for (std::map<int, User>::iterator it = server.getUsers().begin(); it != it_end; it++){
        if (it->second.getNickname() == toFind){
            userhost = it->second.getUserHost();
            reply(fd, server, fd, ":" + hostname + " 302 " + nickname + " " + userhost + "\r\n");
        }
    }
};


void Command::WALLOPS(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string msg(buffer.substr(0, buffer.find(" ")));
    if (server.getUsers().at(fd).getUserMode().find("o") == std::string::npos){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 481 " + server.getUsers().at(fd).getNickname() + " :Permission Denied- You're not an IRC operator\r\n");
        return ;
    }

    std::string hostname = server.getUsers().at(fd).getFullHostname();
    std::map<int, User>::iterator it_end = server.getUsers().end();

    for (std::map<int, User>::iterator it = server.getUsers().begin(); it != it_end; it++){
        if (it->second.getUserMode().find("w") != std::string::npos)
            reply(fd, server, it->first, ":" + hostname + " WALLOPS " + msg);
    }
};


void Command::WHO(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp(buffer.substr(0, buffer.find("\r\n")));

    //à refaire
    
    if (tmp[0] == '#'){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 315 " + server.getUsers().at(fd).getNickname() + " " + server.getUsers().at(fd).getUsername() + " :End of /WHO list\r\n");
    }
};


void Command::WHOIS(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp(buffer.substr(0, buffer.find(" ")));
    std::string toFind(tmp.substr(0, tmp.find("\r\n")));
    std::map<int, User>::iterator it_end = server.getUsers().end();

    for (std::map<int, User>::iterator it = server.getUsers().begin(); it != it_end; it++){
        if (it->second.getNickname() == toFind){
            reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 311 " + server.getUsers().at(fd).getNickname() + " " + toFind + " " + it->second.getUsername() + " " + server.getUsers().at(fd).getHostname() + " * :" + it->second.getRealName() + "\r\n");
            reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 318 " + server.getUsers().at(fd).getNickname() + " " + toFind + " :End of /WHOIS list\r\n");
            return;
        }
    }

    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 401 " + server.getUsers().at(fd).getNickname() + " " + toFind + " :No such nick/channel\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 318 " + server.getUsers().at(fd).getNickname() + " " + toFind + " :End of /WHOIS list\r\n");
};


void Command::WHOWAS(std::string buffer, int fd,  Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp(buffer.substr(0, buffer.find(" ")));
    std::string toFind(tmp.substr(0, tmp.find("\r\n")));

    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 406 " + server.getUsers().at(fd).getNickname() + " " + toFind + " :There was no such nickname\r\n");
    reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 369 " + server.getUsers().at(fd).getNickname() + " " + toFind + " :End of /WHOWAS list\r\n");
};

void Command::PASS(std::string buffer, int fd, Server & server){
    if (buffer.size() <= 7){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 462 " + server.getUsers().at(fd).getNickname() + " PASS :Not enough parameters\r\n");
        return ;
    }
    if (!server.getUsers().at(fd).getPassword().empty()){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 462 " + server.getUsers().at(fd).getNickname() + " :Unauthorized command (already registered)\r\n");
        return ;
    }
    buffer.erase(0, buffer.find(' ') + 1);
    server.getUsers().at(fd).setPassword(buffer.substr(0, buffer.find("\r\n")));
    return;
}


void Command::NICK(std::string buffer, int fd, Server & server){
    // No ERR_NICKCOLLISION because we only have 1 server
    // No ERR_UNAVAILRESOURCE because we don't handle nick delay mechanism
    // No ERR_RESTRICTED because we don't handle +r usermode

    if (buffer.size() <= 7){
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 431 " + server.getUsers().at(fd).getNickname() + " :No nickname given\r\n");
        return ;
    }
    buffer.erase(0, buffer.find(' ') + 1);
    buffer = buffer.substr(0, buffer.find("\r\n"));
    if (buffer.find('\b') != std::string::npos || buffer.find('\r') != std::string::npos
        || buffer.find('@') != std::string::npos || buffer.find('\0') != std::string::npos || buffer.find(' ') != std::string::npos){
            reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " 432 " + server.getUsers().at(fd).getNickname() + " :Nickname " + buffer + " is invalid !\r\n");
            return ;
    }
    std::map<int, User >::iterator it_end = server.getUsers().end();
    for (std::map<int, User >::iterator it = server.getUsers().begin(); it != it_end; it++){
        if (it->second.getNickname() == buffer){
            reply(fd, server, fd, ": 433 * " + buffer + " :Nickname is already in use\r\n");
            return ;
        }
    }
    if (server.getUsers().at(fd).getNickname().empty()){
        server.getUsers().at(fd).setNickname(buffer);
        reply(fd, server, fd, ": NICK " + buffer + "\r\n");
    }
    else{
        reply(fd, server, fd, ":" + server.getUsers().at(fd).getFullHostname() + " NICK :" + buffer + "\r\n");
        server.getUsers().at(fd).setNickname(buffer);
    }
    return;
}


void Command::USER(std::string buffer, int fd, Server & server){
    buffer.erase(0, buffer.find(' ') + 1);
    server.getUsers().at(fd).setUsername(buffer.substr(0, buffer.find(' ')));
    buffer.erase(0, buffer.find(' ') + 1);
    buffer.erase(0, buffer.find(' ') + 1);
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
    _commandsFilled["WHOWAS"] = WHOWAS;
    _commandsFilled["wallops"] = WALLOPS;
    _commandsFilled["userhost"] = USERHOST;
    _commandsFilled["SETHOST"] = SETHOST;
    _commandsFilled["REHASH"] = REHASH;
    _commandsFilled["SERVLIST"] = SERVLIST;
    _commandsFilled["squit"] = SQUIT;
    _commandsFilled["squery"] = SQUERY;
    _commandsFilled["silence"] = SILENCE;
    _commandsFilled["stats"] = STATS;
    _commandsFilled["ison"] = ISO;
    _commandsFilled["map"] = MAP;
    _commandsFilled["links"] = LINKS;
    _commandsFilled["CONNECT"] = SCONNECT;
};

Command::~Command(void){

};