/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dlevillain
 *
 * Created on 18 septembre 2018, 08:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/*
 * 
 */

typedef struct{
	unsigned char jour;
	unsigned char mois;
	unsigned short int annee;
	char jourDeLaSemaine[10];	// le jour en toute lettre
}datePerso;

int main(int argc, char** argv) {
    datePerso entierAEnvoyer;
    int socketClient;
    struct sockaddr_in infoServeur;
    entierAEnvoyer.jour=18;
    entierAEnvoyer.mois=9;
    entierAEnvoyer.annee=2018;
    strcpy(entierAEnvoyer.jourDeLaSemaine, "Mardi");
    int tailleStructure;
    int retour;
    int ret;
    
    //Creation de la socket TCP
    socketClient=socket(PF_INET , SOCK_STREAM, IPPROTO_TCP);
    if(socketClient==-1)
    {
        printf("pb socket : %s \n", strerror(errno));
        exit(errno);
    }
    
    //init des informations serveurs
    infoServeur.sin_family=AF_INET;
    infoServeur.sin_port=htons(7777);
    infoServeur.sin_addr.s_addr=inet_addr("172.18.58.76");
    
    tailleStructure=sizeof(infoServeur);
    
    //connecte la socket à l'adresse spéficiée
    connect(socketClient, (struct sockaddr *)&infoServeur, tailleStructure);
    
    //envoi de la structure
    retour = write(socketClient, &entierAEnvoyer, sizeof(entierAEnvoyer));

    if(retour == -1)
    {
        printf("pb write : %s \n",strerror(errno));
        exit(errno);
    }
    
    //fermeture du socket
    close(socketClient);
    
    return (EXIT_SUCCESS);
}
