/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dlevillain
 *
 * Created on 18 septembre 2018, 08:43
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
int main(int argc, char** argv) {
    int socketClient;
    struct sockaddr_in infoServeur;
    float reelAEnvoyer=12.12;
    float reelRecu;
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
    infoServeur.sin_port=htons(6666);
    infoServeur.sin_addr.s_addr=inet_addr("172.18.58.76");
    
    tailleStructure=sizeof(infoServeur);
    
    //connecte la socket à l'adresse spéficiée
    connect(socketClient, (struct sockaddr *)&infoServeur, tailleStructure);
    
    //envoi du réel
    retour = write(socketClient, &reelAEnvoyer, sizeof(reelAEnvoyer));

    if(retour == -1)
    {
        printf("pb write : %s \n",strerror(errno));
        exit(errno);
    }
    
    //reçoit le réel du serveur
    ret = read(socketClient, &reelRecu, sizeof(reelRecu));
    
    
    if(ret == -1)
    {
        printf("pb read: %s \n",strerror(errno));
    }  
    
    //afficher l'entier du serveur
    printf("message reçu : %f \n", reelRecu);
    
    //fermute du socket
    close(socketClient);
    
    return (EXIT_SUCCESS);
}
