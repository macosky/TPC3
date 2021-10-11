#include "client.h"

int main(void)
{
    char message[100];
    char *server_reply = malloc(100 * sizeof(char));

    struct sockaddr_in *server = malloc(sizeof(struct sockaddr_in));
    

    SOCKET sock = ouverture(server);
    
    
    connection(sock,*server);

    while(1)
        client_echo(sock);
    

    close(sock);
    return 0;
}