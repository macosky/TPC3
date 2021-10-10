#include "client.h"

struct sockaddr_in client_addr;

SOCKET sock;

SOCKET ouverture()
{

    memset(&client_addr, '0', sizeof(client_addr));

    sock = socket(AF_INET, SOCK_STREAM, 0);

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

    while ((n = read(sock, lecture, sizeof(lecture) - 1)) > 0)
    {
        lecture[n] = 0;
        if (fputs(lecture, stdout) == EOF)
        {
            printf("Lecture erreur\n");
        }
    }
}