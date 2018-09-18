/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dlevillain
 *
 * Created on 14 septembre 2018, 11:12
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
typedef struct {
    unsigned char jour;
    unsigned char mois;
    unsigned short int annee;
    char jourDeLaSemaine[10]; // le jour en toute lettre
} datePerso;

int main(int argc, char** argv) {
    int socketServeur;
    datePerso valeurRecue;
    int tailleStructure;
    int retourRec;
    int retourB;
    struct sockaddr_in adresse;
    struct sockaddr_in infoClient;

    //Création de la socket UDP
    socketServeur = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socketServeur == -1) {
        printf("pb socket : %s \n", strerror(errno));
        exit(errno);
    }

    //Init des informations
    adresse.sin_family = AF_INET;
    adresse.sin_port = htons(4444);
    adresse.sin_addr.s_addr = htonl(INADDR_ANY);

    retourB = bind(socketServeur, (struct sockaddr*) &adresse, sizeof (adresse)); //attachement ip-port

    if (retourB == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(0);
    }

    tailleStructure = sizeof (infoClient);

    //Reception de la valeur envoyé par le client
    retourRec = recvfrom(socketServeur, &valeurRecue, sizeof (valeurRecue), 0, (struct sockaddr *) &infoClient, &tailleStructure);

    if (retourRec == -1) {
        printf("pb recvfrom: %s \n", strerror(errno));
    }

    //affiche la valeur reçu
    printf("message du client %s Réponse : %s   %u/%u/%u \n", inet_ntoa(infoClient.sin_addr), valeurRecue.jourDeLaSemaine, valeurRecue.jour, valeurRecue.mois, valeurRecue.annee);

    return (EXIT_SUCCESS);
}
