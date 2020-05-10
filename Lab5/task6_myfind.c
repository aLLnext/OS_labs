//
// Created by sapiest on 10.05.2020.
//

#include "string.h"
#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


static const char *SYMBOL_SPACE = "   ";

static void printNode(char *indent, char *dir_name, char *regex);

static void printChildNode(char *indent, char *dir_name, char *regex) {
  if (regex == NULL) {
    char *new_indent = malloc(strlen(indent) + strlen(SYMBOL_SPACE));
    strcpy(new_indent, indent);
    strcat(new_indent, SYMBOL_SPACE);
    printNode(new_indent, dir_name, regex);
    free(new_indent);
  }else{
    printNode(indent, dir_name, regex);
  }

}

static int check_string(char *str, const char *regex) {
  for (unsigned long i = 0, j = 0; i < strlen(str); ++i) {
    if (regex[j] == '*') {
      if (str[i + 1] == regex[j]) {
        j++;
      }
      continue;
    }
    if (str[i] != regex[j]) {
      return 1;
    }
    j++;
  }
  return 0;
}

static void printNode(char *indent, char *dir_name, char *regex) {
  DIR *dir;
  if (!(dir = opendir(dir_name))) {
    fprintf(stderr, "Dir`s not open\n");

    return;
  }

  struct dirent *dt;
  struct stat st;
  while ((dt = readdir(dir)) != NULL) {
    if (strcmp(dt->d_name, ".") != 0 && strcmp(dt->d_name, "..") != 0) {
      if (regex == NULL) {
        printf("%s%s\n", indent, dt->d_name);
      } else {
        if (!check_string(dt->d_name, regex)) {
          printf("%s%s\n", indent, dt->d_name);
        }
      }
      stat(dt->d_name, &st);
      if (dt->d_type == DT_DIR) {
        char path[2048];
        snprintf(path, sizeof(path), "%s/%s", dir_name, dt->d_name);
        printChildNode(indent, path, regex);
      }
    }
  }
  closedir(dir);
}

static int str_cut(char *str, int begin, int len) {
  int l = strlen(str);

  if (len < 0) {
    len = l - begin;
  }
  if (begin + len > l)
    len = l - begin;
  memmove(str + begin, str + begin + len, l - len + 1);
  return len;
}

static int task6(int argc, char *argv[]) {
  // myfind ./ -name 'dsd'
  char *dir_name = "./";
  regex_t regex;
  printf("argc %i\n", argc);
  for (int i = 0; i < argc; ++i) {
    printf("arg: %s\n", argv[i]);
  }
  printf("\n");

  if(argc == 1 || (argc == 2 && (strcmp(argv[1], "-name") != 0))){
    if(argc == 2){
      dir_name = argv[1];
    }
    printNode("", dir_name, NULL);
    return EXIT_SUCCESS;
  }

  if(argc == 2 && (strcmp(argv[1], "-name") == 0)){
    fprintf(stderr, "Format: myfind [<dir>] [-name][<filename>]\n");
    return EXIT_FAILURE;
  }

  if(argc == 3 && (strcmp(argv[1], "-name") != 0)){
    fprintf(stderr, "Format: myfind [<dir>] [-name][<filename>]\n");
    return EXIT_FAILURE;
  }

  if (((argc == 3 || argc == 4 ) && (strcmp(argv[argc - 2], "-name") != 0)) || argc == 2) {
    dir_name = argv[1];
    printNode("", dir_name, NULL);
  }


  if ((argc == 3 || argc == 4) && (strcmp(argv[argc - 2], "-name") == 0)) {
    char *reg_exp = argv[argc - 1];
    if (reg_exp[0] == '\'' || reg_exp[0] == '\"') {
      str_cut(reg_exp, 0, 1);
    }
    if (reg_exp[strlen(reg_exp) - 1] == '\'' ||
        reg_exp[strlen(reg_exp) - 1] == '\"') {
      str_cut(reg_exp, strlen(reg_exp) - 1, 1);
    }
    printNode("", dir_name, reg_exp);
    return EXIT_SUCCESS;
  }

  fprintf(stderr, "Format: myfind [<dir>] [-name][<filename>]\n");
  return EXIT_FAILURE;
}