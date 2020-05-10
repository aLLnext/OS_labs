//
// Created by sapiest on 23.04.2020.
//

#include <stdio.h>
#include <stdlib.h>

int global;

static int task1() {
  long size = 128;

  int local = 5;
  void *p = malloc(128000000);
  int new_local = 0; //создали новую локальную переменную
  void *new_p = malloc(size); // дабавили malloc()

  printf("Address of main is %li\n", (long)task1);
  printf("Address of global is %li\n", (long)&global);
  printf("Address of local is %li\n", (long)&local);
  printf("Address of p is %li\n\n", (long)&p);

  //вывод новых адресов
  printf("Address of local is %li\n", (long)&local);
  printf("Address of new local is %li\n", (long)&new_local);
  printf("Address of p %li\n", (long)p);
  printf("Address of new p is %li\n\n", (long)new_p);

  //вывдо адреса указателя
  printf("Address of pointer new p is %li\n", (long) &new_p);
  return 0;
}