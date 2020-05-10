//
// Created by sapiest on 10.05.2020.
//

#include "string.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static int task5(int argc, char *argv[]) {
  if (argc > 3 || (argc == 3 && (strcmp(argv[1], "-1") != 0))) {
    fprintf(stderr, "Format: myls [-l] [<dir>]\n");
    return EXIT_FAILURE;
  }

  int l_flag = argc == 3 || (argc == 2 && (strcmp(argv[1], "-l") == 0));

  char *dir_name = "./";
  if (argc == 3) {
    dir_name = argv[2];
  }

  //переменная для хранения директории
  DIR *dir;
  //открываем директорию
  if (!(dir = opendir(dir_name))) {
    fprintf(stderr, "Dir's not open");
    return EXIT_FAILURE;
  }
  //стркутура для хранения элемента директории
  struct dirent *dt;
  struct stat st;

  while ((dt = readdir(dir)) != NULL) {
    printf("%s ", dt->d_name);
    stat(dt->d_name, &st);
    if (l_flag) {
      printf(" (Size: %li, Number link: %lu, Number block: %li, UID: %u, "
             "GID: %u, Mode: %u)\n",
             st.st_size, st.st_nlink, st.st_blocks, st.st_uid, st.st_gid,
             st.st_mode);
    }
  }
  if (closedir(dir) == -1) {
    fprintf(stderr, "Error: close dir\n");
    return EXIT_FAILURE;
  }

  printf("\n");
  return EXIT_SUCCESS;
}