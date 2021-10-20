#include "client.h"

struct sockaddr_in client_addr;
struct sockaddr_in server_addr;

////////////////////
////// STREAM //////
////////////////////

/**
 * @brief Ouverture du socket
 * 
 * @param server pointeur vers les parametre serveur que l'on renseigne
 * @return SOCKET 
 */
SOCKET ouvertureTCP()
{

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    return sock;
}

/**
 * @brief connection au serveur
 * 
 * @param sock notre socket
 * @param server param serveur etablie dans ouverture
 * @return int 
 */
int connectionTCP(SOCKET sock, struct sockaddr_in server)
{
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("Connection fail");
        exit(1);
    }
    return 0;
}

/**
 * @brief on envoie puis on ecoute
 * 
 * @param sock notre socket connecter
 * @return int 
 */
int client_echoTCP(SOCKET sock, char *message)
{
    // char *message = malloc(1000 * sizeof(char));
    // //char *reponse = malloc(1000 * sizeof(char));
    // printf("> ");
    // scanf("%s", message);

    //j'envoie mon message
    if (send(sock, message, strlen(message), 0) < 0)
    {
        puts("Erreur envoie");
        exit(1);
    }

    memset(message, 0, 1000 * sizeof(char));

    //je recoie l'echo
    if (recv(sock, message, 1000 * sizeof(char), 0) < 0)
    {
        puts("Erreur reception");
        exit(1);
    }

    puts(message);
    //free(message);
    return 0;
}

////////////////////
//// DATAGRAMME ////
////////////////////

/**
 * @brief Ouverture du socket
 * 
 * @param server pointeur vers les parametre serveur que l'on renseigne
 * @return SOCKET 
 */
SOCKET ouvertureUDP()
{

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

    return sock;
}

/**
 * @brief on envoie puis on ecoute
 * 
 * @param sock notre socket connecter
 * @return int 
 */
int client_echoUDP(SOCKET sock, struct sockaddr_in server, char *message)
{
    //char *message = malloc(1000 * sizeof(char));
    //printf("> ");
    //scanf("%s", message);

    int taille = sizeof(server);

    //j'envoie mon message
    if (
        sendto(sock, message, strlen(message), MSG_CONFIRM, (struct sockaddr *)&server, taille) < 0)
    {
        puts("Erreur envoie");
        exit(1);
    }

    memset(message, 0, 1000);

    //je recoie l'echo
    if (recvfrom(sock, (char *)message, 1000, MSG_WAITALL, (struct sockaddr *)&server, &taille) < 0)
    {
        puts("Erreur reception");
        exit(1);
    }

    puts(message);
    //free(message);
    return 0;
}
