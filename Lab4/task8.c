//
// Created by sapiest on 30.04.2020.
//

#include <stdio.h>
#include <stdlib.h>

static void task8(){
  int *data = malloc(100 * sizeof(int));
  free(data);
  printf("%i", data[1]);
}