/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   zone.h
 * Author: dlevillain
 *
 * Created on 2 octobre 2018, 08:22
 */

#ifndef ZONE_H
#define ZONE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#define RANDMAX 100
#define CLE 5678

struct donnees{
	long type;
	char texte[9];
};
#endif

