#include "../../includes/Command.hpp"

void Command::reply(int fd, std::string toSend){
    send(fd, toSend.c_str(), toSend.length(), 0);
    if (DEBUG)
        std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend << RESET;
}

void Command::ACCEPT(std::string, int fd, std::map<int, User > &, std::vector<Channel> &){
    reply(fd, "Unknown command: ACCEPT\r\n");
};


// void Command::ACTION(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::ADMIN(std::string, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 256 " + Users.at(fd).getNickname() + " ClownRC :Administrative info\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 257 " + Users.at(fd).getNickname() + " :You're on ClownRC, our server is hosted in France and is accesible with the following url FAUT QUON LA SET\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 258 " + Users.at(fd).getNickname() + " :If you need any information relating our project fell free to contact us\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 259 " + Users.at(fd).getNickname() + " :<achatela@student.42.fr>, <hcarpent@student.42.fr>\r\n");
};


// void Command::ALIAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::AWAY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 2);
    std::string away_msg(buffer.substr(0, buffer.find("\r\n")));

    reply(fd, ":" + Users.at(fd).getFullHostname() + " 306 " + Users.at(fd).getNickname() + " :You have been marked as begin away\r\n");
    Users.at(fd).setIsAway(true);
    Users.at(fd).setAwayMsg(away_msg);
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
// void Command::CTCP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::CYCLE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::DCC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::DEOP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::DEVOICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::DEHILIGHT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::DIE(std::string, int, std::map<int, User > &, std::vector<Channel> &){
    // check if the user is an operator
    exit(1);
    // Free
};


void Command::DISCONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::ECHO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::EVAL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::EXEC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::FLUSHBUFFER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::FOREACH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::FORMAT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::HASH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::HELP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::HILIGHT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::IGNORE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::INFO(std::string, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    std::string debug_str;
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 371" + Users.at(fd).getNickname() + " :------------------INFO------------------\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :Server name ClownRC / URL A DEFINE\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :Version : 1.0\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 371" + Users.at(fd).getNickname() + " :Made by the two original clowns:\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :- achatela <achatela@student.42.fr>\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :- hcarpent <hcarpent@student.42.fr>\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :Thanks for using ClownRC !\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 371 " + Users.at(fd).getNickname() + " :End of /INFO list\r\n");
};


