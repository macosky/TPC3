#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

typedef int SOCKET;

SOCKET ouverture(struct sockaddr_in server);

SOCKET acceptClient(SOCKET sock, struct sockaddr_in client);

void serveur_echo(SOCKET sockClient);

void lecture(SOCKET sock);

////////////////////
//// DATAGRAMME ////
////////////////////

SOCKET ouvertureUDP(struct sockaddr_in server);

void serveur_echoUDP(SOCKET sockServer);

