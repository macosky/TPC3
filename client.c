#include "client.h"

struct sockaddr_in client_addr;
struct sockaddr_in server_addr;

/**
 * @brief Ouverture du socket
 * 
 * @param server pointeur vers les parametre serveur que l'on renseigne
 * @return SOCKET 
 */
SOCKET ouverture(struct sockaddr_in *server)
{

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    server->sin_family = AF_INET;
    server->sin_addr.s_addr = inet_addr("127.0.0.1");
    server->sin_port = htons(1234);

    return sock;
}

/**
 * @brief connection au serveur
 * 
 * @param sock notre socket
 * @param server param serveur etablie dans ouverture
 * @return int 
 */
int connection(SOCKET sock, struct sockaddr_in server)
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
int client_echo(SOCKET sock)
{
    char *message = malloc(1000 * sizeof(char));
    //char *reponse = malloc(1000 * sizeof(char));
    printf("> ");
    scanf("%s", message);

    //j'envoie mon message
    if (send(sock, message, strlen(message), 0) < 0)
    {
        puts("Erreur envoie");
        exit(1);
    }

    memset(message,0,1000 * sizeof(char));
    puts(message);

    //je recoie l'echo
    if (recv(sock, message, 1000 * sizeof(char), 0) < 0)
    {
        puts("Erreur reception");
        exit(1);
    }

    puts(message);
    //memset(message,0,1000 * sizeof(char));
    //memset(reponse,0,1000 * sizeof(char));
    free(message);
    //free(reponse);
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
SOCKET ouvertureUDP(struct sockaddr_in *server)
{

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

    server->sin_family = AF_INET;
    server->sin_addr.s_addr = inet_addr("127.0.0.1");
    server->sin_port = htons(1234);

    return sock;
}


/**
 * @brief on envoie puis on ecoute
 * 
 * @param sock notre socket connecter
 * @return int 
 */
int client_echoUDP(SOCKET sock, struct sockaddr_in server)
{
    char *message = malloc(1000 * sizeof(char));
    printf("> ");
    scanf("%s", message);

    //j'envoie mon message
    if (sendto(sock, message, strlen(message), MSG_DONTWAIT, (struct sockaddr *)&server, (socklen_t)sizeof(server)) < 0)
    {
        puts("Erreur envoie");
        exit(1);
    }

    memset(message,0,1000 * sizeof(char));
    puts(message);

    //je recoie l'echo
    if (recvfrom(sock, message, 1000 * sizeof(char), MSG_DONTWAIT, (struct sockaddr *)&server, (socklen_t *)sizeof(server)) < 0)
    {
        puts("Erreur reception");
        exit(1);
    }

    puts(message);
    free(message);
    return 0;
}
