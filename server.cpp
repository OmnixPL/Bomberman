#include "server.h"

int server()
{
    int servSockfd = -1;
    struct sockaddr_in servaddr = {}, cliaddr = {}; // maybe change client to sockaddr_storage
    socklen_t len = sizeof(cliaddr);
    int readCount;
    char buffer[BUFFERSZ];
    char response[] = "Pozdrawiam.";

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(SERV_PORT);

    if ((servSockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE); 
    }

    if (bind(servSockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) { 
        perror("binding failed"); 
        exit(EXIT_FAILURE); 
    } 

    readCount = recvfrom(servSockfd, buffer, BUFFERSZ, 0, (struct sockaddr *) &cliaddr, &len); 
    buffer[readCount] = '\0';
    printf("Client: %s\n", buffer); 
    sendto(servSockfd, (const char *)response, strlen(response), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
    printf("Hello message sent.\n");
    return 0;
}