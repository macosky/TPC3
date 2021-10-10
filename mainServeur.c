#include "serveur.h"

int main(void){

    ouverture();

    while (1){

        SOCKET sockClient = acceptClient();

        echoClient(sockClient);
        
        close(sockClient);
        
    }

    return 0;
}