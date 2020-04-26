#include "client.h"

Client::Client(int version, char* addr, int port) {
    servaddr.sin6_family = AF_INET6; /* change for ipv6 */
    inet_pton(AF_INET6, addr, &servaddr.sin6_addr);
    servaddr.sin6_port = htons(port);

    if ((cliSockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }
}

int Client::test() {
    int readCount;
    char buffer[BUFFERSZ];
    char msg[] = "Dzien dobry.";

    sendto(cliSockfd, (const char *)msg, strlen(msg), 0, (const struct sockaddr *) &servaddr, len); 
    printf("Hello message sent.\n");
    readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &servaddr, &len); 
    buffer[readCount] = '\0';
    printf("Server: %s\n", buffer);
    close(cliSockfd);
    return 0;
}
