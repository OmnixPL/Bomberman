#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

#include "client.h"
#include "include/packets.h"

// grabs from server.cpp 
void printPacket(std::shared_ptr<Packet> p);

Client::Client(
            int version, 
            char* addr, 
            int port, 
            std::string username, 
            std::string pathToMoves,
            int noSecondsBetweenMoves) {
    servaddr.sin6_family = AF_INET6; /* change for ipv6 */
    inet_pton(AF_INET6, addr, &servaddr.sin6_addr);
    servaddr.sin6_port = htons(port);

    if ((cliSockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }

    model = new Model(username);
    
    sender = new ClientSender(cliSockfd, servaddr, queueMutex, &isExitRequested);
    receiver = new ClientReceiver(cliSockfd, servaddr, &isExitRequested);
    controller = new Controller(pathToMoves,sender, model, &isExitRequested, noSecondsBetweenMoves);
}

void Client::run()
{
    std::thread receiverThread(&ClientReceiver::operator(), receiver);
    // std::thread senderThread(&ClientSender::operator(), sender);
    // std::thread controllerThread(&Controller::operator(), controller);
    // senderThread.join();
    receiverThread.join();
    // controllerThread.join();
    
}

void Client::runSequential()
{   
    while (!isExitRequested || sender->isQueueNotEmpty())
    {
        sender->runOnce();
        receiver->runOnce();
        controller->runOnce();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    
}

// use with testCon in server
void Client::testSender() {
    int readCount;
    char buffer[BUFFERSZ];
    char msg[] = "Dzien dobry.";
    std::string pass = "Haselko";
    sendto(cliSockfd, (const char *)msg, strlen(msg), 0, (const struct sockaddr *) &servaddr, len); 
    printf("Hello message sent.\n");
    readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &servaddr, &len); 
    buffer[readCount] = '\0';
    printf("Server: %s\n", buffer);

    Packet::userDefault = "TUTU";

    sender->sendAuth(pass);
    usleep(300000); 

    sender->sendAck(567);
    usleep(300000); 

    sender->sendRdy(true);
    usleep(300000); 
    
    readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &servaddr, &len);
    PacketAck ack(buffer, BUFFERSZ);    
    std::cout << "Incoming packet type: " << ack.getType() << std::endl; 
    std::cout << "User: " << ack.getUser() << std::endl;
    std::cout << "NO: " << ack.getNo() << std::endl;
    std::cout << "noAck: " << ack.getNoAck() << std::endl << std::endl;

    sender->sendRenew();
    usleep(300000); 
    
    sender->sendDisconnect();

    readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &servaddr, &len);
    PacketAns ans(buffer, BUFFERSZ);
    std::cout << "Incoming packet type: " << ans.getType() << std::endl; 
    std::cout << "User: " << ans.getUser() << std::endl;
    std::cout << "NO: " << ans.getNo() << std::endl;
    std::cout << "Ans: " << ans.getAns() << std::endl << std::endl;

    readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &servaddr, &len);
    PacketLobby l(buffer, BUFFERSZ);
    std::cout << "Incoming packet type: " << l.getType() << std::endl; 
    std::cout << "User: " << l.getUser() << std::endl;
    std::cout << "NO: " << l.getNo() << std::endl;
    for ( size_t i = 0; i < l.players.size(); i++) {
        std::cout << "Player: " << l.players[i] << " rdy: " << l.rdy[i] << std::endl << std::endl;
    }


    close(cliSockfd);
    return;
}

