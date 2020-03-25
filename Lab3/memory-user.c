//
// Created by sapiest on 25.03.2020.
//
#include <stdio.h>
#include <stdlib.h>

static void task2(long bytes) {
  int *array = (int *)malloc(bytes); //выделяем динамически память под массив int
  while (1) {
    for (int i = 0; i < bytes / sizeof(int); ++i) { //бесконечный цикл по элементам
      array[i] = random() % 1000;
    }
  }
}
