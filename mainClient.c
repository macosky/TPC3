#include "client.h"

struct sockaddr_in6 server;
SOCKET sock;

/*sighandler*/
void myInterruptHandler(int signum)
{
    printf("\nATTENTION \nextinction client\n");
    close(sock);
    exit(1);
}

int isValidIpAddress(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        puts("./client [message] [IP server] [PORT] [OPTION]");
        puts("message -> le message a envoyer");
        puts("IP server -> l'ip du server");
        puts("PORT -> le port du server");
        puts("OPTION -> -UDP ou -TCP");
        exit(1);
    }

    if (isValidIpAddress(argv[2]))
    {
        char adresse[64] = "::ffff:";
        strcat(adresse, argv[2]);
        inet_pton(AF_INET6, adresse, &server.sin6_addr);
    }
    else
    {
        inet_pton(AF_INET6, argv[2], &server.sin6_addr);
    }

    memset(&server, 0, sizeof(server));
    server.sin6_family = AF_INET6;
    server.sin6_port = htons(atoi(argv[3]));
    inet_pton(AF_INET6, argv[2], &server.sin6_addr);

    signal(SIGTERM, myInterruptHandler);
    signal(SIGINT, myInterruptHandler);

    if (!strcmp(argv[4], "-UDP") || !strcmp(argv[4], "-udp"))
    {
        ////////////////////
        //// DATAGRAMME ////
        ////////////////////

        //on ouvre le socket
        sock = ouvertureUDP();

        //on parle au serveur et on recoit ca reponse
        client_echoUDP(sock, server, argv[1]);
    }
    else if (!strcmp(argv[4], "-TCP") || !strcmp(argv[4], "-tcp"))
    {
        ////////////////////
        ////// STREAM //////
        ////////////////////

        //on ouvre le socket
        sock = ouvertureTCP(server);

        //on ce connecte au serveur
        connectionTCP(sock, server);

        //on parle au serveur et on recoit ca reponse
        client_echoTCP(sock, argv[1]);
    }
    else
    {
        puts("./client [OPTION]");
        puts("OPTION -> -UDP ou -TCP");
        exit(1);
    }

    return 0;
}