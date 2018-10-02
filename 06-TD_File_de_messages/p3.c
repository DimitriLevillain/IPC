/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   p3.c
 * Author: dlevillain
 *
 * Created on 2 octobre 2018, 09:19
 */

#include "zone.h"

/*
 * 
 */
int main(int argc, char** argv) {
    struct donnees file;
    int id;
    int retour;
    int type;
    float valEnv;
    key_t key;

    //Obtention de la clé
    key = ftok("/tmp/bidon", CLE);
    if (key == -1) {
        perror("ftok");
        exit(2);
    }

    //Obtention de la file pour la clé
    id = msgget(key, 0666 | IPC_CREAT);
    if (id == -1) {
        printf("pb creation file : %s\n", strerror(errno));
        exit(1);
    }


    while (1) {
        memset(file.texte, '\0', 9);    //Efface le texte
        retour = msgrcv(id, (void*) &file, 9, 2, IPC_NOWAIT);   //Reception du message de type 2
        if (retour != -1) {
            printf("temp : %.5s\n", file.texte);
        }
        
        memset(file.texte, '\0', 9);    //Efface le texte
        retour = msgrcv(id, (void*) &file, 9, 3, IPC_NOWAIT);   //Reception du message de type 3
        if (retour != -1) {
            printf("ordre : %s\n", file.texte);
        }
        
        memset(file.texte, '\0', 9);    //Efface le texte
        retour = msgrcv(id, (void*) &file, 9, 4, IPC_NOWAIT);   //Reception du message de type 4
        if (retour != -1) {
            printf("press : %.5s\n", file.texte);
        }
    }

    return (EXIT_SUCCESS);
}

