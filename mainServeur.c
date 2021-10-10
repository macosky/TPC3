#include "serveur.h"

int main(void)
{
    int fin = 1;

    SOCKET sockServer = ouverture();

    while (fin)
    {

        SOCKET sockClient = acceptClient();

        serveur_echo(sockClient);
        
        
        lecture(sockClient);


        close(sockClient);
    }

    return 0;
}