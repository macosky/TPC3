# TP3.2C

Ce projet met en place un echo entre client serveur sur socket C

## Help
```
./serveur [PORT] [OPTION]
PORT -> le port d'ouverture du socket
OPTION -> -UDP ou -TCP
```

```
./client [message] [IP server] [PORT] [OPTION]
message -> le message a envoyer
IP server -> l'ip du server
PORT -> le port du server
OPTION -> -UDP ou -TCP
```

## Usage exemple

### UDP
On ouvre le serveur sur le port 72 en UDP
```s
./serveur 72 -udp             
Socket UDP créé
Socket ouvert on ecoute 
------Attente de message------
j'ai recu bonjour de longueur 7
Ip source : ::1
Hostname source : localhost
------Attente de message------
^C
ATTENTION 
extinction Serveur
```

Le client envoie bonjour à la machine distante et affiche l'echo

```s
./client "bonjour" ::1 72 -udp
> bonjour 
```

### TCP
```
./serveur 72 -TCP
Socket créé
Socket ouvert on ecoute 
------Attente de connexion------
Un client est connecté
Ip source : ::1
Hostname source : localhost
Je suis thread 9155 mon pere est le 8687 et j'ai echo " bonjour " de longueur 7
------Attente de connexion------

```
Le client envoie bonjour à la machine distante et affiche l'echo
```
./client "bonjour" ::1 72 -tcp
> bonjour
```