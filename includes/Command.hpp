#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "../includes/utils.hpp"

class Command{

    private:
        std::map<std::string, void (*)(std::string)> _commandsFilled;

    public:
        Command();
        ~Command();

        std::map<std::string, void (*)(std::string)> getCommand(void){return _commandsFilled;};

        static void ACCEPT(std::string buffer);
        static void ACTION(std::string buffer);
        static void ADMIN(std::string buffer);
        static void ALIAS(std::string buffer);
        static void AWAY(std::string buffer);
        static void BAN(std::string buffer);
        static void BEEP(std::string buffer);
        static void BIND(std::string buffer);
        static void CAT(std::string buffer);
        static void CD(std::string buffer);
        static void CHANNEL(std::string buffer);
        static void CLEAR(std::string buffer);
        static void COMPLETION(std::string buffer);
        static void CONNECT(std::string buffer);
        static void CTCP(std::string buffer);
        static void CYCLE(std::string buffer);
        static void DCC(std::string buffer);
        static void DEOP(std::string buffer);
        static void DEVOICE(std::string buffer);
        static void DEHILIGHT(std::string buffer);
        static void DISCONNECT(std::string buffer);
        static void ECHO(std::string buffer);
        static void EVAL(std::string buffer);
        static void EXEC(std::string buffer);
        static void FLUSHBUFFER(std::string buffer);
        static void FOREACH(std::string buffer);
        static void FORMAT(std::string buffer);
        static void HASH(std::string buffer);
        static void HELP(std::string buffer);
        static void HILIGHT(std::string buffer);
        static void IGNORE(std::string buffer);
        static void INFO(std::string buffer);
        static void INVITE(std::string buffer);
        static void IRCNET(std::string buffer);
        static void ISO(std::string buffer);
        static void NJOIN(std::string buffer);
        static void KICK(std::string buffer);
        static void KICKBAN(std::string buffer);
        static void KILL(std::string buffer);
        static void KNOCK(std::string buffer);
        static void KNOCKOUT(std::string buffer);
        static void LASTLOG(std::string buffer);
        static void LAYOUT(std::string buffer);
        static void LINKS(std::string buffer);
        static void LIST(std::string buffer);
        static void LOAD(std::string buffer);
        static void LASTLOGLUSERS(std::string buffer);
        static void MAP(std::string buffer);
        static void ME(std::string buffer);
        static void MIRCDCC(std::string buffer);
        static void MODE(std::string buffer);
        static void MOTD(std::string buffer);
        static void MSG(std::string buffer);
        static void NAMES(std::string buffer);
        static void NCTCP(std::string buffer);
        static void NETSPLIT(std::string buffer);
        static void NETWORK(std::string buffer);
        static void NICK(std::string buffer);
        static void NOTICE(std::string buffer);
        static void NOTIFY(std::string buffer);
        static void OP(std::string buffer);
        static void OPER(std::string buffer);
        static void PART(std::string buffer);
        static void PING(std::string buffer);
        static void QUERY(std::string buffer);
        static void QUIT(std::string buffer);
        static void QUOTE(std::string buffer);
        static void RAWLOG(std::string buffer);
        static void RECODE(std::string buffer);
        static void RECONNECT(std::string buffer);
        static void REDRAW(std::string buffer);
        static void REHASH(std::string buffer);
        static void RELOAD(std::string buffer);
        static void RESIZE(std::string buffer);
        static void RESTART(std::string buffer);
        static void RMRECONNS(std::string buffer);
        static void RMREJOINS(std::string buffer);
        static void SAVE(std::string buffer);
        static void SCONNECT(std::string buffer);
        static void SCRIPT(std::string buffer);
        static void SCROLLBACK(std::string buffer);
        static void SERVER(std::string buffer);
        static void SERVLIST(std::string buffer);
        static void SET(std::string buffer);
        static void SETHOST(std::string buffer);
        static void SILENCE(std::string buffer);
        static void SQUERY(std::string buffer);
        static void SQUIT(std::string buffer);
        static void STATS(std::string buffer);
        static void STATUSBAR(std::string buffer);
        static void TIME(std::string buffer);
        static void TOGGLE(std::string buffer);
        static void TOPIC(std::string buffer);
        static void TRACE(std::string buffer);
        static void TS(std::string buffer);
        static void UNALIAS(std::string buffer);
        static void UNBAN(std::string buffer);
        static void UNIGNORE(std::string buffer);
        static void UNLOAD(std::string buffer);
        static void UNNOTIFY(std::string buffer);
        static void UNQUERY(std::string buffer);
        static void UNSILENCE(std::string buffer);
        static void UPGRADE(std::string buffer);
        static void UPTIME(std::string buffer);
        static void USERHOST(std::string buffer);
        static void VER(std::string buffer);
        static void VERSION(std::string buffer);
        static void VOICE(std::string buffer);
        static void WAIT(std::string buffer);
        static void WALL(std::string buffer);
        static void WALLOPS(std::string buffer);
        static void WHO(std::string buffer);
        static void WHOIS(std::string buffer);
        static void WHOWAS(std::string buffer);
        static void WINDOW(std::string buffer);
};

#endif