void Client::testLoop() {
    int readCount;
    char buffer[BUFFERSZ];
    std::string pass = "Haselko";
    Packet::userDefault = "TUTU";

    sender->sendAuth(pass);
    usleep(300000); 

    // usually you should check the type (and if any packets actually exists!) but now its expected to be ans
    std::shared_ptr<PacketAns> ans = std::dynamic_pointer_cast<PacketAns>(receiver->grabPacket());
    printPacket(ans);
    std::cout << "Ans: " << ans->getAns() << std::endl << std::endl;

    sender->sendAck(567);
    usleep(300000); 

    sender->sendRdy(true);
    usleep(300000); 
    
    std::shared_ptr<PacketAck> ack = std::dynamic_pointer_cast<PacketAck>(receiver->grabPacket()); 
    printPacket(ack);
    std::cout << "noAck: " << ack->getNoAck() << std::endl << std::endl;

    sender->sendRenew();
    usleep(300000); 
    
    // commented out to see working lobby
    // sender.sendDisconnect();

    std::shared_ptr<PacketLobby> l; 
    while ( (l = std::dynamic_pointer_cast<PacketLobby>(receiver->grabPacket())) == nullptr )
        ;
    printPacket(l);
    for ( size_t i = 0; i < l->players.size(); i++) {
        std::cout << "Player: " << l->players[i] << " rdy: " << l->rdy[i] << std::endl << std::endl;
    }


    close(cliSockfd);
    return;
}

// ********************************** OLD TESTS ***********************

// void Client::test2()
// {
//     std::cout<<"Client performing test 2"<<std::endl;
//     (*receiver)();
// }

// void Client::test3()
// {
//     int readCount;
//     char buffer[BUFFERSZ];
//     char msg[] = "Dzien dobry.";
//     std::string pass = "Pap";
//     sendto(cliSockfd, (const char *)msg, strlen(msg), 0, (const struct sockaddr *) &servaddr, len); 
//     printf("Hello message sent.\n");
//     (*receiver)();
    
// }

// void Client::test4()
// {
//     (*sender)();
//     // receiver->serve();
// }

// void Client::test5()
// {
//     std::thread threadObj( *sender );
//     std::thread receiverThread( *receiver );
//     threadObj.join();
//     receiverThread.join();
// }


// use with testCon in server (outdated)
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
    char b[BUFFERSZ];

    Packet::userDefault = "TUTU";
    PacketAck ack(666);
    PacketAuth auth(s);
    PacketRdy rdy(true);
    PacketRenew renew;
    PacketDisconnect dc;
    // ANS I LOBBY WYSYŁA TYLKO SERVER

    ack.serialize(b, BUFFERSZ);
    sendto(cliSockfd, b, sizeof(ack), 0, (const struct sockaddr *) &servaddr, len);
    usleep(300000); 
    auth.serialize(b, BUFFERSZ);
    sendto(cliSockfd, b, sizeof(auth), 0, (const struct sockaddr *) &servaddr, len);
    usleep(300000); 
    rdy.serialize(b, BUFFERSZ);
    sendto(cliSockfd, b, sizeof(rdy), 0, (const struct sockaddr *) &servaddr, len);
    usleep(300000); 
    renew.serialize(b, BUFFERSZ);
    sendto(cliSockfd, b, sizeof(renew), 0, (const struct sockaddr *) &servaddr, len);
    usleep(300000); 
    dc.serialize(b, BUFFERSZ);
    sendto(cliSockfd, b, sizeof(dc), 0, (const struct sockaddr *) &servaddr, len);

    readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &servaddr, &len);
    PacketAns ans(buffer, BUFFERSZ);
    std::cout << "Incoming packet type: " << ans.getType() << std::endl; 
    std::cout << "User: " << ans.getUser() << std::endl;
    std::cout << "NO: " << ans.getNo() << std::endl;
    std::cout << "Ans: " << ans.getAns() << std::endl << std::endl;

    readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &servaddr, &len);
    PacketLobby l(buffer, BUFFERSZ);
    std::cout << "Incoming packet type: " << l.getType() << std::endl; 
    std::cout << "User: " << l.getUser() << std::endl;
    std::cout << "NO: " << l.getNo() << std::endl;
    for ( size_t i = 0; i < l.players.size(); i++) {
        std::cout << "Player: " << l.players[i] << " rdy: " << l.rdy[i] << std::endl << std::endl;
    }

    close(cliSockfd);
    return 0;
}
