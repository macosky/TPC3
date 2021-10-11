#include "client.h"

struct sockaddr_in client_addr;
struct sockaddr_in server_addr;

SOCKET sock;

SOCKET ouverture(struct sockaddr_in *server)
{


    sock = socket(AF_INET, SOCK_STREAM, 0);

    server->sin_family = AF_INET;
    server->sin_addr.s_addr = inet_addr("127.0.0.1");
    server->sin_port = htons(1234);

    return sock;
}

int connection(SOCKET sock, struct sockaddr_in server)
{
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("Connection fail");
        exit(1);
    }
    return 0;
}

int lecture(SOCKET sock)
{

    int n = 0;
    char lecture[1024];
    printf("Reception : ");

    while ((n = read(sock, lecture, sizeof(lecture) - 1)) > 0)
    {
        lecture[n] = 0;
        if (fputs(lecture, stdout) == EOF)
        {
            puts("Lecture erreur");
            exit(1);
        }
    }
}

int client_echo(SOCKET sock)
{   
    char * message = malloc(100*sizeof(char));
    char * reponse = malloc(100*sizeof(char));
    printf("> ");
    scanf("%s", message);

    //Send some data
    if (send(sock, message, strlen(message), 0) < 0)
    {
        puts("Erreur envoie");
        exit(1);
    }

    //Receive a reply from the server
    if (recv(sock, reponse, sizeof(reponse), 0) < 0)
    {
        puts("Erreur reception");
        exit(1);
    }

    printf("$ %s \n",reponse);
    memset(reponse, 0, sizeof(reponse));
    return 0;
}