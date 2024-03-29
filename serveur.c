#include "serveur.h"

/**
 * @brief Donnes les informations sur le client
 * 
 * @param client 
 */
void getINFO(struct sockaddr_in6 client)
{
    //char *client_ip = inet_ntoa(client.sin6_addr);

    char str[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &client.sin6_addr, str, INET6_ADDRSTRLEN);
    printf("Ip source : %s\n", str);

    char host[128];
    getnameinfo((struct sockaddr *)&client, sizeof(client), host, sizeof(host), NULL, 0, 0);
    printf("Hostname source : %s\n", host);
}

////////////////////
////// STREAM //////
////////////////////

/**
 * @brief Ouverture du socket d'ecoute
 * 
 * @return int 
 */
SOCKET ouvertureTCP(struct sockaddr_in6 server, int port)
{

    memset(&server, '0', sizeof(server));

    SOCKET sock = socket(AF_INET6, SOCK_STREAM, 0);

    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    puts("Socket créé");

    server.sin6_family = AF_INET6;
    server.sin6_addr = in6addr_any;
    server.sin6_port = htons(port);

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
SOCKET acceptClientTCP(SOCKET sock, struct sockaddr_in6 client)
{
    sleep(1);
    puts("------Attente de connexion------");
    int sizesockaddr = sizeof(struct sockaddr_in6);
    SOCKET sockClient = accept(sock, (struct sockaddr *)&client, (socklen_t *)&sizesockaddr);

    puts("Un client est connecté");

    getINFO(client);

    return sockClient;
}

/**
 * @brief On lit et renvoit au client
 * 
 * @param sockClient le sokcet ouvert du client
 */
void serveur_echoTCP(SOCKET sockClient)
{
    char *buffer = malloc(1000 * sizeof(char));
    memset(buffer, 0, 1000 * sizeof(char));
    int stat;

    int taille = recv(sockClient, buffer, 1000 * sizeof(char), 0);

    buffer[taille] = '\0';

    write(sockClient, buffer, strlen(buffer));

    printf("Je suis thread %d mon pere est le %d et j'ai echo \" %s \" de longueur %d\n",getpid(), getppid(),buffer, strlen(buffer));

    memset(buffer, 0, 1000 * sizeof(char));

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
SOCKET ouvertureUDP(struct sockaddr_in6 server, int port)
{

    memset(&server, '0', sizeof(server));

    SOCKET sock = socket(AF_INET6, SOCK_DGRAM, 0);

    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    puts("Socket UDP créé");

    server.sin6_family = AF_INET6;
    server.sin6_addr = in6addr_any;
    server.sin6_port = htons(port);

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
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
 * @param sockServer le sokcet ouvert du client
 */
void serveur_echoUDP(SOCKET sockServer)
{
    puts("------Attente de message------");
    char *buffer = malloc(1000 * sizeof(char));
    struct sockaddr_in6 client;
    int tailleClient = sizeof(client);
    int stat;

    int taille = recvfrom(sockServer, (char *)buffer, 1000, MSG_WAITALL, (struct sockaddr *)&client, &tailleClient);

    buffer[taille] = '\0';

    printf("j'ai recu %s de longueur %d\n", buffer, strlen(buffer));

    getINFO(client);

    sendto(sockServer, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&client, tailleClient);

    memset(buffer, 0, 1000 * sizeof(char));

    free(buffer);
}
