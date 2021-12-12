#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <netdb.h>
#include <signal.h>

typedef int SOCKET;

////////////////////
////// STREAM //////
////////////////////

SOCKET ouvertureTCP(struct sockaddr_in6 server, int port);

SOCKET acceptClientTCP(SOCKET sock, struct sockaddr_in6 client);

void serveur_echoTCP(SOCKET sockClient);

////////////////////
//// DATAGRAMME ////
////////////////////

SOCKET ouvertureUDP(struct sockaddr_in6 server, int port);

void serveur_echoUDP(SOCKET sockServer);
