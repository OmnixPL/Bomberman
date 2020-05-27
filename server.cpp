// Szymon Malolepszy
// Kacper Kula
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
            if (lobby.isAllReady()) {
                gameLoop();
                lobby.unreadyAll();
            }
            target_time = clock_type::now() + seconds(3);
        }
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
        sh.renewClient(p.addr, *rdy);
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


    auto last_timepoint = clock_type::now(); 
    auto current_timepoint = clock_type::now(); 
    auto target_time = clock_type::now(); 

    // repurpose last active into latest packet counter
    for (unsigned int i = 0; i < cs.size(); i++ ) {
        cs[i].lastActive = 0;
    }

    // main game loop
    while (game.isInProgress()) {
        // grab all packets
        while (true) {
            receiver.grabPacket();
            if (packets.empty()) {
                break;
            }
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

                if (i != MAX_PLAYERS && act->getNo() > cs[i].lastActive) {
                    if (act->getBombPlacement() == true)
                        game.placeBomb(i);

                    game.updateIntent(i, act->getAction());

                    cs[i].lastActive = act->getNo();
                }
            }
            else {
                packets.pop();
            }
        }
        game.tick();

        std::this_thread::sleep_until(target_time);
        target_time += milliseconds(TICKTIME);
        current_timepoint = clock_type::now(); 

        printf("\033c");
        std::cout << "TICK TIME: \t" << std::chrono::duration_cast<std::chrono::milliseconds>(current_timepoint - last_timepoint).count() << std::endl;
        game.printGamefield();
        
        last_timepoint = current_timepoint;
        sender.sendGameAll(game);
    }

    // set last active back into time counter (otherwise lobby will kick all players)
    for (unsigned int i = 0; i < cs.size(); i++ ) {
        cs[i].lastActive = time(NULL);
    }
}