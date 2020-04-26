#include "include/server.h"
#include "include/packets.h"

Server::Server(int port) {
    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_addr = in6addr_any;
    servaddr.sin6_port = htons(port);

    if ((servSockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }

    if (bind(servSockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) { 
        perror("binding failed"); 
        return; 
    }
}

int Server::test() {
    int readCount;
    char buffer[BUFFERSZ];
    char response[] = "Pozdrawiam.";
    char ip[80];
    std::string xd3 = "ded";
    PacketAuth xd2(xd3, xd3);
    readCount = recvfrom(servSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &cliaddr, &len);
    buffer[readCount] = '\0';
    printf("Client IP: %s: MSG: %s\n", inet_ntop(AF_INET6, &cliaddr.sin6_addr, ip, INET6_ADDRSTRLEN), buffer);
    //sh.addNewClient(cliaddr.sin6_addr, xd2);
    sendto(servSockfd, (const char *)response, strlen(response), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
    printf("Hello message sent.\n");
    return 0;
}