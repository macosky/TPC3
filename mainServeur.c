#include "serveur.h"

int main(void)
{
    struct sockaddr_in server, client;
    int fin = 1;

    SOCKET sockServer = ouverture(server);

    

    while (fin)
    {

        SOCKET sockClient = acceptClient(client);

        serveur_echo(sockClient);


        //     close(sockClient);
    }

   

    return 0;
}