void Command::INVITE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::IRCNET(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::ISO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::JOIN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name(buffer.substr(0, buffer.find("\r\n")));
    std::vector<Channel>::iterator it = channels.begin();
    for (; it != channels.end(); it++){
        if (it->getChannelName() == chan_name){
            for (std::vector<int>::iterator ite = it->getFdList().begin(); ite != it->getFdList().end(); ite++){
                reply(*ite, ":" + Users.at(fd).getFullHostname() + " JOIN :" + chan_name + "\r\n"); // envoyer le putain
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
    std::string msg = "@";
    for (std::vector<std::string>::iterator ite = it->getUserList().begin() ; ite != it->getUserList().end(); ite++){
        msg += *ite;
        if (it->getUserList().end() - ite != 1){
            msg += " ";
        }
    }
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 353 " + Users.at(fd).getNickname() + " = " + chan_name + " :" + msg + "\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 366 " + Users.at(fd).getNickname() + " " + chan_name + " :End of /NAMES list\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " JOIN " + chan_name + "\r\n");
    //confirmation que l'user à join
    //envoyé le topic (RPL_TOPIC)
    //Envoyer liste user a celui qui join (RPL_NAMREPLY)
    //it->addUsername
};


void Command::KICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::KICKBAN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::KILL(std::string , int, std::map<int, User > &, std::vector<Channel> &){

};


void Command::KNOCK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::KNOCKOUT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::LASTLOG(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::LAYOUT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::LINKS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::LIST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::LOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::LASTLOGLUSERS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::MAP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::ME(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::MIRCDCC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


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
            for(; i <= space_num; i++){
                if (username[i][0] == '+')
                    break;
                if (!check.isInUserList(username[i])){
                    reply(fd, ":" + Users.at(fd).getFullHostname() + " 441 " + Users.at(fd).getNickname() + " " + tmp + " :User not on the channel\r\n");
                }
                else{
                    reply(fd, ":" + Users.at(fd).getFullHostname() + " 324 " + Users.at(fd).getNickname() + " " + tmp + " +" + flags[i + 1] + " " + username[i] + "\r\n");
                }
            }
            if (i < flags.size() - 1){
                ;
            }
        }
        reply(fd, ":" + Users.at(fd).getFullHostname() + " 324 " + Users.at(fd).getNickname() + " " + tmp + " +n\r\n");
    }
};


void Command::MOTD(std::string, int fd, std::map<int, User > & Users, std::vector<Channel> &){ // changer (ouvrir un fichier conf/ircd.motd)
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 375 " + Users.at(fd).getNickname() + " :- ClownRC Message of the day\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :-           achatela                                hcarpent\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⣼⡟⠋⣀⣼⣾⣶⣶⣦⣤⣤⣴⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡘⢹⠄           ⣼⡟⠋⣀⣼⣾⣶⣶⣦⣤⣤⣴⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡘⢹⠄\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⡟⠄⢰⣿⣿⣿⣿⣿⣿⣿⠈⠈⣿⣿⣿⣿⡋⠉⣻⣿⣿⣿⣿⣿⣿⣿⡄⠘⣇           ⡟⠄⢰⣿⣿⣿⣿⣿⣿⣿⠈⠈⣿⣿⣿⣿⡋⠉⣻⣿⣿⣿⣿⣿⣿⣿⡄⠘⣇\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠁⠄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⢵⣽⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠄⢹           ⠁⠄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⢵⣽⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠄⢹\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⢀⣾⣿⣿⣿⣿⣿⣿⣿⡿⠋⣿⣿⣿⣿⣿⠉⠻⠿⣿⣿⣿⣿⣿⣿⣿⣇⠄           ⠄⢀⣾⣿⣿⣿⣿⣿⣿⣿⡿⠋⣿⣿⣿⣿⣿⠉⠻⠿⣿⣿⣿⣿⣿⣿⣿⣇⠄\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⢰⣿⣿⡿⠿⠟⠋⠉⠄⠄⠈⣿⣿⣿⣿⡏⢀⣤⣤⣄⣀⣀⣀⡈⠉⢻⣿⠄           ⠄⢰⣿⣿⡿⠿⠟⠋⠉⠄⠄⠈⣿⣿⣿⣿⡏⢀⣤⣤⣄⣀⣀⣀⡈⠉⢻⣿⠄\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⡄⢸⣯⣥⡴⠒⢊⡁ 🧿 ⢸⣿⣿⣿⣿⣦⠈⠁ 🧿 ⣆⠈⣁⣈⣿⣿⡴         ⡄⢸⣯⣥⡴⠒⢊⡁ ⭕ ⢸⣿⣿⣿⣿⣦⠈⠁ ⭕ ⣆⠈⣁⣈⣿⣿⡴\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⣿⢸⣿⣿⣿⣿⣶⣶⣿⣶⣡⣼⣿⣿⣿⣿⣿⢿⣆⣤⣾⣬⣭⣵⣶⣿⣿⣿⣿           ⣿⢸⣿⣿⣿⣿⣶⣶⣿⣶⣡⣼⣿⣿⣿⣿⣿⢿⣆⣤⣾⣬⣭⣵⣶⣿⣿⣿⣿\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⢻⡟⣩⣾⣿⣿⣿⠏⠿⡿⢿⡿⠿⠯⠎⠉⠙⠻⣿⣿⣿⡿⢖⣀⣀⠄⣼⠄           ⠄⢻⡟⣩⣾⣿⣿⣿⠏⠿⡿⢿⡿⠿⠯⠎⠉⠙⠻⣿⣿⣿⡿⢖⣀⣀⠄⣼⠄\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⢀⠘⣷⣿⢿⣿⣿⣿⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢸⣿⠿⠟⠋⠁⣴⣿⠏⠄           ⢀⠘⣷⣿⢿⣿⣿⣿⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢸⣿⠿⠟⠋⠁⣴⣿⠏⠄\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⠄⠘⣿⣷⣌⠙⠻⢿⣷⣶⣤⣤⣤⣀⣠⡤⠞⡋⡍⠄⠂⠄⠄⣼⣿⠃⠄⠄           ⠄⠄⠘⣿⣷⣌⠙⠻⢿⣷⣶⣤⣤⣤⣀⣠⡤⠞⡋⡍⠄⠂⠄⠄⣼⣿⠃⠄⠄\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⠄⠄⠄⢸⣿⣦⠄⠘⣿⡁⣾⣹⡍⣁⠐⡆⡇⠁⡌⠄⠄⠄⣰⣿⠇⠄⠄⠄           ⠄⠄⠄⠄⢸⣿⣦⠄⠘⣿⡁⣾⣹⡍⣁⠐⡆⡇⠁⡌⠄⠄⠄⣰⣿⠇⠄⠄⠄\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⠄⠄⠄⠄⠈⣿⣿⣷⡹⢹⠸⢣⢈⠘⡇⠘⠈⠄⠁⠄⠄⣼⣿⣿⠃⣰⠄⠄           ⠄⠄⠄⠄⠄⠈⣿⣿⣷⡹⢹⠸⢣⢈⠘⡇⠘⠈⠄⠁⠄⠄⣼⣿⣿⠃⣰⠄⠄\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⠄⠄⠄⠄⣷⠘⣿⣿⣷⡀⠄⠸⢿⣿⡏⣾⠓⠃⠄⠄⢀⡟⣿⠏⣰⣿⣷⠄           ⠄⠄⠄⠄⠄⣷⠘⣿⣿⣷⡀⠄⠸⢿⣿⡏⣾⠓⠃⠄⠄⢀⡟⣿⠏⣰⣿⣷⠄\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⠄⣠⣿⣿⣿⣷⠙⣿⣿⣷⡀⠄⠈⠄⠄⠄⠄⠄⠄⣠⡞⣼⡿⢀⣿⣿⣿⣷           ⠄⠄⣠⣿⣿⣿⣷⠙⣿⣿⣷⡀⠄⠈⠄⠄⠄⠄⠄⠄⣠⡞⣼⡿⢀⣿⣿⣿⣷\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- ⠄⣼⣿⣿⣿⣿⣿⣷⠈⠿⣝⣿⣿⣦⣤⣭⣥⣤⣤⣶⣾⠿⠋⢀⣼⣿⣿             ⠄⣼⣿⣿⣿⣿⣿⣷⠈⠿⣝⣿⣿⣦⣤⣭⣥⣤⣤⣶⣾⠿⠋⢀⣼⣿⣿\r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 372 " + Users.at(fd).getNickname() + " :- \r\n");
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 376 " + Users.at(fd).getNickname() + " :End of /MOTD command\r\n");
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
            reply(fd, ":" + Users.at(fd).getFullHostname() + " 401 " + Users.at(fd).getNickname() + " " + tmp_user + " :No such nick/channel\r\n");
        }
    }

    if (tmp_user[0] == '#'){
        std::vector<Channel>::iterator it = channels.begin();

        while (it != channels.end()){
            if (it->getChannelName() == tmp_user)
                break;
            it++;
        }
        if (it == channels.end()){
            std::cout << "possible ? " << std::endl;
        }

        for (std::vector<int>::iterator ite = it->getFdList().begin(); ite != it->getFdList().end(); ite++){
            if (*ite != fd)
                reply(*ite, ":" + Users.at(fd).getFullHostname() + " PRIVMSG " + tmp_user + " :" + tmp_msg + "\r\n"); // envoyer à tous les fd
        }
    }
    else {//if (buffer[0] != 1){
        for (std::map<int, User>::iterator it = Users.begin(); it != Users.end(); it++){
            if (it->second.getNickname() == tmp_user){
                if (Users.at(it->first).getIsAway() == true){
                    reply(fd, ":" + Users.at(fd).getFullHostname() + " 301 " + Users.at(fd).getNickname() + " :" + Users.at(it->first).getAwayMsg() + "\r\n");
                }
                reply(it->first, ":" + Users.at(fd).getFullHostname() + " PRIVMSG " + tmp_user + " :" + tmp_msg + "\r\n");
                break ;
            }
        }
    }
};



