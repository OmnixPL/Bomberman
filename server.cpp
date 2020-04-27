#include "include/server.h"
#include "include/packets.h"

Server::Server(int port, std::string ppassword) : password(ppassword) {
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

int Server::testConnection() {
    int readCount;
    char buffer[BUFFERSZ];
    char response[] = "Pozdrawiam.";
    char ip[80];
    
    readCount = recvfrom(servSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &cliaddr, &len);
    buffer[readCount] = '\0';
    printf("Client IP: %s MSG: %s\n", inet_ntop(AF_INET6, &cliaddr.sin6_addr, ip, INET6_ADDRSTRLEN), buffer);
    sendto(servSockfd, (const char *)response, strlen(response), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
    printf("Hello message sent.\n");
    return 0;
}

int Server::selfTest() {
    std::string xd3 = "";
    PacketAuth xd2(xd3);
    PacketRenew renew;
    PacketDisconnect disc;

    std::cout << "Password: >" << password << "<" << std::endl; 
    sh.addNewClient(cliaddr.sin6_addr, xd2);
    sleep(3);
    sh.renewClient(cliaddr.sin6_addr, renew);
    //sleep(12);
    //sh.checkTimeouts();
    sh.removeClient(cliaddr.sin6_addr, disc);
    return 0;
}