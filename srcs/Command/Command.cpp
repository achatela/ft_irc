#include "../../includes/Command.hpp"

void Command::reply(std::string cmd, int fd, std::string msg){
    std::cout << YELLOW << cmd << MAGENTA << ">>" << CYAN <<  "[" << fd << "] " << BLUE << msg << RESET;
}

void Command::ACCEPT(std::string, int fd, std::map<int, User > &, std::vector<Channel> &){
    std::string toSend("Unknown command: ACCEPT\r\n");
    send(fd, toSend.c_str(), toSend.length(), 0);

    if (DEBUG)
        reply("ACCEPT", fd, toSend);
};


// void Command::ACTION(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::ADMIN(std::string, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    std::string toSendFirst(":" + Users.at(fd).getFullHostname() + " 256 " + Users.at(fd).getNickname() + " ClownRC " + ":Administrative info\r\n");
    std::string toSendSecond(":" + Users.at(fd).getFullHostname() + " 257 " + Users.at(fd).getNickname() + " :You're on ClownRC, our server is hosted in France and is accesible with the following url FAUT QUON LA SET\r\n"); //URL a define
    std::string toSendThird(":" + Users.at(fd).getFullHostname() + " 258 " + Users.at(fd).getNickname() + " :If you need any information relating our project fell free to contact us\r\n");
    std::string toSendForth(":" + Users.at(fd).getFullHostname() + " 259 " + Users.at(fd).getNickname() + " :<achatela@student.42.fr>, <hcarpent@student.42.fr>\r\n");

    send(fd, toSendFirst.c_str(), toSendFirst.length(), 0);
    send(fd, toSendSecond.c_str(), toSendSecond.length(), 0);
    send(fd, toSendThird.c_str(), toSendThird.length(), 0);
    send(fd, toSendForth.c_str(), toSendForth.length(), 0);

    if (DEBUG){
        reply("ADMIN", fd, toSendFirst);
        reply("ADMIN", fd, toSendSecond);
        reply("ADMIN", fd, toSendThird);
        reply("ADMIN", fd, toSendForth);
    }
};


// void Command::ALIAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::AWAY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 2);
    std::string away_msg(buffer.substr(0, buffer.find("\r\n")));

    std::string toSend(":" + Users.at(fd).getFullHostname() + " 306 " + Users.at(fd).getNickname() + " :You have been marked as begin away\r\n");
    send(fd, toSend.c_str(), toSend.length(), 0);
    Users.at(fd).setIsAway(true);
    Users.at(fd).setAwayMsg(away_msg);
    if (DEBUG){
        reply("AWAY", fd, toSend);
        reply("AWAY", fd, Users.at(fd).getAwayMsg());
    }
};


void Command::BAN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::BEEP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::BIND(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::CAT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::CD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::CHANNEL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::CLEAR(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::COMPLETION(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::CONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::CTCP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::CYCLE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::DCC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::DEOP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::DEVOICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::DEHILIGHT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::DISCONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::ECHO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::EVAL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::EXEC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::FLUSHBUFFER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::FOREACH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::FORMAT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::HASH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::HELP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::HILIGHT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::IGNORE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::INFO(std::string, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    std::string debug_str;
    std::string toSend(":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :------------------INFO------------------\r\n"); //URL a define
    send(fd, toSend.c_str(), toSend.length(), 0);

    debug_str += toSend;
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :Server name ClownRC / URL A DEFINE\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);

    debug_str += toSend;
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :Version : 1.0\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);

    debug_str += toSend;
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :Made by the two original clowns:\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);

    debug_str += toSend;
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :- achatela <achatela@student.42.fr>\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);

    debug_str += toSend;
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :- hcarpent <hcarpent@student.42.fr>\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);

    debug_str += toSend;
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + ":\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);

    debug_str += toSend;
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :Thanks for using ClownRC !\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);

    debug_str += toSend;
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 374 " + Users.at(fd).getNickname() + " :End of /INFO list\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    debug_str += toSend;
    if (DEBUG)
        reply("INFO", fd, debug_str);
};