void Command::NAMES(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::NCTCP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::NETSPLIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::NETWORK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
//void Command::NICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (voidfd; (void)Users, (void)channels; return;};


void Command::NOTICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp_user(buffer.substr(0, buffer.find(' ')));

    std::map<int, User>::iterator it = Users.begin();

    while (it != Users.end()){
        if (it->second.getNickname() == tmp_user)
            break;
        it++;
    }
    reply(it->first, ":" + Users.at(fd).getFullHostname() + " NOTICE " + buffer + "\r\n");
};


void Command::NOTIFY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;}; // notify list empty
// void Command::OP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::OPER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::PART(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string serv_name(buffer.substr(0, buffer.find("\r\n")));

    std::vector<Channel>::iterator it = channels.begin();
    for (; it != channels.end(); it++){
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
    reply(fd, ":" + Users.at(fd).getFullHostname() + " PART " + serv_name + "\r\n");
    for (std::vector<int>::iterator ite = it->getFdList().begin(); ite != it->getFdList().end(); ite++){
        reply(*ite, ":" + Users.at(fd).getFullHostname() + " PART " + serv_name + "\r\n");
    }
    if (it->getFdList().empty())
        channels.erase(it);
};


void Command::PING(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & ){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string toSend(":" + Users.at(fd).getFullHostname() + " PONG :" + buffer);
    send(fd, toSend.c_str(), toSend.length(), 0);
    if (DEBUG)
        std::cout << YELLOW << "Server" << BLUE << " >> " << CYAN << "[" << fd << "] " << BLUE << toSend << RESET;
};

