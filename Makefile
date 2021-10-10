CC=gcc -g -pthread
INC= -I.

OBJ_CLIENT=client.o mainClient.o
OBJ_SERVEUR=serveur.o mainServeur.o

PRG=client serveur

all: client serveur

# client
client: $(OBJ_CLIENT) client.h
	$(CC) -o client $(OBJ_CLIENT)

# serveur
serveur: $(OBJ_SERVEUR) serveur.h 
	$(CC) -o serveur $(OBJ_SERVEUR)
	
%.o: %.c
	$(CC) -o $@ -c $< $(SYS) $(INC)

clean:
	rm -f *.o

realclean: clean
	rm -f $(PRG) *~ out.*

