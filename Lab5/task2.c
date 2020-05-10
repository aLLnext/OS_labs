//
// Created by sapiest on 10.05.2020.
//
#include <bits/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <zconf.h>

static const char *file_name = "task2_file.txt";

void start_timer();

double end_timer();

//Метод А
static void A() {
  char c = 'a';
  //создали файл и открыли его на запись
  int f = creat(file_name, S_IWRITE);
  for (unsigned i = 0; i < 300000; ++i) {
    //записали 300 000 записей, размером в 1 байт
    write(f, &c, 1);
  }
  //закрыли файл
  close(f);
}

//Метод B
static void B() {
  char c = 'b';
  //создали файл и открыли его на запись
  FILE *f = fopen(file_name, "w");
  for (unsigned i = 0; i < 300000; ++i) {
    //записали 300 000 записей, размером в 1 байт
    fwrite(&c, 1, 1, f);
  }
  //закрыли файл
  fclose(f);
}

static void task2() {
  printf("TASK2\n");
  start_timer();
  A();
  printf("A: %f\n", end_timer());

  start_timer();
  B();
  printf("B: %f\n", end_timer());
  printf("\n");
}