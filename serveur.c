#include "serveur.h"

struct sockaddr_in serv_addr;
struct sockaddr_in client_addr;

SOCKET sock;

/**
 * @brief Ouverture du socket d'ecoute
 * 
 * @return int 
 */
int ouverture()
{

    memset(&serv_addr, '0', sizeof(serv_addr));

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1234);

    if (bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        printf("bind() error \n");
        exit(1);
    }

    if (listen(sock, 100) == -1)
    {
        printf("listen() error \n");
        exit(1);
    }

    printf("Socket ouvert on ecoute \n");
    return 0;
}

SOCKET acceptClient()
{

    SOCKET sockClient = accept(sock, NULL, NULL);

    return sockClient;
}

char *getPORT(SOCKET sockClient)
{
    char *buffer = malloc(sizeof(char) * 100);
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    if (getsockname(sockClient, (struct sockaddr *)&sin, &len) == -1)
    {
        perror("getsockname");
    }
    else
    {
        sprintf(buffer, "port number %d\n", ntohs(sin.sin_port));
    }
    
    return buffer;
}

void echoClient(SOCKET sockClient)
{
    char *buffer = getPORT(sockClient);

    printf("%s",buffer);
    if (write(sockClient, buffer, strlen(buffer)) < 0)
    {
        perror("Cannot write");
        exit(3);
    }
    free(buffer);
}

