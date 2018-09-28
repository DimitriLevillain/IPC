/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dlevillain
 *
 * Created on 21 septembre 2018, 08:09
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * 
 */
int main(int argc, char** argv) {

    int pid1, pid2, pid3, pid4, pid5, pid6, pid7;
    int pid;
    pid1 = getpid();

    pid3 = fork();
    if (pid3 == 0) //enfant de P1 nommé P3
    {
        pid2 = fork();
        if (pid2 == 0) //Enfant de P3 nommé P2
        {
            printf("P2 : pid=%d ppid=%d \n", getpid(), getppid());
        }
        else { //on est toujours dans P3

            pid4 = fork();
            if (pid4 == 0) //enfant de P3 nommé P4
            {
                printf("P4 : pid=%d ppid=%d \n", getpid(), getppid());
            }
            else //on est toujours dans P3
            {
                pid5 = fork();
                if (pid5 == 0) //enfant de P3 nommé P5
                {
                    pid6 = fork();
                    if (pid6 == 0)
                    {
                        printf("P6 : pid=%d ppid=%d \n", getpid(), getppid());
                        sleep(2);
                    }
                    
                    else {  //on est dans p5
                        pid7 = fork();
                        if (pid7 == 0)
                        {
                            printf("P7 : pid=%d ppid=%d \n", getpid(), getppid());
                            sleep(2);
                        }
                        else {
                    printf("P5 : pid=%d ppid=%d \n", getpid(), getppid());
                    pid5 = wait(NULL);
                    //printf("Fin de : %d \n", pid5);
                        }
                    }
                    
                } else //on est toujours dans P3
                {
                    printf("P3 : pid=%d ppid=%d \n", getpid(), getppid());
                    sleep(2);
                    pid3 = wait(NULL);
                    //printf("Fin de : %d \n", pid3);
                }
            }
        }
    }
    else
    {   //pere P1
        printf ( "p1 : pid=%d ppid=%d \n", pid1, getppid());
        pid = wait(NULL);
        printf("Fin de : %d \n", pid);
    }

    return (EXIT_SUCCESS);
}

