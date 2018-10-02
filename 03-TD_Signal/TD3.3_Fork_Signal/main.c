/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dlevillain
 *
 * Created on 25 septembre 2018, 10:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

/*
 * 
 */
//handler affichage
void affichage(int sig)
{   
    static int cpt = 0;
    static int signal[2];
    
    signal[cpt] = sig;
    cpt++;
            
    if (cpt == 2)
    {
        printf("1 : Signal %d recu par %d\n",signal[0], getpid());
        printf("%d : Signal %d recu par %d\n", cpt, signal[1], getpid());
    }
}

int main(int argc, char** argv) {
    int pid1, pid2, pid3;
    int retour;
    
    pid1 = getpid();    //p1
    (void) signal(SIGUSR1, affichage); // redirection des signaux SIGUSR1 vers la fonction affichage
    printf ("Père   p1 pid = %d\n", pid1);
    pid2 = fork();
    if (pid2 == 0)
    {       //enfant p2
        pid3 = fork();
        if (pid3 == 0)
        {   //enfant p3
            sleep(1);
            printf("p3\n");
            
            printf("P3 envoie un signal USR1 à P1\n");
            retour = kill(pid1, SIGUSR1); //envoi d'un signal SIGUSR1 au pere P1
            if (retour !=0){
                printf("Erreur avec kill");
            }
            printf("Fin de processus P3\n");
        } 
        else {
            printf("p2\n");
            
            printf("P2 envoie un signal USR1 à P1\n");
            
            retour = kill(pid1, SIGUSR1);   //envoi d'un signal SIGUSR1 au pere P1
            if (retour !=0){
                printf("Erreur avec kill");
            }
            printf("Fin de processus P2\n");
        }
    } 
    else {  //p1
        printf("P1 attend un premier signal SIGUSR1\n");
        pause();
        printf("P1 attend un deuxième signal SIGUSR1\n");
        pause();
        printf("Fin de processus P1\n");
    }

    return (EXIT_SUCCESS);
}

