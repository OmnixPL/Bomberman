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
    char ip[INET6_ADDRSTRLEN];
    
    readCount = recvfrom(servSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &cliaddr, &len);
    buffer[readCount] = '\0';
    printf("Client IP: %s MSG: %s\n", inet_ntop(AF_INET6, &cliaddr.sin6_addr, ip, INET6_ADDRSTRLEN), buffer);
    sendto(servSockfd, (const char *)response, strlen(response), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
    printf("Hello message sent.\n");

    readCount = recvfrom(servSockfd, buffer, 512, 0, (struct sockaddr *) &cliaddr, &len);
    Packet p1(buffer, 512);
    std::cout << "Incoming packet type: " << p1.getType() << std::endl; 
    std::cout << "User: " << p1.getUser() << std::endl;
    std::cout << "NO: " << p1.getNo() << std::endl << std::endl;
    
    readCount = recvfrom(servSockfd, buffer, 512, 0, (struct sockaddr *) &cliaddr, &len);
    PacketAck ack(buffer, 512);
    std::cout << "Incoming packet type: " << ack.getType() << std::endl; 
    std::cout << "User: " << ack.getUser() << std::endl;
    std::cout << "NO: " << ack.getNo() << std::endl;
    std::cout << "noAck: " << ack.getNoAck() << std::endl << std::endl;

    readCount = recvfrom(servSockfd, buffer, 512, 0, (struct sockaddr *) &cliaddr, &len);
    PacketAuth auth(buffer, 512);
    std::cout << "Incoming packet type: " << auth.getType() << std::endl; 
    std::cout << "User: " << auth.getUser() << std::endl;
    std::cout << "NO: " << auth.getNo() << std::endl;
    std::cout << "Pass: " << auth.getPassword() << std::endl << std::endl;

    readCount = recvfrom(servSockfd, buffer, 512, 0, (struct sockaddr *) &cliaddr, &len);
    PacketRdy rdy(buffer, 512);
    std::cout << "Incoming packet type: " << rdy.getType() << std::endl; 
    std::cout << "User: " << rdy.getUser() << std::endl;
    std::cout << "NO: " << rdy.getNo() << std::endl;
    std::cout << "rdy: " << rdy.getRdy() << std::endl << std::endl;

    readCount = recvfrom(servSockfd, buffer, 512, 0, (struct sockaddr *) &cliaddr, &len);
    PacketRenew renew(buffer, 512);
    std::cout << "Incoming packet type: " << renew.getType() << std::endl; 
    std::cout << "User: " << renew.getUser() << std::endl;
    std::cout << "NO: " << renew.getNo() << std::endl << std::endl;

    readCount = recvfrom(servSockfd, buffer, 512, 0, (struct sockaddr *) &cliaddr, &len);
    PacketDisconnect dc(buffer, 512);
    std::cout << "Incoming packet type: " << dc.getType() << std::endl; 
    std::cout << "User: " << dc.getUser() << std::endl;
    std::cout << "NO: " << dc.getNo() << std::endl << std::endl;

    sleep(1);
    PacketAns ans(TIMEOUT);
    ans.serialize(buffer, 512);
    sendto(servSockfd, (const char *)buffer, sizeof(ans), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 

    std::vector<std::string> ppp;
    std::vector<bool> rrr;
    ppp.push_back("Pap");
    rrr.push_back(false);
    ppp.push_back("KEK");
    rrr.push_back(true);

    sleep(1);
    PacketLobby l(ppp, rrr);
    l.serialize(buffer, 512);
    sendto(servSockfd, (const char *)buffer, sizeof(ans), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);

    return 0;
}

int Server::selfTest() {
    std::string xd3 = "";
    PacketAuth xd2(xd3);
    PacketRenew renew;
    PacketDisconnect disc;
    PacketRdy rdy(true);
    std::cout << "Password: >" << password << "<" << std::endl; 
    sh.addNewClient(cliaddr.sin6_addr, xd2);
    //sleep(3);
    //sh.renewClient(cliaddr.sin6_addr, renew);
    //sleep(12);
    //sh.checkTimeouts();
    //sh.removeClient(cliaddr.sin6_addr, disc);
    //lobby.clientReady(cliaddr.sin6_addr, rdy);
    //lobby.isAllReady();
    return 0;
}