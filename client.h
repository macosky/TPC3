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

////////////////////
//// DATAGRAMME ////
////////////////////

SOCKET ouvertureUDP();

int client_echoUDP(SOCKET sock, struct sockaddr_in6 server, char *message);

////////////////////
////// STREAM //////
////////////////////

SOCKET ouvertureTCP();

int connectionTCP(SOCKET sock, struct sockaddr_in6 server);

int client_echoTCP(SOCKET sock, char *message);
