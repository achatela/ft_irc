#include "utils.hpp"

int create_socket(void){
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
	int addrlen = sizeof(address);
    int opt = 1;

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(6667); // remplacer par av[1]
    bind(sockfd, (struct sockaddr*)&address, sizeof(address));
    listen(sockfd, 10); // check la doc 10 = file d'attente
	accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    return (sockfd);
}