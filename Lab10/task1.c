//
// Created by sapiest on 15.06.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int reader(){
  FILE *f;
  if((f = fopen("test_task1.txt","r")) == 0){
    perror("Can`t read");
    return EXIT_FAILURE;
  }

  char c;
  while (1){
    fseek(f, 0, SEEK_SET);
    while ((c = fgetc(f)) != EOF){
      printf("%c", c);
    }
    printf("\n");
  }

  fclose(f);
  return EXIT_SUCCESS;
}

static int unlink_file(){
  if(unlink("test_task1.txt") != 0){
    perror("Unlink error");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}