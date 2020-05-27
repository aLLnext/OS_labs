//
// Created by sapiest on 10.05.2020.
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <zconf.h>
#include<string.h>


static unsigned get_lines_count(const char *buf, unsigned int size) {
  unsigned int lines = 0;
  for (unsigned i = 0; i <= size; i++) {
    if (buf[i] == '\n' || buf[i] == '\0') {
      lines++;
    }
  }
  return lines;
}

static int task3(int argc, char *argv[]){
  int fd;                // переменная для файла
  struct stat file_stat; //структура для описания файла

  //промерка агументов
  //проверка количества аргументов
  if (argc != 3) {
    fprintf(stderr, "Format: mytail -<n> <filename>\n");

    return EXIT_FAILURE;
  }

  //получаем введенное количство строк
  int n = atoi(argv[1] + 1);
  if (n < 0) {
    fprintf(stderr, "n can't be < 0\n");

    return EXIT_FAILURE;
  }

  //открываем файл на чтение
  const char *file_name = argv[2];

  if ((fd = open(file_name, O_RDONLY)) < 0) {
    fprintf(stderr, "File's not open\n");

    return EXIT_FAILURE;
  }
  //получаем описание нашего файла
  stat(file_name, &file_stat);
  //получили размер нашего файла
  unsigned int size = file_stat.st_size + 1;
  //буфер для хранения текста
  char buf[size];
  unsigned int lines = 0;
  //записали текст в буффер
  read(fd, buf, size);
  //получили количество строк в файле
  lines = get_lines_count(buf, size);
  //если требуется вывести все строки - выводит буфер
  if (lines <= n) {
    printf("%s\n", buf);

    return EXIT_SUCCESS;
  }

  for (unsigned int i = 0; i < size; i++) {
    if(buf[i] == '\n'){
      lines--;
    }
    //находим нужное количество строк
    if(lines == n){
      char ans[size - i];
      strcpy(ans, (buf + (i + 1)));
      printf("%s\n", ans);

      return EXIT_SUCCESS;
    }
  }

  return EXIT_FAILURE;
}