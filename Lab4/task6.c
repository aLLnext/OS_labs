//
// Created by sapiest on 30.04.2020.
//
#include <stdlib.h>

static void task6(){
  void *p = malloc(256);
  ((int *)p)[0] = 1;
}