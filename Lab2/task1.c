//
// Created by sapiest on 12.03.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int task1() {
  int x = 100;
  int rc = fork();
  if (rc < 0) {
    // fork failed; exit
    printf("No fork = %d\n", x);
    exit(1);
  } else if (rc == 0) {
    // child (new process)
    x = 300;
    printf("Child x = %d\n", x);
    sleep(1);
  } else {
    // parent goes down this path (original process)
    int wc = wait(NULL);
    x = 22;
    printf("Parent x = %d\n", x);
  }
  return 0;
}