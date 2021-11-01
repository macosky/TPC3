#include "serveur.h"

SOCKET sockServer, sockClient;
struct sockaddr_in server, client;

/*sighandler*/
void myInterruptHandler(int signum)
{
    printf("\nATTENTION \nextinction Serveur\n");
    close(sockClient);
    close(sockServer);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        puts("./serveur [PORT] [OPTION]");
        puts("PORT -> le port d'ouverture du socket");
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

        //Creation socket
        sockServer = ouvertureUDP(server, atoi(argv[1]));

        while (1)
        {
            // on fait de l'echo
            serveur_echoUDP(sockServer);
        }
    }
    else if (!strcmp(argv[2], "-TCP") || !strcmp(argv[2], "-tcp"))
    {
        ////////////////////
        ////// STREAM //////
        ////////////////////
        // Creation socket
        sockServer = ouvertureTCP(server, atoi(argv[1]));

        while (1)
        {
            //on prend 1 client
            sockClient = acceptClientTCP(sockServer, client);

            // on fait de l'echo
            serveur_echoTCP(sockClient);
        }
    }
    else
    {
        puts("./serveur [OPTION]");
        puts("OPTION -> -UDP ou -TCP");
        exit(1);
    }

    return 0;
}