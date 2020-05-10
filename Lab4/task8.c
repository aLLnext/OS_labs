//
// Created by sapiest on 30.04.2020.
//

#include <stdio.h>
#include <stdlib.h>

int main(){
  int *data = malloc(100 * sizeof(int));
  data[1] = 1;
  free(data);
  printf("%i", data[1]);
}