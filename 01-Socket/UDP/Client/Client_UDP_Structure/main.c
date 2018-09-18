/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dlevillain
 *
 * Created on 14 septembre 2018, 08:44
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

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
    entierAEnvoyer.jour=14;
    entierAEnvoyer.mois=9;
    entierAEnvoyer.annee=2018;
    strcpy(entierAEnvoyer.jourDeLaSemaine, "Vendredi");
    int tailleStructure;
    int retour;
    
    //Creation de la socket UDP
    socketClient=socket(PF_INET , SOCK_DGRAM, IPPROTO_UDP);
    if(socketClient==-1)
    {
        printf("pb socket : %s \n", strerror(errno));
        exit(errno);
    }
    //init des informations serveurs

    infoServeur.sin_family=AF_INET;
    infoServeur.sin_port=htons(4444);
    infoServeur.sin_addr.s_addr=inet_addr("172.18.58.81");
    
    //envoyer l'entier du serveur
    tailleStructure=sizeof(infoServeur);
    retour=sendto(socketClient, &entierAEnvoyer, sizeof(entierAEnvoyer), 0, (struct sockaddr *)&infoServeur, tailleStructure);
    
    if(retour == -1)
    {
        printf("pb sento : %s \n",strerror(errno));
        exit(errno);
    }
    
    
    return (EXIT_SUCCESS);
}