// void Command::QUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::QUIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string leave_msg(buffer.substr(0, buffer.find("\r\n")));

    Users.at(fd).setIsConnected(false);
    reply(fd, ":" + Users.at(fd).getFullHostname() + " QUIT :QUIT " + leave_msg + "\r\n");
};


// void Command::QUOTE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::RAWLOG(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::RECODE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::RECONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::REDRAW(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::REHASH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;}; // ??
// void Command::RELOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::RESIZE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::RESTART(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::RMRECONNS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::RMREJOINS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::SAVE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SCONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::SCRIPT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::SCROLLBACK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::SERVER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SERVLIST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::SET(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SETHOST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SILENCE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SQUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::SQUIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::STATS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::STATUSBAR(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::TIME(std::string , int fd, std::map<int, User > & Users, std::vector<Channel> &){
    std::time_t time = std::time(NULL);
    reply(fd, ":" + Users.at(fd).getFullHostname() + " 391 " + Users.at(fd).getNickname() + " ClownRC :" + std::asctime(std::localtime(&time)) + "\r\n");
};


// void Command::TOGGLE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::TOPIC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string chan_name(buffer.substr(0, buffer.find(" ")));
    buffer.erase(0, buffer.find(' ') + 1);

    std::string toFind = chan_name;
    if (chan_name[0] != '#'){
        std::string toFind = "#" + chan_name;
    }  
    std::vector<Channel>::iterator it = channels.begin();

    while (it != channels.end()){
        if (it->getChannelName() == toFind)
            break;
        it++;
    }
    if (it == channels.end()){
        reply(fd, ":" + Users.at(fd).getFullHostname() + " 442 " + Users.at(fd).getNickname() + " " + chan_name + " :You're not on that channel\r\n");
        return;
    }

    reply(fd, ":" + Users.at(fd).getFullHostname() + " TOPIC " + chan_name + " " + buffer);
};