void Command::INVITE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::IRCNET(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::ISO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::JOIN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name(buffer.substr(0, buffer.find("\r\n")));
    std::vector<Channel>::iterator it = channels.begin();
    for (; it != channels.end(); it++){
        if (it->getChannelName() == chan_name){
            std::string toSen(":" + Users.at(fd).getFullHostname() + " JOIN :" + chan_name + "\r\n");
            std::vector <int> tmp_vec = it->getFdList();
            for (size_t i = 0; i < tmp_vec.size(); i++){
                send(tmp_vec[i], toSen.c_str(), toSen.length(), 0); // envoyer le putain 
            }
            break;
        }
    }
    if (it == channels.end()){
        channels.push_back(Channel());
        channels.back().setChannelName(chan_name);
        it = channels.end() - 1;
    }
    it->pushFdList(fd); // protéger si l'user n'a pas les droits
    it->getUserList().push_back(Users.at(fd).getNickname());
    std::string toSend(":" + Users.at(fd).getFullHostname() + " 353 " + Users.at(fd).getNickname() + " = " + chan_name + " :@");
    for (std::vector<std::string>::iterator ite = it->getUserList().begin() ; ite != it->getUserList().end(); ite++){
        toSend += *ite;
        if (it->getUserList().end() - ite != 1){
            toSend += " ";
        }
    }
    toSend += "\r\n";
    std::string toSend2(":" + Users.at(fd).getFullHostname() + " 366 " + Users.at(fd).getNickname() + " " + chan_name + " :End of /NAMES list" + "\r\n");
    std::string toSend3(":" + Users.at(fd).getFullHostname() + " JOIN :" + chan_name + "\r\n");
    send(fd, toSend.c_str(), toSend.length(), 0);
    send(fd, toSend2.c_str(), toSend2.length(), 0);
    send(fd, toSend3.c_str(), toSend3.length(), 0);
    if (DEBUG){
        reply("JOIN", fd, toSend);
        reply("JOIN", fd, toSend2);
        reply("JOIN", fd, toSend3);
    }
    //confirmation que l'user à join
    //envoyé le topic (RPL_TOPIC)
    //Envoyer liste user a celui qui join (RPL_NAMREPLY)
    //it->addUsername
};


