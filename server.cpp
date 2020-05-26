#include "include/server.h"
#include "include/packets.h"

using namespace std::literals;
using clock_type = std::chrono::high_resolution_clock;

void printPacket(std::shared_ptr<Packet> p) {
    std::cout << "Incoming packet type: " << p->getType() << std::endl; 
    std::cout << "User: " << p->getUser() << std::endl;
    std::cout << "NO: " << p->getNo() << std::endl;
}

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

void Server::lobbyLoop() {
    auto target_time = clock_type::now() + seconds(1);
    while (true) {
        while (usePacket());

        sh.checkTimeouts();
        
        if (target_time < clock_type::now()) {
            sender.sendLobbyAll();
            target_time = clock_type::now() + seconds(1);
        }

        if (lobby.isAllReady())
            gameLoop();
    }
}

bool Server::usePacket() {
    packet_t type;

    receiver.grabPacket();
    if ( packets.empty() )
        return false;
    type = packets.front().packet->getType();
    if ( type == ACK) {
        PacketContainer p = std::move(packets.front());
        packets.pop();
        std::shared_ptr<PacketAck> ack = std::dynamic_pointer_cast<PacketAck>(p.packet);

        printPacket(ack);
        std::cout << "noAck: " << ack->getNoAck() << std::endl << std::endl;
    }
    else if ( type == AUTH) {
        PacketContainer p = std::move(packets.front());
        packets.pop();
        std::shared_ptr<PacketAuth> auth = std::dynamic_pointer_cast<PacketAuth>(p.packet);
        ans_t answer;
        answer = sh.addNewClient(p.addr, *auth);
        sender.sendAns(p.addr, answer);
        sender.sendLobbyAll();
    }
    else if ( type == RDY) {
        PacketContainer p = std::move(packets.front());
        packets.pop();
        std::shared_ptr<PacketRdy> rdy = std::dynamic_pointer_cast<PacketRdy>(p.packet);

        lobby.clientReady(p.addr, *rdy);
        sender.sendAck(p.addr, rdy->getNo());
        sender.sendLobbyAll();
    }
    else if ( type == RENEW) {
        PacketContainer p = std::move(packets.front());
        packets.pop();
        std::shared_ptr<PacketRenew> renew = std::dynamic_pointer_cast<PacketRenew>(p.packet);

        sh.renewClient(p.addr, *renew);
    }
    else if ( type == DISCONNECT) {
        PacketContainer p = std::move(packets.front());
        packets.pop();
        std::shared_ptr<PacketDisconnect> dc = std::dynamic_pointer_cast<PacketDisconnect>(p.packet);

        sh.removeClient(p.addr, *dc);
    }
    else {
        packets.pop();
    }
    return true;
}

void Server::gameLoop() {
    packet_t type;
    Game game(cs.size());

    auto when_started = clock_type::now(); 
    auto target_time = when_started;
    // main game loop
    while (game.isInProgress()) {
        target_time += milliseconds(TICKTIME);
        // grab all packets
        while (true) {
            receiver.grabPacket();
            if (packets.empty())
                break;

            type = packets.front().packet->getType();
            if (type == ACTION) {
                PacketContainer p = std::move(packets.front());
                packets.pop();
                std::shared_ptr<PacketAction> act = std::dynamic_pointer_cast<PacketAction>(p.packet);


                ClientSession client(p.addr, act->getUser(), 0);
                int i;
                for (i = 0; i < MAX_PLAYERS; i++) {
                    if (cs[i] == client)
                        break;
                }

                if (i == MAX_PLAYERS)
                    continue;

                if (act->getNo() < cs[i].lastActive)
                    continue;

                if (act->getBombPlacement() == true)
                    game.placeBomb(i);

                game.updateIntent(i, act->getAction());

                cs[i].lastActive = act->getNo();
            }
            else {
                packets.pop();
            }

        }
        game.tick();
        std::this_thread::sleep_until(target_time);
        target_time += 10ms;

        sender.sendGameAll(game);
    }
}

void Server::testLoop() {
    password = "Haselko";
    packet_t type;
    int i = 8000000;

    // this can be a server LOBBY loop (except receiver can grab packets on its own)
    // while loop isnt endless because i need to send lobby status sometime and now its only one thread
    while (i--) {
        receiver.grabPacket();
        if ( packets.empty() )
            continue;
        type = packets.front().packet->getType();
        if ( type == ACK) {
            PacketContainer p = std::move(packets.front());
            packets.pop();
            std::shared_ptr<PacketAck> ack = std::dynamic_pointer_cast<PacketAck>(p.packet);

            printPacket(ack);
            std::cout << "noAck: " << ack->getNoAck() << std::endl << std::endl;
        }
        else if ( type == AUTH) {
            PacketContainer p = std::move(packets.front());
            packets.pop();
            std::shared_ptr<PacketAuth> auth = std::dynamic_pointer_cast<PacketAuth>(p.packet);
            ans_t answer;
            answer = sh.addNewClient(p.addr, *auth);
            sender.sendAns(p.addr, answer);
        }
        else if ( type == RDY) {
            PacketContainer p = std::move(packets.front());
            packets.pop();
            std::shared_ptr<PacketRdy> rdy = std::dynamic_pointer_cast<PacketRdy>(p.packet);

            lobby.clientReady(p.addr, *rdy);
            sender.sendAck(p.addr, rdy->getNo());
        }
        else if ( type == RENEW) {
            PacketContainer p = std::move(packets.front());
            packets.pop();
            std::shared_ptr<PacketRenew> renew = std::dynamic_pointer_cast<PacketRenew>(p.packet);

            sh.renewClient(p.addr, *renew);
        }
        else if ( type == DISCONNECT) {
            PacketContainer p = std::move(packets.front());
            packets.pop();
            std::shared_ptr<PacketDisconnect> dc = std::dynamic_pointer_cast<PacketDisconnect>(p.packet);

            sh.removeClient(p.addr, *dc);
        }
    }

    std::cout << "CLIENTS: ";
    for (ClientSession c : cs) {
        std::cout << "Client: " << c.name << std::endl;
    }
    sender.sendLobbyAll();

    return;
}

