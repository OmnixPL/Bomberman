#include "client.h"

int client(char *ipVersion, char *addr, char *port)
{
    printf("IPver: %s, ADDRESS: %s, PORT: %s\n", ipVersion, addr, port);
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
