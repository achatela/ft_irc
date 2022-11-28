#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "utils.hpp"
# include "User.hpp"
# include "Channel.hpp"

class Channel;

class Command{

    private:
        std::map<std::string, void  (*)(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels)> _commandsFilled;

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

        std::map<std::string, void  (*)(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels)> getCommand(void){return _commandsFilled;};

        static void reply(int fd, std::string full_host_name, std::string reply_type, std::string nickname, std::string msg);
        static void  ACCEPT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  ACTION(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  ADMIN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  ALIAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  AWAY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  BAN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  BEEP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  BIND(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  CAT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  CD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  CHANNEL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  CLEAR(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  COMPLETION(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  CONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  CTCP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  CYCLE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  DCC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  DEOP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  DEVOICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  DEHILIGHT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  DIE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  DISCONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  ECHO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  EVAL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  EXEC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  FLUSHBUFFER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  FOREACH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  FORMAT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  HASH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        // static void  HELP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  HILIGHT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  IGNORE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  INFO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  INVITE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  IRCNET(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  ISO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  JOIN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  KICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  KICKBAN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  KILL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  KNOCK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  KNOCKOUT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  LASTLOG(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  LAYOUT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  LINKS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  LIST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  LOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  LASTLOGLUSERS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  MAP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  ME(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  MIRCDCC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  MODE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  MOTD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  PRIVMSG(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  NAMES(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  NCTCP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  NETSPLIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  NETWORK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        //static void  NICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  NOTICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  NOTIFY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  OP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  OPER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  PART(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  PING(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  QUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  QUIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  QUOTE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  RAWLOG(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  RECODE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  RECONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  REDRAW(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  REHASH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  RELOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  RESIZE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  RESTART(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  RMRECONNS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  RMREJOINS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  SAVE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  SCONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  SCRIPT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  SCROLLBACK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  SERVER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  SERVLIST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  SET(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  SETHOST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  SILENCE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  SQUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  SQUIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  STATS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  STATUSBAR(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  TIME(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  TOGGLE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  TOPIC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  TRACE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  TS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  UNALIAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  UNBAN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  UNIGNORE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  UNLOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  UNNOTIFY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  UNQUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  UNSILENCE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  UPGRADE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  UPTIME(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  USERHOST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  VER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  VERSION(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  VOICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  WAIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  WALL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  WALLOPS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  WHO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  WHOIS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  WHOWAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  WINDOW(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  PASS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  NICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
        static void  USER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<Channel> & channels);
};

#endif