#include "client.h"

struct sockaddr_in client_addr;
struct sockaddr_in server_addr;

SOCKET sock;

SOCKET ouverture()
{

    memset(&client_addr, '0', sizeof(client_addr));

    sock = socket(AF_INET, SOCK_STREAM, 0);

    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(1234);

    if (inet_pton(AF_INET, "127.0.0.1", &client_addr.sin_addr) <= 0)
    {
        printf("Convertion d'adresse fail\n");
        exit(1);
    }

    return sock;
}

int connection(SOCKET sock)
{
    if (connect(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
    {
        printf("Connection fail\n");
        return 1;
    }
    return 0;
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

char *getServerDescritpion(SOCKET sock)
{
    char IP[16];
    unsigned int Port;
    char *buffer = malloc(sizeof(char) * 100);

    bzero(&server_addr, sizeof(server_addr));
    socklen_t len = sizeof(server_addr);

    getsockname(sock, (struct sockaddr *)&server_addr, &len);

    inet_ntop(AF_INET, &server_addr.sin_addr, IP, sizeof(IP));

    Port = ntohs(server_addr.sin_port);

    sprintf(buffer, "IP: %s PORT: %d", IP, Port);

    return buffer;
}

void client_echo(SOCKET sock)
{
    char *buffer = getServerDescritpion(sock);

    printf("J'envoie : %s\n", buffer);
    if (write(sock, buffer, strlen(buffer)) < 0)
    {
        perror("Cannot write");
        exit(3);
    }
    free(buffer);
}