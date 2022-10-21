// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>

#define PORT 6667

int main(int argc, char const* argv[])
{
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    char addr[40];
    gethostname(addr, 40);
    struct addrinfo hints, *servinfo;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    int rv;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    rv = getaddrinfo( addr , 0 , &hints , &servinfo);
    serv_addr.sin_addr = ((struct sockaddr_in *) servinfo->ai_addr)->sin_addr;

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    // if (inet_pton(AF_INET, "e3r12p5.clusters.42paris.fr", &serv_addr.sin_addr)
    //     <= 0) {
    //     printf(
    //         "\nInvalid address/ Address not supported \n");
    //     return -1;
    // }
    printf("avant connect\n");
    if ((client_fd
        = connect(sock, (struct sockaddr*)&serv_addr,
                sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    sleep(5);
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);

    // closing the connected socket
    close(client_fd);
    return 0;
}