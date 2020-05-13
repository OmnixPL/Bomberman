#include "clientReceiver.h"

ClientReceiver::ClientReceiver(int& sservSockfd, std::vector<Packet>& ppackets) : Receiver(sservSockfd, ppackets){}

ClientReceiver::~ClientReceiver()
{
}

void ClientReceiver::defaultBehaviour()
{
    ;
}