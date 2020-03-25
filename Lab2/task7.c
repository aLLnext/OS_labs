//
// Created by sapiest on 12.03.2020.
//

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int task7() {
  int rc = fork();

  if (rc == 0) // child process
  {
    close(STDOUT_FILENO);
    printf("Hello World. Can you see this?\n");
  } else if (rc > 0) {
    wait(NULL);
    printf("I am parent process\n");
  } else {
    printf("Error occurred during fork()\n");
  }
  return 0;
}