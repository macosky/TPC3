#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <netdb.h>

typedef int SOCKET;

////////////////////
////// STREAM //////
////////////////////

SOCKET ouvertureTCP(struct sockaddr_in server);

SOCKET acceptClientTCP(SOCKET sock, struct sockaddr_in client);

void serveur_echoTCP(SOCKET sockClient);

////////////////////
//// DATAGRAMME ////
////////////////////

SOCKET ouvertureUDP(struct sockaddr_in server);

void serveur_echoUDP(SOCKET sockServer);
