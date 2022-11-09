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

        void ACCEPT(std::string buffer);
        void ACTION(std::string buffer);
        void ADMIN(std::string buffer);
        void ALIAS(std::string buffer);
        void AWAY(std::string buffer);
        void BAN(std::string buffer);
        void BEEP(std::string buffer);
        void BIND(std::string buffer);
        void CAT(std::string buffer);
        void CD(std::string buffer);
        void CHANNEL(std::string buffer);
        void CLEAR(std::string buffer);
        void COMPLETION(std::string buffer);
        void CONNECT(std::string buffer);
        void CTCP(std::string buffer);
        void CYCLE(std::string buffer);
        void DCC(std::string buffer);
        void DEOP(std::string buffer);
        void DEVOICE(std::string buffer);
        void DEHILIGHT(std::string buffer);
        void DISCONNECT(std::string buffer);
        void ECHO(std::string buffer);
        void EVAL(std::string buffer);
        void EXEC(std::string buffer);
        void FLUSHBUFFER(std::string buffer);
        void FOREACH(std::string buffer);
        void FORMAT(std::string buffer);
        void HASH(std::string buffer);
        void HELP(std::string buffer);
        void HILIGHT(std::string buffer);
        void IGNORE(std::string buffer);
        void INFO(std::string buffer);
        void INVITE(std::string buffer);
        void IRCNET(std::string buffer);
        void ISO(std::string buffer);
        void NJOIN(std::string buffer);
        void KICK(std::string buffer);
        void KICKBAN(std::string buffer);
        void KILL(std::string buffer);
        void KNOCK(std::string buffer);
        void KNOCKOUT(std::string buffer);
        void LASTLOG(std::string buffer);
        void LAYOUT(std::string buffer);
        void LINKS(std::string buffer);
        void LIST(std::string buffer);
        void LOAD(std::string buffer);
        void LASTLOGLUSERS(std::string buffer);
        void MAP(std::string buffer);
        void ME(std::string buffer);
        void MIRCDCC(std::string buffer);
        static void MODE(std::string buffer);
        void MOTD(std::string buffer);
        void MSG(std::string buffer);
        void NAMES(std::string buffer);
        void NCTCP(std::string buffer);
        void NETSPLIT(std::string buffer);
        void NETWORK(std::string buffer);
        void NICK(std::string buffer);
        void NOTICE(std::string buffer);
        void NOTIFY(std::string buffer);
        void OP(std::string buffer);
        void OPER(std::string buffer);
        void PART(std::string buffer);
        static void PING(std::string buffer);
        void QUERY(std::string buffer);
        void QUIT(std::string buffer);
        void QUOTE(std::string buffer);
        void RAWLOG(std::string buffer);
        void RECODE(std::string buffer);
        void RECONNECT(std::string buffer);
        void REDRAW(std::string buffer);
        void REHASH(std::string buffer);
        void RELOAD(std::string buffer);
        void RESIZE(std::string buffer);
        void RESTART(std::string buffer);
        void RMRECONNS(std::string buffer);
        void RMREJOINS(std::string buffer);
        void SAVE(std::string buffer);
        void SCONNECT(std::string buffer);
        void SCRIPT(std::string buffer);
        void SCROLLBACK(std::string buffer);
        void SERVER(std::string buffer);
        void SERVLIST(std::string buffer);
        void SET(std::string buffer);
        void SETHOST(std::string buffer);
        void SILENCE(std::string buffer);
        void SQUERY(std::string buffer);
        void SQUIT(std::string buffer);
        void STATS(std::string buffer);
        void STATUSBAR(std::string buffer);
        void TIME(std::string buffer);
        void TOGGLE(std::string buffer);
        void TOPIC(std::string buffer);
        void TRACE(std::string buffer);
        void TS(std::string buffer);
        void UNALIAS(std::string buffer);
        void UNBAN(std::string buffer);
        void UNIGNORE(std::string buffer);
        void UNLOAD(std::string buffer);
        void UNNOTIFY(std::string buffer);
        void UNQUERY(std::string buffer);
        void UNSILENCE(std::string buffer);
        void UPGRADE(std::string buffer);
        void UPTIME(std::string buffer);
        void USERHOST(std::string buffer);
        void VER(std::string buffer);
        void VERSION(std::string buffer);
        void VOICE(std::string buffer);
        void WAIT(std::string buffer);
        void WALL(std::string buffer);
        void WALLOPS(std::string buffer);
        void WHO(std::string buffer);
        void WHOIS(std::string buffer);
        void WHOWAS(std::string buffer);
        void WINDOW(std::string buffer);
};

#endif