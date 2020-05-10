//
// Created by sapiest on 10.05.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static int task4() {
  //имя файла
  const char *file_name = "temp/temp.txt";
  //стркутура для описания файла
  struct stat file_stat;
  //получаем описание файла
  if (stat(file_name, &file_stat)) {
    fprintf(stderr, "Error\n");
    return EXIT_FAILURE;
  }

  printf("Size: %li\n", file_stat.st_size);
  printf("Number link: %li\n", file_stat.st_nlink);
  printf("Number block: %li\n", file_stat.st_blocks);
  return EXIT_SUCCESS;
}