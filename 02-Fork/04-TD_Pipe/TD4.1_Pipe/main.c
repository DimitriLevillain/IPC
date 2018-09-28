/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dlevillain
 *
 * Created on 25 septembre 2018, 11:13
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/*
 * 
 */
int main(int argc, char** argv) 
{
    FILE *pp;
    char buffer[255];
    int nbRead;
    
    pp = popen("/bin/uname","r");
    if ((pp == NULL))
    {
        printf("Pb avec popen : %s", strerror(errno));
        exit(0);
    }
    
    nbRead = fread(buffer, sizeof(buffer),1,pp);
    printf("%s",buffer);
    
    pclose(pp);

    return (EXIT_SUCCESS);
}

