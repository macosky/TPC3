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

int main(void)
{
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = INADDR_ANY;


    ////////////////////
    ////// STREAM //////
    ////////////////////
    //on ouvre le socket
    sock = ouverture(server);

    //on ce connecte au serveur
    connection(sock, server);

    while (1)
    {
        //gestion signaux
        signal(SIGTERM, myInterruptHandler);
        signal(SIGINT, myInterruptHandler);

        //on parle au serveur et on recoit ca reponse
        client_echo(sock);
    }

    ////////////////////
    //// DATAGRAMME ////
    ////////////////////

    //on ouvre le socket
    // sock = ouvertureUDP();
    
    // while (1)
    // {
    //     //gestion signaux
    //     signal(SIGTERM, myInterruptHandler);
    //     signal(SIGINT, myInterruptHandler);

    //     //on parle au serveur et on recoit ca reponse
    //     client_echoUDP(sock, server);
    // }

  
    // close(sock);

    return 0;
}