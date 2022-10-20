#include "utils.hpp"


static bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    if (s.empty() == 1)
        return (0);
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return it == s.end();
}

int handle_errors(int ac, char **av){
    if (ac != 3){
        std::cerr << "Format is: ./exec <port> <password>" << std::endl;
        return 1;
    }
    std::string number(av[1]);
    if (is_number(number) == 0){ // vérifier les ports inutilisables
        std::cerr << "Second argument as to be a valid number" << std::endl;
        return 1;
    }
    return 0;
}