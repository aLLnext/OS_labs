//
// Created by sapiest on 30.04.2020.
//
#include "task1.c"
#include "task2.c"
#include "task3_mytail.c"
#include "task4.c"
#include "task5_myls.c"
#include "task6_myfind.c"
#include <stdio.h>
#include<string.h>

static struct timeval tv1, tv2, dtv;

static struct timezone tz;

//старт функции, которая измеряет время
void start_timer() {gettimeofday(&tv1, &tz);}

//функция, которая возвращает время в секундах, прошедшее с запуска таймера
double end_timer() {
  gettimeofday(&tv2, &tz);
  dtv.tv_sec = tv2.tv_sec - tv1.tv_sec;
  dtv.tv_usec = tv2.tv_usec - tv1.tv_usec;
  if (dtv.tv_usec < 0) {
    dtv.tv_sec--;
    dtv.tv_usec += 1e6;
  }
  return ((double)dtv.tv_sec * 1000 + (double)dtv.tv_usec / 1000) / 1000;
}

int main(int argc, char *argv[]) {
//  task1();
//  task2();
  //task3(argc, argv);
  //task4();
  //task5(argc, argv);
  task6(argc, argv);
  return 0;
}