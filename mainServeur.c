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

int main(void)
{
    //Creation socket
    sockServer = ouverture(server);

    while (1)
    {
        // gestion des sig
        signal(SIGTERM, myInterruptHandler);
        signal(SIGINT, myInterruptHandler);

        //on prend 1 client
        sockClient = acceptClient(sockServer, client);

        // on fait de l'echo
        serveur_echo(sockClient);
    }

    return 0;
}