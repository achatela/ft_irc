#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "utils.hpp"
# include "User.hpp"

class Command{

    private:
        std::map<std::string, void (*)(std::string buffer, int fd, std::map<int, User > & Users)> _commandsFilled;

    public:
        Command();
        ~Command();

        std::map<std::string, void (*)(std::string buffer, int fd, std::map<int, User > & Users)> getCommand(void){return _commandsFilled;};

        static void ACCEPT(std::string buffer, int fd, std::map<int, User > & Users);
        static void ACTION(std::string buffer, int fd, std::map<int, User > & Users);
        static void ADMIN(std::string buffer, int fd, std::map<int, User > & Users);
        static void ALIAS(std::string buffer, int fd, std::map<int, User > & Users);
        static void AWAY(std::string buffer, int fd, std::map<int, User > & Users);
        static void BAN(std::string buffer, int fd, std::map<int, User > & Users);
        static void BEEP(std::string buffer, int fd, std::map<int, User > & Users);
        static void BIND(std::string buffer, int fd, std::map<int, User > & Users);
        static void CAT(std::string buffer, int fd, std::map<int, User > & Users);
        static void CD(std::string buffer, int fd, std::map<int, User > & Users);
        static void CHANNEL(std::string buffer, int fd, std::map<int, User > & Users);
        static void CLEAR(std::string buffer, int fd, std::map<int, User > & Users);
        static void COMPLETION(std::string buffer, int fd, std::map<int, User > & Users);
        static void CONNECT(std::string buffer, int fd, std::map<int, User > & Users);
        static void CTCP(std::string buffer, int fd, std::map<int, User > & Users);
        static void CYCLE(std::string buffer, int fd, std::map<int, User > & Users);
        static void DCC(std::string buffer, int fd, std::map<int, User > & Users);
        static void DEOP(std::string buffer, int fd, std::map<int, User > & Users);
        static void DEVOICE(std::string buffer, int fd, std::map<int, User > & Users);
        static void DEHILIGHT(std::string buffer, int fd, std::map<int, User > & Users);
        static void DISCONNECT(std::string buffer, int fd, std::map<int, User > & Users);
        static void ECHO(std::string buffer, int fd, std::map<int, User > & Users);
        static void EVAL(std::string buffer, int fd, std::map<int, User > & Users);
        static void EXEC(std::string buffer, int fd, std::map<int, User > & Users);
        static void FLUSHBUFFER(std::string buffer, int fd, std::map<int, User > & Users);
        static void FOREACH(std::string buffer, int fd, std::map<int, User > & Users);
        static void FORMAT(std::string buffer, int fd, std::map<int, User > & Users);
        static void HASH(std::string buffer, int fd, std::map<int, User > & Users);
        static void HELP(std::string buffer, int fd, std::map<int, User > & Users);
        static void HILIGHT(std::string buffer, int fd, std::map<int, User > & Users);
        static void IGNORE(std::string buffer, int fd, std::map<int, User > & Users);
        static void INFO(std::string buffer, int fd, std::map<int, User > & Users);
        static void INVITE(std::string buffer, int fd, std::map<int, User > & Users);
        static void IRCNET(std::string buffer, int fd, std::map<int, User > & Users);
        static void ISO(std::string buffer, int fd, std::map<int, User > & Users);
        static void NJOIN(std::string buffer, int fd, std::map<int, User > & Users);
        static void KICK(std::string buffer, int fd, std::map<int, User > & Users);
        static void KICKBAN(std::string buffer, int fd, std::map<int, User > & Users);
        static void KILL(std::string buffer, int fd, std::map<int, User > & Users);
        static void KNOCK(std::string buffer, int fd, std::map<int, User > & Users);
        static void KNOCKOUT(std::string buffer, int fd, std::map<int, User > & Users);
        static void LASTLOG(std::string buffer, int fd, std::map<int, User > & Users);
        static void LAYOUT(std::string buffer, int fd, std::map<int, User > & Users);
        static void LINKS(std::string buffer, int fd, std::map<int, User > & Users);
        static void LIST(std::string buffer, int fd, std::map<int, User > & Users);
        static void LOAD(std::string buffer, int fd, std::map<int, User > & Users);
        static void LASTLOGLUSERS(std::string buffer, int fd, std::map<int, User > & Users);
        static void MAP(std::string buffer, int fd, std::map<int, User > & Users);
        static void ME(std::string buffer, int fd, std::map<int, User > & Users);
        static void MIRCDCC(std::string buffer, int fd, std::map<int, User > & Users);
        static void MODE(std::string buffer, int fd, std::map<int, User > & Users);
        static void MOTD(std::string buffer, int fd, std::map<int, User > & Users);
        static void MSG(std::string buffer, int fd, std::map<int, User > & Users);
        static void NAMES(std::string buffer, int fd, std::map<int, User > & Users);
        static void NCTCP(std::string buffer, int fd, std::map<int, User > & Users);
        static void NETSPLIT(std::string buffer, int fd, std::map<int, User > & Users);
        static void NETWORK(std::string buffer, int fd, std::map<int, User > & Users);
        //static void NICK(std::string buffer, int fd, std::map<int, User > & Users);
        static void NOTICE(std::string buffer, int fd, std::map<int, User > & Users);
        static void NOTIFY(std::string buffer, int fd, std::map<int, User > & Users);
        static void OP(std::string buffer, int fd, std::map<int, User > & Users);
        static void OPER(std::string buffer, int fd, std::map<int, User > & Users);
        static void PART(std::string buffer, int fd, std::map<int, User > & Users);
        static void PING(std::string buffer, int fd, std::map<int, User > & Users);
        static void QUERY(std::string buffer, int fd, std::map<int, User > & Users);
        static void QUIT(std::string buffer, int fd, std::map<int, User > & Users);
        static void QUOTE(std::string buffer, int fd, std::map<int, User > & Users);
        static void RAWLOG(std::string buffer, int fd, std::map<int, User > & Users);
        static void RECODE(std::string buffer, int fd, std::map<int, User > & Users);
        static void RECONNECT(std::string buffer, int fd, std::map<int, User > & Users);
        static void REDRAW(std::string buffer, int fd, std::map<int, User > & Users);
        static void REHASH(std::string buffer, int fd, std::map<int, User > & Users);
        static void RELOAD(std::string buffer, int fd, std::map<int, User > & Users);
        static void RESIZE(std::string buffer, int fd, std::map<int, User > & Users);
        static void RESTART(std::string buffer, int fd, std::map<int, User > & Users);
        static void RMRECONNS(std::string buffer, int fd, std::map<int, User > & Users);
        static void RMREJOINS(std::string buffer, int fd, std::map<int, User > & Users);
        static void SAVE(std::string buffer, int fd, std::map<int, User > & Users);
        static void SCONNECT(std::string buffer, int fd, std::map<int, User > & Users);
        static void SCRIPT(std::string buffer, int fd, std::map<int, User > & Users);
        static void SCROLLBACK(std::string buffer, int fd, std::map<int, User > & Users);
        static void SERVER(std::string buffer, int fd, std::map<int, User > & Users);
        static void SERVLIST(std::string buffer, int fd, std::map<int, User > & Users);
        static void SET(std::string buffer, int fd, std::map<int, User > & Users);
        static void SETHOST(std::string buffer, int fd, std::map<int, User > & Users);
        static void SILENCE(std::string buffer, int fd, std::map<int, User > & Users);
        static void SQUERY(std::string buffer, int fd, std::map<int, User > & Users);
        static void SQUIT(std::string buffer, int fd, std::map<int, User > & Users);
        static void STATS(std::string buffer, int fd, std::map<int, User > & Users);
        static void STATUSBAR(std::string buffer, int fd, std::map<int, User > & Users);
        static void TIME(std::string buffer, int fd, std::map<int, User > & Users);
        static void TOGGLE(std::string buffer, int fd, std::map<int, User > & Users);
        static void TOPIC(std::string buffer, int fd, std::map<int, User > & Users);
        static void TRACE(std::string buffer, int fd, std::map<int, User > & Users);
        static void TS(std::string buffer, int fd, std::map<int, User > & Users);
        static void UNALIAS(std::string buffer, int fd, std::map<int, User > & Users);
        static void UNBAN(std::string buffer, int fd, std::map<int, User > & Users);
        static void UNIGNORE(std::string buffer, int fd, std::map<int, User > & Users);
        static void UNLOAD(std::string buffer, int fd, std::map<int, User > & Users);
        static void UNNOTIFY(std::string buffer, int fd, std::map<int, User > & Users);
        static void UNQUERY(std::string buffer, int fd, std::map<int, User > & Users);
        static void UNSILENCE(std::string buffer, int fd, std::map<int, User > & Users);
        static void UPGRADE(std::string buffer, int fd, std::map<int, User > & Users);
        static void UPTIME(std::string buffer, int fd, std::map<int, User > & Users);
        static void USERHOST(std::string buffer, int fd, std::map<int, User > & Users);
        static void VER(std::string buffer, int fd, std::map<int, User > & Users);
        static void VERSION(std::string buffer, int fd, std::map<int, User > & Users);
        static void VOICE(std::string buffer, int fd, std::map<int, User > & Users);
        static void WAIT(std::string buffer, int fd, std::map<int, User > & Users);
        static void WALL(std::string buffer, int fd, std::map<int, User > & Users);
        static void WALLOPS(std::string buffer, int fd, std::map<int, User > & Users);
        static void WHO(std::string buffer, int fd, std::map<int, User > & Users);
        static void WHOIS(std::string buffer, int fd, std::map<int, User > & Users);
        static void WHOWAS(std::string buffer, int fd, std::map<int, User > & Users);
        static void WINDOW(std::string buffer, int fd, std::map<int, User > & Users);
        static void PASS(std::string buffer, int fd, std::map<int, User > & Users);
        static void NICK(std::string buffer, int fd, std::map<int, User > & Users);
        static void USER(std::string buffer, int fd, std::map<int, User > & Users);
};

#endif