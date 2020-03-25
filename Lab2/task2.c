#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void sig_handler(int signum) {
  printf("goodbye\n");
  exit(0);
}

static int task2() {
  int parent_pid = getpid();
  int rc = fork();
  if (rc == 0) //child
  {
    printf("hello\n");
    kill(parent_pid, SIGCONT);
    exit(0);
  }
  else if (rc > 0) // parent
  {
    signal(SIGCONT, sig_handler); // install signal handler
    pause();
  }
  else // fork did not succeed
  {
    printf("error\n");
    return 1;
  }
}
