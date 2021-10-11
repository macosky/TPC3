#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int SOCKET;


SOCKET ouverture(struct sockaddr_in *server);

int connection(SOCKET sock,struct sockaddr_in server);

void lecture(SOCKET sock);

void client_echo(SOCKET sock);


