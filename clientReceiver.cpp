#include "clientReceiver.h"

ClientReceiver::ClientReceiver(int& cliSockfd, char* address, int port) : Receiver(cliSockfd, address, port){}

ClientReceiver::~ClientReceiver()
{
}

void ClientReceiver::defaultBehaviour()
{
    ;
}