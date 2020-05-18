#include "clientReceiver.h"

ClientReceiver::ClientReceiver(int& cliSockfd, char* address, int port, struct timeval timeout) : Receiver(cliSockfd, address, port, timeout){}

ClientReceiver::~ClientReceiver()
{
}

void ClientReceiver::defaultBehaviour(char* buffer, size_t len)
{
    std::cout<<"I'm inside method defaultBehaviour and I see packet of type "<<Packet::extractType(buffer, len);
    isExitRequested = true;
}