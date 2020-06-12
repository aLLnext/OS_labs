#include <stdio.h>

#include "mythreads.h"

int balance = 0;

void* worker(void* arg) {
    balance++; // unprotected access 
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    pthread_mutex_t m;
    Pthread_create(&p, NULL, worker, NULL);
    Pthread_mutex_lock(&m);
    balance++; // unprotected access
    Pthread_mutex_unlock(&m);
    Pthread_join(p, NULL);
    return 0;
}
