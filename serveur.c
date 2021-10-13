#include "serveur.h"

/**
 * @brief Ouverture du socket d'ecoute
 * 
 * @return int 
 */
SOCKET ouverture(struct sockaddr_in server)
{

    memset(&server, '0', sizeof(server));

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    puts("Socket créé");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(1234);

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        printf("bind() error \n");
        exit(1);
    }

    if (listen(sock, 10) == -1)
    {
        printf("listen() error \n");
        exit(1);
    }

    printf("Socket ouvert on ecoute \n");
    return sock;
}

/**
 * @brief On accept la conection d'un client
 * 
 * @param sock 
 * @param client 
 * @return SOCKET 
 */
SOCKET acceptClient(SOCKET sock, struct sockaddr_in client)
{
    puts("Attente de connexion");
    int sizesockaddr = sizeof(struct sockaddr_in);
    SOCKET sockClient = accept(sock, (struct sockaddr *)&client, (socklen_t *)&sizesockaddr);
    puts("Un client est connecté");

    return sockClient;
}

/**
 * @brief On lit et renvoit au client
 * 
 * @param sockClient le sokcet ouvert du client
 */
void serveur_echo(SOCKET sockClient)
{
    int taille = 0;
    char *buffer = malloc(1000 * sizeof(char));

    while ((taille = recv(sockClient, buffer, 1000 * sizeof(char), 0)) > 0)
    {
        write(sockClient, buffer, strlen(buffer));
        memset(buffer, 0, 1000 * sizeof(char));
    }
    free(buffer);
}


////////////////////
//// DATAGRAMME ////
////////////////////

/**
 * @brief Ouverture du socket d'ecoute
 * 
 * @return int 
 */
SOCKET ouvertureUDP(struct sockaddr_in server)
{

    memset(&server, '0', sizeof(server));

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    puts("Socket UDP créé");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(1234);

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        printf("bind() error \n");
        exit(1);
    }

    printf("Socket ouvert on ecoute \n");
    return sock;
}

/**
 * @brief On lit et renvoit au client
 * 
 * @param sockClient le sokcet ouvert du client
 */
void serveur_echoUDP(SOCKET sockClient, struct sockaddr_in client)
{
    int taille = 0; 
    char *buffer = malloc(1000 * sizeof(char));

    while ((taille = recvfrom(sockClient, buffer, 1000 * sizeof(char), MSG_DONTWAIT, (struct sockaddr *)&client, (socklen_t *)sizeof(client)) > 0))
    {
        // sendto(sockClient, )
        write(sockClient, buffer, strlen(buffer));
        memset(buffer, 0, 1000 * sizeof(char));
    }
    free(buffer);
}