void Command::TRACE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::TS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::UNALIAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UNBAN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::UNIGNORE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::UNLOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::UNNOTIFY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::UNQUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UNSILENCE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::UPGRADE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::UPTIME(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::USERHOST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::VER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::VERSION(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::VOICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::WAIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::WALL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::WALLOPS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};


void Command::WHO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 1);
    std::string tmp(buffer.substr(0, buffer.find("\r\n")));

    if (tmp[0] == '#'){
        reply(fd, ":" + Users.at(fd).getFullHostname() + " 315 " + Users.at(fd).getNickname() + " " + Users.at(fd).getUsername() + " :End of /WHO list\r\n");
    }
};


void Command::WHOIS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
void Command::WHOWAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};
// void Command::WINDOW(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels){(void)buffer; (void)fd; (void)Users, (void)channels; return;};

void Command::PASS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 1);
    Users.at(fd).setPassword(buffer.substr(0, buffer.find("\r\n")));
    // if (Users.at(fd).getPassword()[Users.at(fd).getPassword().length() - 1] == '\r')
    //     Users.at(fd).getPassword().erase(0, Users.at(fd).getPassword().end() - 1);
    // std::cout << "password: " << Users.at(fd).getPassword() << std::endl;
    return;
}


void Command::NICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> &){
    buffer.erase(0, buffer.find(' ') + 1);
    buffer = buffer.substr(0, buffer.find("\r\n"));
    if (buffer.find('\b') != std::string::npos || buffer.find('\r') != std::string::npos
        || buffer.find('@') != std::string::npos || buffer.find('\0') != std::string::npos || buffer.find(' ') != std::string::npos){
            reply(fd, ":" + Users.at(fd).getFullHostname() + " 432 " + Users.at(fd).getNickname() + " :Nickname " + buffer + " is invalid !\r\n");
            return ;
    }
    for (std::map<int, User >::iterator it = Users.begin() ; it != Users.end(); it++){
        if (it->second.getNickname() == buffer){
            reply(fd, ": 433 * " + buffer + " :Nickname is already in use\r\n");
            return ;
        }
    }
    Users.at(fd).setNickname(buffer);
    reply(fd, ": NICK " + buffer + "\r\n");
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
    // if ((Users.at(fd).getBuffer().empty() || Users.at(fd).getHostname().empty() || Users.at(fd).getNickname().empty()
    //     ||  Users.at(fd).getPassword().empty() || Users.at(fd).getRealName().empty() || Users.at(fd).getUsername().empty()))
    //     Users.at(fd).setAccess(FORBIDDEN);
    // else{
    //     if (Users.at(fd).getRealPassword().empty())
    //         Users.at(fd).setAccess(AUTHORIZED);
    //     else{
    //         if (Users.at(fd).getPassword() != Users.at(fd).getRealPassword()){
    //             Users.at(fd).setAccess(FORBIDDEN);
    //         }
    //         else
    //             Users.at(fd).setAccess(AUTHORIZED);
    //     }
    // }
    // if (Users.at(fd).getAccess() == AUTHORIZED){

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

        //reply(fd, ":" + Users.at(fd).getFullHostname() + " 001 " + Users.at(fd).getNickname() + " Welcome to the Internet Relay Network " + Users.at(fd).getFullHostname());
        // std::cout << toSend << std::endl;
    //}
    //reply(fd, ":" + Users.at(fd).getFullHostname() + " 001 " + Users.at(fd).getNickname() + " Welcome to the Internet Relay Network " + Users.at(fd).getFullHostname());
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
    _commandsFilled["TOPIC"] = TOPIC;
};

Command::~Command(void){

};