void Command::KICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::KICKBAN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::KILL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::KNOCK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::KNOCKOUT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::LASTLOG(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::LAYOUT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::LINKS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::LIST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::LOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::LASTLOGLUSERS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::MAP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::ME(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::MIRCDCC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::MODE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp(buffer.substr(0, buffer.find(" ")));
    if (buffer.find(' ') != std::string::npos)
        buffer.erase(0, buffer.find(' ') + 1);
    if (tmp[0] == '#'){
        std::string flags(buffer.substr(0, buffer.find(" ")));
        size_t space_num = 0;
        Channel check;
        int j = getChannel(tmp, channels);
        if (j == -1){
            std::cout << "not existing" << std::endl;
            return ;
        }
        else
            check = channels.at(j);
        if (flags[0] != '#'){
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
            // 
            for(; i <= space_num; i++){
                if (username[i][0] == '+')
                    break;
                tmp_send.clear();
                if (!check.isInUserList(username[i])){
                    tmp_send += ":" + Users.at(fd).getFullHostname() + " 441 " + Users.at(fd).getNickname() + " " + tmp + " :User not on the channel\r\n";
                    send(fd, tmp_send.c_str(), tmp_send.length(), 0);
                    if (DEBUG)
                       reply("MODE", fd, tmp_send);
                }
                else{
                    tmp_send += ":" + Users.at(fd).getFullHostname() + " 324 " + Users.at(fd).getNickname() + " " + tmp + " +" + flags[i + 1] + " " + username[i] + "\r\n";
                    std::cout << i << ":" << " " << tmp_send << std::endl;
                    send(fd, tmp_send.c_str(), tmp_send.length(), 0);
                    if (DEBUG)
                       reply("MODE", fd, tmp_send);
                }
            }
            if (i < flags.size() - 1){
                ;
            }
        }
        std::string toSend(":" + Users.at(fd).getFullHostname() + " 324 " + Users.at(fd).getNickname() + " " + tmp + " +n\r\n"); // suspect il faut enlever le \n en plein milieu
        std::cout << "to send = " << toSend << std::endl;
        send(fd, toSend.c_str(), toSend.length(), 0);
    }
};


void Command::MOTD(std::string, int fd, std::map<int, User > & Users, std::vector<Channel> &){ // changer (ouvrir un fichier conf/ircd.motd)
    std::string toSendFirst(":" + Users.at(fd).getFullHostname() + " 375 " + Users.at(fd).getNickname() + " :- ClownRC Message of the day\r\n");
    send(fd, toSendFirst.c_str(), toSendFirst.length(), 0);


    std::string toSend(":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :-           achatela                                hcarpent" "\r\n");
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⣼⡟⠋⣀⣼⣾⣶⣶⣦⣤⣤⣴⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡘⢹⠄          ⠄⢹⡘⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣾⣶⣶⣶⣴⣤⣤⣦⣶⣶⣾⣼⣀⠋⡟⣼\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⡟⠄⢰⣿⣿⣿⣿⣿⣿⣿⠈⠈⣿⣿⣿⣿⡋⠉⣻⣿⣿⣿⣿⣿⣿⣿⡄⠘⣇          ⣇⠘⡄⣿⣿⣿⣿⣿⣿⣿⣻⠉⡋⣿⣿⣿⣿⠈⠈⣿⣿⣿⣿⣿⣿⣿⢰⠄⡟\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠁⠄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⢵⣽⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠄⢹          ⢹⠄⣧⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣽⢵⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⠄⠁\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⢀⣾⣿⣿⣿⣿⣿⣿⣿⡿⠋⣿⣿⣿⣿⣿⠉⠻⠿⣿⣿⣿⣿⣿⣿⣿⣇⠄          ⠄⣇⣿⣿⣿⣿⣿⣿⣿⠿⠻⠉⣿⣿⣿⣿⣿⠋⡿⣿⣿⣿⣿⣿⣿⣿⣾⢀⠄\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⢰⣿⣿⡿⠿⠟⠋⠉⠄⠄⠈⣿⣿⣿⣿⡏⢀⣤⣤⣄⣀⣀⣀⡈⠉⢻⣿⠄          ⠄⣿⢻⠉⡈⣀⣀⣀⣄⣤⣤⢀⡏⣿⣿⣿⣿⠈⠄⠄⠉⠋⠟⠿⡿⣿⣿⢰⠄\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⡄⢸⣯⣥⡴⠒⢊⡁ ⭕ ⢸⣿⣿⣿⣿⣦⠈⠁ ⭕ ⣆⠈⣁⣈⣿⣿⡴        ⡴⣿⣿⣈⣁⠈⣆ 🌀 ⠁⠈⣦⣿⣿⣿⣿⢸ 🌀 ⡁⢊⠒⡴⣥⣯⢸⡄\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⣿⢸⣿⣿⣿⣿⣶⣶⣿⣶⣡⣼⣿⣿⣿⣿⣿⢿⣆⣤⣾⣬⣭⣵⣶⣿⣿⣿⣿          ⣿⣿⣿⣿⣶⣵⣭⣬⣾⣤⣆⢿⣿⣿⣿⣿⣿⣼⣡⣶⣿⣶⣶⣿⣿⣿⣿⢸⣿\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⢻⡟⣩⣾⣿⣿⣿⠏⠿⡿⢿⡿⠿⠯⠎⠉⠙⠻⣿⣿⣿⡿⢖⣀⣀⠄⣼⠄          ⠄⣼⠄⣀⣀⢖⡿⣿⣿⣿⠻⠙⠉⠎⠯⠿⡿⢿⡿⠿⠏⣿⣿⣿⣾⣩⡟⢻⠄\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⢀⠘⣷⣿⢿⣿⣿⣿⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢸⣿⠿⠟⠋⠁⣴⣿⠏⠄          ⠄⠏⣿⣴⠁⠋⠟⠿⣿⢸⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⡀⣿⣿⣿⢿⣿⣷⠘⢀\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⠄⠘⣿⣷⣌⠙⠻⢿⣷⣶⣤⣤⣤⣀⣠⡤⠞⡋⡍⠄⠂⠄⠄⣼⣿⠃⠄⠄          ⠄⠄⠃⣿⣼⠄⠄⠂⠄⡍⡋⠞⡤⣠⣀⣤⣤⣤⣶⣷⢿⠻⠙⣌⣷⣿⠘⠄⠄\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⠄⠄⠄⢸⣿⣦⠄⠘⣿⡁⣾⣹⡍⣁⠐⡆⡇⠁⡌⠄⠄⠄⣰⣿⠇⠄⠄⠄          ⠄⠄⠄⠇⣿⣰⠄⠄⠄⡌⠁⡇⡆⠐⣁⡍⣹⣾⡁⣿⠘⠄⣦⣿⢸⠄⠄⠄⠄\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⠄⠄⠄⠄⠈⣿⣿⣷⡹⢹⠸⢣⢈⠘⡇⠘⠈⠄⠁⠄⠄⣼⣿⣿⠃⣰⠄⠄          ⠄⠄⣰⠃⣿⣿⣼⠄⠄⠁⠄⠈⠘⡇⠘⢈⢣⠸⢹⡹⣷⣿⣿⠈⠄⠄⠄⠄⠄\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⠄⠄⠄⠄⣷⠘⣿⣿⣷⡀⠄⠸⢿⣿⡏⣾⠓⠃⠄⠄⢀⡟⣿⠏⣰⣿⣷⠄          ⠄⣷⣿⣰⠏⣿⡟⢀⠄⠄⠃⠓⣾⡏⣿⢿⠸⠄⡀⣷⣿⣿⠘⣷⠄⠄⠄⠄⠄\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⠄⣠⣿⣿⣿⣷⠙⣿⣿⣷⡀⠄⠈⠄⠄⠄⠄⠄⠄⣠⡞⣼⡿⢀⣿⣿⣿⣷          ⣷⣿⣿⣿⢀⡿⣼⡞⣠⠄⠄⠄⠄⠄⠄⠈⠄⡀⣷⣿⣿⠙⣷⣿⣿⣿⣠⠄⠄\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⣼⣿⣿⣿⣿⣿⣷⠈⠿⣝⣿⣿⣦⣤⣭⣥⣤⣤⣶⣾⠿⠋⢀⣼⣿⣿            ⣿⣿⣼⢀⠋⠿⣾⣶⣤⣤⣥⣭⣤⣦⣿⣿⣝⠿⠈⣷⣿⣿⣿⣿⣿⣼⠄\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);
    toSend.clear();
    toSend += ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- " "\r\n";
    send(fd, toSend.c_str(), toSend.length(), 0);

    std::string toSendLast(":" + Users.at(fd).getFullHostname() + " 376 " + Users.at(fd).getNickname() + " :End of /MOTD command\r\n");
    send(fd, toSendLast.c_str(), toSendLast.length(), 0);
    if (DEBUG){
        reply("MOTD", fd, toSendFirst);
        reply("MOTD", fd, toSendLast);
    }
};



