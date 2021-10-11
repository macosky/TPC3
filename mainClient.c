#include "client.h"

struct sockaddr_in *server;
SOCKET sock;

/*sighandler*/
void myInterruptHandler(int signum)
{
    printf("\nATTENTION \nextinction client\n");
    free(server);
    close(sock);
    exit(1);
}

int main(void)
{

    server = malloc(sizeof(struct sockaddr_in));

    //on ouvre le socket
    sock = ouverture(server);

    //on ce connecte au serveur
    connection(sock, *server);

    while (1)
    {   
        //gestion signaux
        signal(SIGTERM, myInterruptHandler);
        signal(SIGINT, myInterruptHandler);

        //on parle au serveur et on recoit ca reponse
        client_echo(sock);
    }

    return 0;
}