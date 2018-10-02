/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "zone.h"

float randomC(){
	return ((char)('A'+((char)24.0*(rand()/(RAND_MAX+0.1)))));
}

int main(int argc, char** argv) {
    struct donnees file;
    int id;
    int retour;
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

    //Envoi des messages
    while (1) {
        //Type 3
        file.texte[0]=randomC();    //Tirage au sort d'une lettre
        file.type = 3;
        printf("type = %ld message = %s\n", file.type, file.texte); 
        retour = msgsnd(id, (void*) &file, sizeof(char), IPC_NOWAIT);    //envoi du message
        if (retour == -1) {
            printf("Echec msgsnd");
        }
        sleep(1);
    }

    return (EXIT_SUCCESS);
}