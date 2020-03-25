//
// Created by sapiest on 12.03.2020.
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* #8 Write a program that creates two children, and connects the standard
output of one to the standard input of the other, using the
pipe() system call */

static int task8() {
  int p[2];
  char buf[100];

  if (pipe(p) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  int cpid1 = fork();
  if (cpid1 == 0) {
    close(p[0]);
    char msg1[] = "hello";
    write(p[1], msg1, 5);
    close(p[1]);
  } else {
    int cpid2 = fork();
    if (cpid2 == 0) {
      close(p[1]);
      read(p[0], buf, 5);
      printf("%s", buf);
      close(p[0]);
    }
  }
  //  // Setup our pipe
  //  char buff[BUFSZE];
  //  int p[2];
  //
  //  if (pipe(p) < 0)
  //    exit(1);
  //
  //  int rc1 = fork();
  //  if (rc1 < 0) {
  //    // fork failed; exit
  //    fprintf(stderr, "fork #1 failed\n");
  //    exit(1);
  //  } else if (rc1 == 0) {
  //    // Child #1
  //    printf(" Child #1 ");
  //    close(p[0]);   // This one only writes
  //    dup2(p[1], 1); // redirect stdout to pipe write
  //    printf("_This is getting sent to the pipe_");
  //  } else {
  //    // Parent process
  //    int rc2 = fork();
  //    if (rc2 < 0) {
  //      fprintf(stderr, "fork #2 failed\n");
  //      exit(1);
  //    } else if (rc2 == 0) {
  //      // Child #2
  //      printf(" Child #2 ");
  //      close(p[1]);   // Only read here
  //      dup2(p[0], 0); // Redirect stdin to pipe read
  //
  //      /* Strangely it looks like ALL of the stdout from
  //       * fork 1 is being sent to the pipe, even the stuff
  //       * sent to stdout BEFORE dup2 is called. This can be
  //       * shown by adjusting the size of the buffer below
  //       * to something small like 6 and seeing what gets
  //       * printed out... weird! */
  //
  //      char buff[512];                // Make a buffer
  //      read(STDIN_FILENO, buff, 512); // Read in from stdin
  //      printf("%s", buff);            // Print out buffer
  //
  //    } else {
  //      // Initial parent process
  //      /* If we wait for rc1 then it could finish before rc2 is done,
  //       * giving us some strange behavior. */
  //
  //      int wc = waitpid(rc2, NULL, 0);
  //      printf("goodbye");
  //    }
  //  }
  return 0;
}