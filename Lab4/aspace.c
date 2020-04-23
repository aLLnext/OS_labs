//
// Created by sapiest on 23.04.2020.
//

#include <stdio.h>
#include <stdlib.h>

int global;

int task1() {
  long size = 128;

  int local = 5;
  void *p = malloc(128000000);
  int new_local = 0; //создали новую локальную переменную
  void *new_p = malloc(size); // дабавили malloc()

  printf("Address of main is %p\n", task1);
  printf("Address of global is %p\n", &global);
  printf("Address of local is %p\n", &local);
  printf("Address of p is %p\n\n", p);

  //вывод новых адресов
  printf("Address of local is %p\n", &local);
  printf("Address of new local is %p\n", &new_local);
  printf("Address of p %p\n", p);
  printf("Address of new p is %p\n\n", new_p);

  //вывдо адреса указателя
  printf("Address of pointer new p is %p\n", &new_p);
  return 0;
}