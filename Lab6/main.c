//
// Created by sapiest on 12.05.2020.
//

#include <sys/time.h>
#include "task1_check-xor.c"
#include "task2_check-fletcher.c"
#include "task3_crc.c"
#include "task5_create-csum.c"
#include "task5_check-csum.c"

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

int main(){
//  printf("XOR\n");
//  task1();
//  printf("Fletcher\n");
//  task2();
//  printf("Crc\n");
//  task3();
  printf("crc 8 bit\n");
  task5();
  task5_check();
}