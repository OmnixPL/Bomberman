#include <iostream>
#include <thread>
#include <mutex>

#include "client.h"
#include "include/packets.h"

std::mutex globalMutex;

Client::Client(int version, char* addr, int port, std::string filepath) {
    servaddr.sin6_family = AF_INET6; /* change for ipv6 */
    inet_pton(AF_INET6, addr, &servaddr.sin6_addr);
    servaddr.sin6_port = htons(port);

    timeout.tv_sec = 2 * 60; // 2 min timeout for socket
    timeout.tv_usec = 0;

    if ((cliSockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }

    receiver = new ClientReceiver(cliSockfd, addr, port, timeout);
    sender = new ClientSender(cliSockfd, addr, port, globalMutex);
    controller = new Controller(filepath, sender);
}

int Client::test() {
    int readCount;
    char buffer[BUFFERSZ];
    char msg[] = "Dzien dobry.";
    std::string pass = "Pap";
    sendto(cliSockfd, (const char *)msg, strlen(msg), 0, (const struct sockaddr *) &servaddr, len); 
    printf("Hello message sent.\n");
    readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &servaddr, &len); 
    buffer[readCount] = '\0';
    printf("Server: %s\n", buffer);

    std::string s = "TESTER";
    char b[512];

    Packet::userDefault = "TUTU";
    Packet p1(GAME);
    PacketAck ack(666);
    PacketAuth auth(s);
    PacketRdy rdy(true);
    PacketRenew renew;
    PacketDisconnect dc;
    // ANS I LOBBY WYSYŁA TYLKO SERVER

    p1.serialize(b, 512);
    sendto(cliSockfd, b, sizeof(p1), 0, (const struct sockaddr *) &servaddr, len);
    sleep(1); 
    ack.serialize(b, 512);
    sendto(cliSockfd, b, sizeof(ack), 0, (const struct sockaddr *) &servaddr, len);
    sleep(1);
    auth.serialize(b, 512);
    sendto(cliSockfd, b, sizeof(auth), 0, (const struct sockaddr *) &servaddr, len);
    sleep(1);
    rdy.serialize(b, 512);
    sendto(cliSockfd, b, sizeof(rdy), 0, (const struct sockaddr *) &servaddr, len);
    sleep(1);
    renew.serialize(b, 512);
    sendto(cliSockfd, b, sizeof(renew), 0, (const struct sockaddr *) &servaddr, len);
    sleep(1);
    dc.serialize(b, 512);
    sendto(cliSockfd, b, sizeof(dc), 0, (const struct sockaddr *) &servaddr, len);

    readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &servaddr, &len);
    PacketAns ans(buffer, 512);
    std::cout << "Incoming packet type: " << ans.getType() << std::endl; 
    std::cout << "User: " << ans.getUser() << std::endl;
    std::cout << "NO: " << ans.getNo() << std::endl;
    std::cout << "Ans: " << ans.getAns() << std::endl << std::endl;

    readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &servaddr, &len);
    PacketLobby l(buffer, 512);
    std::cout << "Incoming packet type: " << l.getType() << std::endl; 
    std::cout << "User: " << l.getUser() << std::endl;
    std::cout << "NO: " << l.getNo() << std::endl;
    for ( size_t i = 0; i < l.players.size(); i++) {
        std::cout << "Player: " << l.players[i] << " rdy: " << l.rdy[i] << std::endl << std::endl;
    }

    close(cliSockfd);
    return 0;
}

void Client::test2()
{
    std::cout<<"Client performing test 2"<<std::endl;
    (*receiver)();
}

void Client::test3()
{
    int readCount;
    char buffer[BUFFERSZ];
    char msg[] = "Dzien dobry.";
    std::string pass = "Pap";
    sendto(cliSockfd, (const char *)msg, strlen(msg), 0, (const struct sockaddr *) &servaddr, len); 
    printf("Hello message sent.\n");
    (*receiver)();
    
}

void Client::test4()
{
    (*sender)();
    // receiver->serve();
}

void Client::test5()
{
    std::thread threadObj( *sender );
    std::thread receiverThread( *receiver );
    threadObj.join();
    receiverThread.join();
}
