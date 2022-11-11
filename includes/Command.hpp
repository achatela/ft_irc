#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "utils.hpp"
# include "User.hpp"

class Command{

    private:
        std::map<std::string, void (*)(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds)> _commandsFilled;

    public:
        Command();
        Command(std::map<int, User > & Users, std::vector<pollfd > & pfds);
        ~Command();

        std::map<std::string, void (*)(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds)> getCommand(void){return _commandsFilled;};

        static void ACCEPT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void ACTION(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void ADMIN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void ALIAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void AWAY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void BAN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void BEEP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void BIND(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void CAT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void CD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void CHANNEL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void CLEAR(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void COMPLETION(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void CONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void CTCP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void CYCLE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void DCC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void DEOP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void DEVOICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void DEHILIGHT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void DISCONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void ECHO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void EVAL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void EXEC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void FLUSHBUFFER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void FOREACH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void FORMAT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void HASH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void HELP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void HILIGHT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void IGNORE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void INFO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void INVITE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void IRCNET(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void ISO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void NJOIN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void KICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void KICKBAN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void KILL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void KNOCK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void KNOCKOUT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void LASTLOG(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void LAYOUT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void LINKS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void LIST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void LOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void LASTLOGLUSERS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void MAP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void ME(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void MIRCDCC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void MODE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void MOTD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void MSG(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void NAMES(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void NCTCP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void NETSPLIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void NETWORK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        //static void NICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void NOTICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void NOTIFY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void OP(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void OPER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void PART(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void PING(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void QUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void QUIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void QUOTE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void RAWLOG(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void RECODE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void RECONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void REDRAW(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void REHASH(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void RELOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void RESIZE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void RESTART(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void RMRECONNS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void RMREJOINS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void SAVE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void SCONNECT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void SCRIPT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void SCROLLBACK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void SERVER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void SERVLIST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void SET(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void SETHOST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void SILENCE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void SQUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void SQUIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void STATS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void STATUSBAR(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void TIME(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void TOGGLE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void TOPIC(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void TRACE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void TS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void UNALIAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void UNBAN(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void UNIGNORE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void UNLOAD(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void UNNOTIFY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void UNQUERY(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void UNSILENCE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void UPGRADE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void UPTIME(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void USERHOST(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void VER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void VERSION(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void VOICE(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void WAIT(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void WALL(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void WALLOPS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void WHO(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void WHOIS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void WHOWAS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void WINDOW(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void PASS(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void NICK(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
        static void USER(std::string buffer, int fd, std::map<int, User > & Users, std::vector<pollfd > pfds);
};

#endif