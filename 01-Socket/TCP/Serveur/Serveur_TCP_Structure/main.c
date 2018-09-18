/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dlevillain
 *
 * Created on 18 septembre 2018, 09:52
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
typedef struct {
    unsigned char jour;
    unsigned char mois;
    unsigned short int annee;
    char jourDeLaSemaine[10]; // le jour en toute lettre
} datePerso;

int main(int argc, char** argv) {
    datePerso valeurRecue;
    int socketServeur;
    int socketDeux;
    int tailleStructure;
    int retourListen;
    int retourRead;
    int retourB;
    struct sockaddr_in adresse;
    struct sockaddr_in infoClient;

    //Création de la socket TCP
    socketServeur = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (socketServeur == -1) {
        printf("pb socket : %s \n", strerror(errno));
        exit(errno);
    }

    //Init des informations
    adresse.sin_family = AF_INET;
    adresse.sin_port = htons(7777);
    adresse.sin_addr.s_addr = htonl(INADDR_ANY);

    retourB = bind(socketServeur, (struct sockaddr*) &adresse, sizeof (adresse)); //attachement ip-port

    if (retourB == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(0);
    }


    //définie la taille de la file de connexion
    retourListen = listen(socketServeur, 10);

    if (retourListen == -1) {
        printf("pb listen: %s \n", strerror(errno));
    }


    tailleStructure = sizeof (infoClient);

    while (1) {

        socketDeux = accept(socketServeur, (struct sockaddr *) &infoClient, &tailleStructure);

        if (socketDeux == -1) {
            printf("pb accept: %s \n", strerror(errno));
        }

        //reçoit l'entier du client
        retourRead = read(socketDeux, &valeurRecue, sizeof (valeurRecue));


        if (retourRead == -1) {
            printf("pb read: %s \n", strerror(errno));
        }

        //affiche la valeur reçu
        printf("message du client %s Réponse : %s   %u/%u/%u \n", inet_ntoa(infoClient.sin_addr), valeurRecue.jourDeLaSemaine, valeurRecue.jour, valeurRecue.mois, valeurRecue.annee);
        
        close(socketDeux);

    }
    
    close(socketServeur);
    
    return (EXIT_SUCCESS);
}