//
// Created by sapiest on 25.03.2020.
//
#include <stdio.h>
#include <stdlib.h>

static void task2(long bytes) {
  int *array;
  array = (int *)malloc(bytes);
  while (1) {
    for (int i = 0; i < bytes / sizeof(int); ++i) {
      array[i] = random() % 1000;
    }
  }
}
