/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dlevillain
 *
 * Created on 25 septembre 2018, 11:22
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUFSIZ 255

/*
 * 
 */
int main(int argc, char** argv) {

    int pid1,pid2;
    int nbOctets;
    int descTube[2];
    const char chaine[] = "Bonjour";
    char buffer[BUFSIZ];
    pid_t pid;
    pid1 = getpid();
    memset(buffer, '\0', BUFSIZ);

    if (pipe(descTube) == 0) 
    {
        pid2 = fork();  //duplication du processus
        
        if(pid2 == 0)     //process pere
        {   // fils p2
            printf("Je suis le fils");
            sleep(2);
            nbOctect = read(descTbe)
        }
        else    //je suis dans le process fils
        {
            nbOctets = write(descTube[1], chaine, strlen(chaine));
            printf("%d octet ecrits\n", nbOctets);
        }
    }
    
    exit (EXIT_SUCCESS);
}


        
       /* pid2 = fork();
        if (pid2 == 0) 
        {
            printf("p2\n");
        }
        else {
            printf("p1\n");
        }*/