void Command::PRIVMSG(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp_user(buffer.substr(0, buffer.find(' ')));
    buffer.erase(0, buffer.find(" :") + 2);
    std::string tmp_msg(buffer.substr(0, buffer.find("\r\n")));

    std::map<int, User>::iterator it = Users.begin();

    if (tmp_user[0] != '#'){
        while (it != Users.end()){
            if (it->second.getNickname() == tmp_user)
                break;
            it++;
        }
        if (it == Users.end()){
            std::string tmp_error(":" + Users.at(fd).getFullHostname() + " 401 " + Users.at(fd).getNickname() + " " + tmp_user + " :No such nick/channel\r\n");
            send(fd, tmp_error.c_str(), tmp_error.length(), 0);
            if (DEBUG){
                reply("PRIVMSG", fd, tmp_error);
            }
        }
    }

    if (tmp_user[0] == '#'){
        std::string toSend2(":" + Users.at(fd).getFullHostname() + " PRIVMSG " + tmp_user + " :" + tmp_msg + "\r\n");
        std::vector<Channel>::iterator it = channels.begin();

        while (it != channels.end()){
            if (it->getChannelName() == tmp_user)
                break;
            it++;
        }
        if (it == channels.end()){
            std::cout << "possible ? " << std::endl;
        }

        std::vector<int> list_fd = it->getFdList();

        size_t i = 0;
        while (i != list_fd.size()){
            if (list_fd[i] != fd)
                send(list_fd[i], toSend2.c_str(), toSend2.length(), 0); // envoyer à tous les fd
            i++;
        }
        if (DEBUG){
            reply("PRIVMSG", fd, toSend2);
        }
    }
    else {//if (buffer[0] != 1){
        for (std::map<int, User>::iterator it = Users.begin(); it != Users.end(); it++){
            if (it->second.getNickname() == tmp_user){
                if (Users.at(it->first).getIsAway() == true){
                    std::string tmp(":" + Users.at(it->first).getFullHostname() + " 301 " + Users.at(fd).getNickname() + " " + tmp_user + " :" + Users.at(it->first).getAwayMsg() + "\r\n");
                    send(fd, tmp.c_str(), tmp.length(), 0);
                }
                std::string toSend(":" + Users.at(fd).getFullHostname() + " PRIVMSG " + tmp_user +  " :" + tmp_msg + "\r\n");
                std::cout << "to send = " << toSend << std::endl;
                send(it->first, toSend.c_str(), toSend.length(), 0);
                break ;
            }
        }
    }
};



