/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dlevillain
 *
 * Created on 28 septembre 2018, 08:05
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

/*
 * 
 */
typedef struct {
    int v1;
    int v2;
    int v3;
}laStruct;

laStruct message;

void *ma_fonction_thread1(void *arg) {
    long tid;
    tid = syscall(SYS_gettid);
    message.v1 = *(int *) arg;
    printf("Dans le thread 1:\n- id : %ld\n- Valeur : %d\n",tid,message.v1);
    sleep(3);
    pthread_exit((void *)"merci pour le temps CPU T1");
}

void *ma_fonction_thread2(void *arg) {
    long tid;
    tid = syscall(SYS_gettid);
    message.v2 = *(int *) arg;
    printf("Dans le thread 1:\n- id : %ld\n- Valeur : %d\n",tid,message.v2);
    sleep(3);
    pthread_exit((void *)"merci pour le temps CPU T2");
}

void *ma_fonction_thread3(void *arg) {
    long tid;
    tid = syscall(SYS_gettid);
    message.v3 = *(int *) arg;
    printf("Dans le thread 1:\n- id : %ld\n- Valeur : %d\n",tid,message.v3);
    sleep(3);
    pthread_exit((void *)"merci pour le temps CPU T3");
}

int main(int argc, char** argv) {
    int res;
    int a = 1;
    int b = 2;
    int c = 3;
    pthread_t thread_un;
    pthread_t thread_deux;
    pthread_t thread_trois;
    void *thread_result;
    void *thread_result2;
    void *thread_result3;
    
    
    
    //Thread 1
    res = pthread_create(&thread_un, NULL, ma_fonction_thread1, (void *) &a);
    if (res != 0) {
        perror("thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("attente de la fin du thread ...\n");
    
    res= pthread_join(thread_un, &thread_result);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    
    //Thread 2
    res = pthread_create(&thread_deux, NULL, ma_fonction_thread2, (void *) &b);
    if (res != 0) {
        perror("thread creation failed 2");
        exit(EXIT_FAILURE);
    }
    printf("attente de la fin du thread 2...\n");
    
    res= pthread_join(thread_deux, &thread_result2);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    
    //Thread 3
    res = pthread_create(&thread_trois, NULL, ma_fonction_thread3, (void *) &c);
    if (res != 0) {
        perror("thread creation failed 3");
        exit(EXIT_FAILURE);
    }
    printf("attente de la fin du thread 3...\n");
    
    res= pthread_join(thread_un, &thread_result3);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    
    printf("Ok, valeur de retour du Thread 1 join :%s\n", (char *)thread_result);
    printf("Ok, valeur de retour du Thread 2 join :%s\n", (char *)thread_result2);
    printf("Ok, valeur de retour du Thread 3 join :%s\n", (char *)thread_result3);

    
    exit (EXIT_SUCCESS);
}

