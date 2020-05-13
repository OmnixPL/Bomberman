#include "include/ServerRecv.h"
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include "receiver.h"


ServerRecv::ServerRecv(int& sservSockfd, std::vector<Packet>& ppackets) : Receiver(sservSockfd, ppackets){}

