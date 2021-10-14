#include "client.h"

struct sockaddr_in server;
SOCKET sock;

/*sighandler*/
void myInterruptHandler(int signum)
{
    printf("\nATTENTION \nextinction client\n");
    close(sock);
    exit(1);
}

int main(int argc, char *argv[])
{
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = INADDR_ANY;

    if (argc != 3)
    {
        puts("./client [message] [OPTION]");
        puts("message -> le message a envoyer");
        puts("OPTION -> -UDP ou -TCP");
        exit(1);
    }

    signal(SIGTERM, myInterruptHandler);
    signal(SIGINT, myInterruptHandler);

    if (!strcmp(argv[2], "-UDP") || !strcmp(argv[2], "-udp"))
    {
        ////////////////////
        //// DATAGRAMME ////
        ////////////////////

        //on ouvre le socket
        sock = ouvertureUDP();

        //on parle au serveur et on recoit ca reponse
        client_echoUDP(sock, server, argv[1]);
    }
    else if (!strcmp(argv[2], "-TCP") || !strcmp(argv[2], "-tcp"))
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