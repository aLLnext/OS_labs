//
// Created by sapiest on 23.06.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <zconf.h>
#include <assert.h>
#include "queue.c"
#include "queue_mutex.c"
#include "queue_cond.c"

#define NUM_CHILDREN 2

int main(int argc, char *argv[]) {
  if (argc != 2) {
    perror("Incorrect input. Needs \"program [code 1 - 3]\"");
    exit(EXIT_FAILURE);
  }

  int i;
  pthread_t child[NUM_CHILDREN];

  Shared *shared = make_shared();

  switch (atoi(argv[1])) {
  case 1: {
  }

  case 2: {
  }

  case 3: {
  }

  }
}

int test1() {}

int test2() {}

int test3() {}