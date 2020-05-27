//
// Created by sapiest on 30.04.2020.
//
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <zconf.h>

void start_timer();

double end_timer();

static void task1() {
  printf("TASK1\n");
  //задаем имя файла
  const char *file_name = "task1_file.txt";
  //устанавливаем количество байт
  const unsigned int n = 300 * 1024;
  //выделили память под нужное количество байт
  char *buff = malloc(n);
  //запустиили таймер
  start_timer();
  //создали файл, и открыли его на запись
  int f = creat(file_name, S_IWRITE);
  if (f < 0) {
    printf("Error in create\n");
  }
  //остановили таймер и вывели время
  printf("Create: %f\n", end_timer());

  start_timer();
  if (write(f, buff, n) != n) {
    printf("Error in write\n");
  }
  printf("Write: %f\n", end_timer());

  start_timer();
  //аналог fflush - очистии записи в файл
  fsync(f);
  printf("Fflush: %f\n", end_timer());

  start_timer();
  //закрыли файл
  close(f);
  printf("Close: %f\n", end_timer());

  start_timer();
  //удалили файл
  remove(file_name);
  printf("Remove: %f\n", end_timer());

  //освободили буфер
  free(buff);

  printf("\n");
}