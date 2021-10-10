#include "client.h"


int main(void){

    SOCKET sock = ouverture();
    connection(sock);
    lecture(sock);

    close(sock);    
    return 0;
}