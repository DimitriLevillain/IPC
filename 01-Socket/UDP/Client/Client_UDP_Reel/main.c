/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dlevillain
 *
 * Created on 14 septembre 2018, 08:39
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
int main(int argc, char** argv) {
    int socketClient;
    struct sockaddr_in infoServeur;
    float reelAEnvoyer=12.12;
    float reelRecu;
    int tailleStructure;
    int retour;
    int ret;
    //Creation de la socket UDP
    socketClient=socket(PF_INET , SOCK_DGRAM, IPPROTO_UDP);
    if(socketClient==-1)
    {
        printf("pb socket : %s \n", strerror(errno));
        exit(errno);
    }
    //init des informations serveurs
    //u_long inet_addr(const char *adresseAuFormatTexte="172.18.58.147");
    infoServeur.sin_family=AF_INET;
    infoServeur.sin_port=htons(3333);
    infoServeur.sin_addr.s_addr=inet_addr("172.18.58.83");
    //envoyer l'entier du serveur
    tailleStructure=sizeof(infoServeur);
    retour=sendto(socketClient, &reelAEnvoyer, sizeof(reelAEnvoyer), 0, (struct sockaddr *)&infoServeur, tailleStructure);
    
    if(retour == -1)
    {
        printf("pb sento : %s \n",strerror(errno));
        exit(errno);
    }
    //recevoir l'entier du serveur
    ret=recvfrom(socketClient, &reelRecu, sizeof(reelRecu), 0, (struct sockaddr *)&infoServeur, &tailleStructure);
    
    if(ret == -1)
    {
        printf("pb recvfrom: %s \n",strerror(errno));
    }  
    //afficher l'entier du serveur
    printf("message reçu : %f \n", reelRecu);
    
    
    
    return (EXIT_SUCCESS);
}