// void Server::test2()
// {
//     int readCount;
//     char buffer[BUFFERSZ];
//     char response[] = "Pozdrawiam.";
//     char ip[INET6_ADDRSTRLEN];

//     int i = 10;
//     std::cout<<"Sending 10 packets"<<std::endl;
//     while (i--)
//     {
//         sendto(servSockfd, (const char *)response, strlen(response), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
//         std::cout<<"Sent packet "<<i<<std::endl;
//     }
// }

void Server::test3()
{
    for(int i = 0; i < 10; i++)
    {
        ;
    }
}

// ********************************** OLD TESTS ***********************

int Server::selfTest() {
    std::string xd3 = "";
    Packet::userDefault = "Add client";
    PacketAuth xd2(xd3);
    PacketRenew renew;
    PacketDisconnect disc;
    PacketRdy rdy(true);
    std::cout << "Password: >" << password << "<" << std::endl; 
    sh.addNewClient(cliaddr, xd2);
    sleep(3);
    sh.renewClient(cliaddr, renew);
    sleep(12);
    sh.checkTimeouts();
    sh.removeClient(cliaddr, disc);
    lobby.clientReady(cliaddr, rdy);
    lobby.isAllReady();
    return 0;
}

int Server::testCon() {
    int readCount;
    char buffer[BUFFERSZ];
    char response[] = "Pozdrawiam.";
    char ip[INET6_ADDRSTRLEN];

    readCount = recvfrom(servSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &cliaddr, &len);
    buffer[readCount] = '\0';
    printf("Client IP: %s MSG: %s\n", inet_ntop(AF_INET6, &cliaddr.sin6_addr, ip, INET6_ADDRSTRLEN), buffer);
    sendto(servSockfd, (const char *)response, strlen(response), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
    printf("Hello message sent.\n");

    password = "Haselko";

    while (!receiver.grabPacket())
        usleep(600000);
    PacketContainer p3 = std::move(packets.front());
    packets.pop();
    std::shared_ptr<PacketAuth> auth = std::dynamic_pointer_cast<PacketAuth>(p3.packet);

    // printPacket(auth);
    // std::cout << "Pass: " << auth->getPassword() << std::endl << std::endl;
    sh.addNewClient(p3.addr, *auth);

    while (!receiver.grabPacket())
        usleep(600000);
    PacketContainer p = std::move(packets.front());
    packets.pop();
    std::shared_ptr<PacketAck> ack = std::dynamic_pointer_cast<PacketAck>(p.packet);
    
    printPacket(ack);
    std::cout << "noAck: " << ack->getNoAck() << std::endl << std::endl;

    while (!receiver.grabPacket())
        usleep(600000);
    p = std::move(packets.front());
    packets.pop();
    std::shared_ptr<PacketRdy> rdy = std::dynamic_pointer_cast<PacketRdy>(p.packet);

    // printPacket(rdy);
    // std::cout << "rdy: " << rdy->getRdy() << std::endl << std::endl;
    lobby.clientReady(p.addr, *rdy);
    sender.sendAck(p.addr, rdy->getNo());

    while (!receiver.grabPacket())
        usleep(600000);
    p = std::move(packets.front());
    packets.pop();
    std::shared_ptr<PacketRenew> renew = std::dynamic_pointer_cast<PacketRenew>(p.packet);

    // printPacket(renew);
    // std::cout << std::endl;
    sh.renewClient(p.addr, *renew);

    while (!receiver.grabPacket())
        usleep(600000);
    p = std::move(packets.front());
    packets.pop();
    std::shared_ptr<PacketDisconnect> dc = std::dynamic_pointer_cast<PacketDisconnect>(p.packet);

    // printPacket(dc);
    // std::cout << std::endl;
    sh.removeClient(p.addr, *dc);

    sleep(1);
    PacketAns ans(TIMEOUT);
    ans.serialize(buffer, BUFFERSZ);
    sendto(servSockfd, (const char *)buffer, sizeof(ans), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 

    std::vector<std::string> ppp;
    std::vector<bool> rrr;
    ppp.push_back("Pap");
    rrr.push_back(false);
    ppp.push_back("KEK");
    rrr.push_back(true);

    sleep(1);
    PacketLobby l(ppp, rrr);
    l.serialize(buffer, BUFFERSZ);
    sendto(servSockfd, (const char *)buffer, sizeof(ans), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);

    return 0;
}