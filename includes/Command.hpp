#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "utils.hpp"
# include "User.hpp"
# include "Channel.hpp"
# include "Server.hpp"

class Channel;
class Server;

class Command{

    private:
        std::map<std::string, void  (*)(std::string buffer, int fd,  Server & server)> _commandsFilled;

    public:
        Command();
        ~Command();

        static int getChannel(std::string chan_name, std::vector<Channel> & channels){
            int i = 0;
            std::vector<Channel>::iterator it = channels.begin();
            for (; it != channels.end() && it->getChannelName() != chan_name; it++){
                i++;
            }
            if (it == channels.end())
                return -1;
            return i;
        }

        std::map<std::string, void  (*)(std::string buffer, int fd,  Server & server)> getCommand(void){return _commandsFilled;};

        static void reply(int atFd, Server & server, int fd, std::string toSend);
        static void  ACCEPT(std::string buffer, int fd,  Server & server);
        // static void  ACTION(std::string buffer, int fd,  Server & server);
        static void  ADMIN(std::string buffer, int fd,  Server & server);
        // static void  ALIAS(std::string buffer, int fd,  Server & server);
        static void  AWAY(std::string buffer, int fd,  Server & server);
        static void  BAN(std::string buffer, int fd,  Server & server);
        // static void  BEEP(std::string buffer, int fd,  Server & server);
        // static void  BIND(std::string buffer, int fd,  Server & server);
        // static void  CAT(std::string buffer, int fd,  Server & server);
        // static void  CD(std::string buffer, int fd,  Server & server);
        // static void  CHANNEL(std::string buffer, int fd,  Server & server);
        // static void  CLEAR(std::string buffer, int fd,  Server & server);
        // static void  COMPLETION(std::string buffer, int fd,  Server & server);
        // static void  CONNECT(std::string buffer, int fd,  Server & server);
        static void  CTCP(std::string buffer, int fd,  Server & server);
        static void  CYCLE(std::string buffer, int fd,  Server & server);
        static void  DCC(std::string buffer, int fd,  Server & server);
        static void  DEOP(std::string buffer, int fd,  Server & server);
        static void  DEVOICE(std::string buffer, int fd,  Server & server);
        static void  DEHILIGHT(std::string buffer, int fd,  Server & server);
        static void  DIE(std::string buffer, int fd,  Server & server);
        static void  DISCONNECT(std::string buffer, int fd,  Server & server);
        // static void  ECHO(std::string buffer, int fd,  Server & server);
        static void  EVAL(std::string buffer, int fd,  Server & server);
        static void  EXEC(std::string buffer, int fd,  Server & server);
        static void  FLUSHBUFFER(std::string buffer, int fd,  Server & server);
        static void  FOREACH(std::string buffer, int fd,  Server & server);
        static void  FORMAT(std::string buffer, int fd,  Server & server);
        static void  HASH(std::string buffer, int fd,  Server & server);
        // static void  HELP(std::string buffer, int fd,  Server & server);
        static void  HILIGHT(std::string buffer, int fd,  Server & server);
        static void  IGNORE(std::string buffer, int fd,  Server & server);
        static void  INFO(std::string buffer, int fd,  Server & server);
        static void  INVITE(std::string buffer, int fd,  Server & server);
        static void  IRCNET(std::string buffer, int fd,  Server & server);
        static void  ISO(std::string buffer, int fd,  Server & server);
        static void  JOIN(std::string buffer, int fd,  Server & server);
        static void  KICK(std::string buffer, int fd,  Server & server);
        static void  KICKBAN(std::string buffer, int fd,  Server & server);
        static void  KILL(std::string buffer, int fd,  Server & server);
        static void  KNOCK(std::string buffer, int fd,  Server & server);
        static void  KNOCKOUT(std::string buffer, int fd,  Server & server);
        static void  LASTLOG(std::string buffer, int fd,  Server & server);
        static void  LAYOUT(std::string buffer, int fd,  Server & server);
        static void  LINKS(std::string buffer, int fd,  Server & server);
        static void  LIST(std::string buffer, int fd,  Server & server);
        static void  LOAD(std::string buffer, int fd,  Server & server);
        static void  LASTLOGLUSERS(std::string buffer, int fd,  Server & server);
        static void  MAP(std::string buffer, int fd,  Server & server);
        static void  ME(std::string buffer, int fd,  Server & server);
        static void  MIRCDCC(std::string buffer, int fd,  Server & server);
        static void  MODE(std::string buffer, int fd,  Server & server);
        static void  MOTD(std::string buffer, int fd,  Server & server);
        static void  PRIVMSG(std::string buffer, int fd,  Server & server);
        static void  NAMES(std::string buffer, int fd,  Server & server);
        static void  NCTCP(std::string buffer, int fd,  Server & server);
        static void  NETSPLIT(std::string buffer, int fd,  Server & server);
        static void  NETWORK(std::string buffer, int fd,  Server & server);
        //static void  NICK(std::string buffer, int fd,  Server & server);
        static void  NOTICE(std::string buffer, int fd,  Server & server);
        static void  NOTIFY(std::string buffer, int fd,  Server & server);
        static void  OP(std::string buffer, int fd,  Server & server);
        static void  OPER(std::string buffer, int fd,  Server & server);
        static void  PART(std::string buffer, int fd,  Server & server);
        static void  PING(std::string buffer, int fd,  Server & server);
        static void  QUERY(std::string buffer, int fd,  Server & server);
        static void  QUIT(std::string buffer, int fd,  Server & server);
        static void  QUOTE(std::string buffer, int fd,  Server & server);
        static void  RAWLOG(std::string buffer, int fd,  Server & server);
        static void  RECODE(std::string buffer, int fd,  Server & server);
        static void  RECONNECT(std::string buffer, int fd,  Server & server);
        static void  REDRAW(std::string buffer, int fd,  Server & server);
        static void  REHASH(std::string buffer, int fd,  Server & server);
        static void  RELOAD(std::string buffer, int fd,  Server & server);
        static void  RESIZE(std::string buffer, int fd,  Server & server);
        static void  RESTART(std::string buffer, int fd,  Server & server);
        static void  RMRECONNS(std::string buffer, int fd,  Server & server);
        static void  RMREJOINS(std::string buffer, int fd,  Server & server);
        static void  SAVE(std::string buffer, int fd,  Server & server);
        static void  SCONNECT(std::string buffer, int fd,  Server & server);
        static void  SCRIPT(std::string buffer, int fd,  Server & server);
        static void  SCROLLBACK(std::string buffer, int fd,  Server & server);
        static void  SERVER(std::string buffer, int fd,  Server & server);
        static void  SERVLIST(std::string buffer, int fd,  Server & server);
        static void  SET(std::string buffer, int fd,  Server & server);
        static void  SETHOST(std::string buffer, int fd,  Server & server);
        static void  SILENCE(std::string buffer, int fd,  Server & server);
        static void  SQUERY(std::string buffer, int fd,  Server & server);
        static void  SQUIT(std::string buffer, int fd,  Server & server);
        static void  STATS(std::string buffer, int fd,  Server & server);
        static void  STATUSBAR(std::string buffer, int fd,  Server & server);
        static void  TIME(std::string buffer, int fd,  Server & server);
        static void  TOGGLE(std::string buffer, int fd,  Server & server);
        static void  TOPIC(std::string buffer, int fd,  Server & server);
        static void  TRACE(std::string buffer, int fd,  Server & server);
        static void  TS(std::string buffer, int fd,  Server & server);
        static void  UNALIAS(std::string buffer, int fd,  Server & server);
        static void  UNBAN(std::string buffer, int fd,  Server & server);
        static void  UNIGNORE(std::string buffer, int fd,  Server & server);
        static void  UNLOAD(std::string buffer, int fd,  Server & server);
        static void  UNNOTIFY(std::string buffer, int fd,  Server & server);
        static void  UNQUERY(std::string buffer, int fd,  Server & server);
        static void  UNSILENCE(std::string buffer, int fd,  Server & server);
        static void  UPGRADE(std::string buffer, int fd,  Server & server);
        static void  UPTIME(std::string buffer, int fd,  Server & server);
        static void  USERHOST(std::string buffer, int fd,  Server & server);
        static void  VER(std::string buffer, int fd,  Server & server);
        static void  VERSION(std::string buffer, int fd,  Server & server);
        static void  VOICE(std::string buffer, int fd,  Server & server);
        static void  WAIT(std::string buffer, int fd,  Server & server);
        static void  WALL(std::string buffer, int fd,  Server & server);
        static void  WALLOPS(std::string buffer, int fd,  Server & server);
        static void  WHO(std::string buffer, int fd,  Server & server);
        static void  WHOIS(std::string buffer, int fd,  Server & server);
        static void  WHOWAS(std::string buffer, int fd,  Server & server);
        static void  WINDOW(std::string buffer, int fd,  Server & server);
        static void  PASS(std::string buffer, int fd,  Server & server);
        static void  NICK(std::string buffer, int fd,  Server & server);
        static void  USER(std::string buffer, int fd,  Server & server);
};

#endif