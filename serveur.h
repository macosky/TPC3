#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int SOCKET;

SOCKET ouverture(struct sockaddr_in server);

SOCKET acceptClient();

void serveur_echo(SOCKET sockClient);

void lecture(SOCKET sock);
