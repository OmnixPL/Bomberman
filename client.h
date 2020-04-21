#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE
#include <string.h>
#include <unistd.h> // close
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define BUFFERSZ 256

int client(char *ipVersion, char *addr, char *port);