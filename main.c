#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE
#include <string.h>
#include <unistd.h> // close
// idk czy wszystkie są potrzebne
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_PORT 57312
#define BUFFERSZ 256

int server()
{
    int servSockfd = -1;
    struct sockaddr_in servaddr = {}, cliaddr = {}; // maybe change client to sockaddr_storage
    socklen_t len = sizeof(cliaddr);
    int readCount;
    char buffer[BUFFERSZ];
    char response[] = "Pozdrawiam.";

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(SERV_PORT);

    if ((servSockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE); 
    }

    if (bind(servSockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) { 
        perror("binding failed"); 
        exit(EXIT_FAILURE); 
    } 

    readCount = recvfrom(servSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &cliaddr, &len); 
    buffer[readCount] = '\0';
    printf("Client: %s\n", buffer); 
    sendto(servSockfd, (const char *)response, strlen(response), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
    printf("Hello message sent.\n");
    return 0;
}

int client(char *ipVersion, char *addr, char *port)
{
    printf("IP: %s, ADDRESS: %s, PORT: %s\n", ipVersion, addr, port);
/* IPVERSION NOT IMPLEMENTED, ipv4 only now */
    int cliSockfd = -1;
    struct sockaddr_in servaddr = {}, cliaddr = {}; /* change for ipv6 */
    socklen_t len = sizeof(servaddr);
    int readCount;
    char buffer[BUFFERSZ];
    char msg[] = "Dzien dobry.";

    servaddr.sin_family = AF_INET; /* change for ipv6 */
    inet_pton(AF_INET, addr, &servaddr.sin_addr);
    servaddr.sin_port = htons(atoi(port));

    if ((cliSockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { /* change for ipv6 */
        perror("socket creation failed");
        exit(EXIT_FAILURE); 
    }
/*
    if (bind(cliSockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) { 
        perror("binding failed"); 
        exit(EXIT_FAILURE); 
    } */

    sendto(cliSockfd, (const char *)msg, strlen(msg), 0, (const struct sockaddr *) &servaddr, len); 
    printf("Hello message sent.\n");
    readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &servaddr, &len); 
    buffer[readCount] = '\0';
    printf("Server: %s\n", buffer);
    close(cliSockfd);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        if (!strcmp(argv[1], "server")) {
            server();
        }
        else if (argc > 4 && !strcmp(argv[1], "client")) {
            client(argv[2], argv[3], argv[4]);
        }
    }
    else {
        printf("Arguments needed: server OR client IPv4/IPv6 IP_ADDRESS PORT\n");
        exit(EXIT_FAILURE);
    }    
    return 0;
}