void Command::NAMES(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::NCTCP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::NETSPLIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::NETWORK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
//void Command::NICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (voidfd; (void)Users, (void)channels; return;};


void Command::NOTICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    std::string toSend(":" + Users.at(fd).getFullHostname() + " " + buffer + "\r\n");

    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp_user(buffer.substr(0, buffer.find(' ')));

    std::map<int, User>::iterator it = Users.begin();

    while (it != Users.end()){
        if (it->second.getNickname() == tmp_user)
            break;
        it++;
    }

    send(it->first, toSend.c_str(), toSend.length(), 0);

    if (DEBUG){
        reply("NOTICE", fd, toSend);
    }
};


void Command::NOTIFY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::OP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::OPER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::PART(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string serv_name(buffer.substr(0, buffer.find("\r\n")));

    std::vector<Channel>::iterator it = channels.begin();
    for (; it != channels.end(); it++){
        std::cout << it->getChannelName() << std::endl;
        if (it->getChannelName() == serv_name)
            break;
    }
    if (it == channels.end()){
        std::cout << "CHANNEL CAN'T BE DELETED" << std::endl;
        return ;
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
    std::string toSend(":" + Users.at(fd).getFullHostname() + " PART " + serv_name + "\r\n");
    send(fd, toSend.c_str(), toSend.length(), 0);
    std::cout << toSend << std::endl;
    std::vector <int> tmp_fd2 = it->getFdList();
    for (size_t i = 0; i < tmp_fd2.size(); i++){
            send(tmp_fd2[i], toSend.c_str(), toSend.length(), 0);
    }
    if (it->getFdList().empty())
        channels.erase(it);
};


void Command::PING(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels;return ;};
void Command::QUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::QUIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string leave_msg(buffer.substr(0, buffer.find("\r\n")));

    std::string toSend(":" + Users.at(fd).getFullHostname() + " QUIT :QUIT " + leave_msg + "\r\n");
    Users.at(fd).setIsConnected(false);
    send(fd, toSend.c_str(), toSend.length(), 0);
    if (DEBUG)
        reply("QUIT", fd, toSend);
};


