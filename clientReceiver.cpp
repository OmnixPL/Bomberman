#include "clientReceiver.h"

ClientReceiver::ClientReceiver(int& cliSockfd, char* address, int port) : Receiver(cliSockfd, address, port){}

ClientReceiver::~ClientReceiver()
{
}

void ClientReceiver::defaultBehaviour(char* buffer, size_t len)
{
    std::cout<<"I'm inside method defaultBehaviour and I see packet of type "<<Packet::extractType(buffer, len);
    isExitRequested = true;
}