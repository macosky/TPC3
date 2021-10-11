#include "serveur.h"



SOCKET sock;

/**
 * @brief Ouverture du socket d'ecoute
 * 
 * @return int 
 */
SOCKET ouverture(struct sockaddr_in server)
{

    memset(&server, '0', sizeof(server));

    sock = socket(AF_INET, SOCK_STREAM, 0);

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

SOCKET acceptClient(struct sockaddr_in client)
{
    int sizesockaddr = sizeof(struct sockaddr_in);
    SOCKET sockClient = accept(sock, (struct sockaddr *)&client, (socklen_t *)&sizesockaddr);

    return sockClient;
}

void lecture(SOCKET sock)
{

    int n = 0;
    char lecture[1024];
    printf("Reception : ");

    while ((n = read(sock, lecture, sizeof(lecture) - 1)) > 0)
    {
        lecture[n] = 0;
        if (fputs(lecture, stdout) == EOF)
        {
            printf("Lecture erreur\n");
        }
    }
}

void serveur_echo(SOCKET sockClient)
{
    int taille = 0;
    char *buffer = malloc(100 * sizeof(char));
    
    while ((taille = recv(sockClient, buffer, 100, 0)) > 0)
    {
        printf("%s", buffer);
        write(sockClient, buffer, strlen(buffer));
        memset(buffer,0,sizeof(buffer));
    }
    
}