void Command::QUOTE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::RAWLOG(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::RECODE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::RECONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::REDRAW(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::REHASH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::RELOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::RESIZE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::RESTART(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::RMRECONNS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::RMREJOINS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SAVE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SCONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SCRIPT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SCROLLBACK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SERVER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SERVLIST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SET(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SETHOST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SILENCE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SQUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SQUIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::STATS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::STATUSBAR(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::TIME(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::TOGGLE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::TOPIC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::TRACE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::TS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UNALIAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UNBAN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UNIGNORE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UNLOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UNNOTIFY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UNQUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UNSILENCE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UPGRADE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UPTIME(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::USERHOST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::VER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::VERSION(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::VOICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::WAIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::WALL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::WALLOPS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::WHO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp(buffer.substr(0, buffer.find("\r\n")));

    if (tmp[0] == '#'){
        std::string toSend(":" + Users.at(fd).getFullHostname() + " 315 " + Users.at(fd).getNickname() + " " + Users.at(fd).getUsername() + " :End of /WHO list\r\n");
        send(fd, toSend.c_str(), toSend.length(), 0);
    }
};


void Command::WHOIS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::WHOWAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::WINDOW(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};

void Command::PASS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 1);
    Users.at(fd).setPassword(buffer.substr(0, buffer.find("\r\n")));
    // if (Users.at(fd).getPassword()[Users.at(fd).getPassword().length() - 1] == '\r')
    //     Users.at(fd).getPassword().erase(0, Users.at(fd).getPassword().end() - 1);
    if (Users.at(fd).getPassword() != Users.at(fd).getRealPassword())
        Users.at(fd).setAccess(FORBIDDEN);
    if (DEBUG)
    ;
        // std::cout << "password: " << Users.at(fd).getPassword() << std::endl;
    return;
}


void Command::NICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 1);
    buffer = buffer.substr(0, buffer.find("\r\n"));
    if (buffer.find('\b') != std::string::npos || buffer.find('\r') != std::string::npos
        || buffer.find('@') != std::string::npos || buffer.find('\0') != std::string::npos || buffer.find(' ') != std::string::npos){
            std::string toSend(":" + Users.at(fd).getFullHostname() + " 432 " + Users.at(fd).getNickname() +  " :Nickname " + buffer + " is invalid !\r\n");
            send(fd, toSend.c_str(), toSend.length(), 0);
            return ;
    }
    for (std::map<int, User >::iterator it = Users.begin() ; it != Users.end(); it++){
        if (it->second.getNickname() == buffer){
            std::string toSend(": 433 * " + buffer + " :Nickname is already in use\r\n");
            send(fd, toSend.c_str(), toSend.length(), 0);
            if (DEBUG)
                reply("NICK", fd, toSend);
            return ;
        }
    } 
    Users.at(fd).setNickname(buffer);
    std::string toSend2(": NICK :" + buffer + "\r\n");
    send(fd, toSend2.c_str(), toSend2.length(), 0);
    if (DEBUG)
        reply("NICK", fd, toSend2);
    return;
}


void Command::USER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 1);
    Users.at(fd).setUsername(buffer.substr(0, buffer.find(' ')));
    buffer.erase(0, buffer.find(' ') + 1);
    //c'est quoi ? <mode> ?
    buffer.erase(0, buffer.find(' ') + 1);
    //Users.at(fd).setHostname(buffer.substr(0, buffer.find(" :")));
    buffer.erase(0, buffer.find(" :") + 2);
    Users.at(fd).setRealName(buffer.substr(0, buffer.find("\r\n")));
    // if (Users.at(fd).getUsername()[Users.at(fd).getUsername().length() - 1] == '\r')
    //     Users.at(fd).getUsername().erase(0, Users.at(fd).getUsername().end() - 1);
    // if (Users.at(fd).getRealName()[Users.at(fd).getRealName().length() - 1] == '\r')
    //     Users.at(fd).getRealName().erase(0, Users.at(fd).getRealName().end() - 1);
    if (DEBUG){
        // std::cout << "username: " << Users.at(fd).getUsername() << std::endl;
        // std::cout << "hostname: " << Users.at(fd).getHostname() << std::endl;
        // std::cout << "real_name: " << Users.at(fd).getRealName() << std::endl;
    }
    if ((Users.at(fd).getBuffer().empty() || Users.at(fd).getHostname().empty() || Users.at(fd).getNickname().empty()
        ||  Users.at(fd).getPassword().empty() || Users.at(fd).getRealName().empty() || Users.at(fd).getUsername().empty()))
        Users.at(fd).setAccess(FORBIDDEN);
    else{
        if (Users.at(fd).getRealPassword().empty())
            Users.at(fd).setAccess(AUTHORIZED);
        else{
            if (Users.at(fd).getPassword() != Users.at(fd).getRealPassword()){
                Users.at(fd).setAccess(FORBIDDEN);
            }
            else
                Users.at(fd).setAccess(AUTHORIZED);
        }
    }
    if (Users.at(fd).getAccess() == AUTHORIZED){

        // std::map<int, User >::iterator it = Users.begin();
        // for (; it != Users.end(); it++){
        //     if (it->first != fd && it->second.getFullInfo() == Users.at(fd).getFullInfo())
        //         break;
        // }
        // if (it != Users.end()){
        //     if (it->second.getIsConnected() == true){
        //         std::string toSend(":" + Users.at(fd).getFullHostname() + " 432 " + Users.at(fd).getNickname() +  " :Nickname " + Users.at(fd).getNickname() + " is already in use !\r\n");
        //         send(fd, toSend.c_str(), toSend.length(), 0);
        //         Users.at(fd).setAccess(FORBIDDEN);
        //         return ;
        //     }
        //     else
        //         std::cout << "User disconncted" << std::endl;
        // }

        std::string toSend(":" + Users.at(fd).getFullHostname() + " 001 " + Users.at(fd).getNickname() +  " :Welcome to the Internet Relay Network " + Users.at(fd).getNickname() + " ! " + Users.at(fd).getUsername() + "@" + "\r\n" + Users.at(fd).getHostname() + "\r\n");
        send(fd, toSend.c_str(), toSend.length(), 0);
        // std::cout << toSend << std::endl;
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
};

Command::~Command(void){

};