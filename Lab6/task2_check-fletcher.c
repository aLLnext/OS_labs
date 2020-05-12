//
// Created by sapiest on 12.05.2020.
//

#include <bits/types/FILE.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void start_timer();

double end_timer();

static int check_fletcher(const char* file_name, uint16_t answer);

static int task2(){
  int res = check_fletcher("../../Lab6/tests/test1.txt", 18468);
  res = res || check_fletcher("../../Lab6/tests/test2.txt", 64033);
  res = res || check_fletcher("../../Lab6/tests/test3.txt", 15392);
  return res;
}

static int check_fletcher(const char* file_name, uint16_t answer){
  FILE *f;
  uint16_t sum1 = 0, sum2 = 0;

  if(!(f = fopen(file_name, "r"))){
    fprintf(stderr, "File's not open\n");

    return EXIT_FAILURE;
  }

  char c;

  start_timer();
  while ((c = fgetc(f)) != EOF){
    sum1 = (sum1 + c) % 255;
    sum2 = (sum2 + sum1) % 255;
  }
  uint16_t check_sum = (sum2 << 8) | sum1;

  printf("time: %f\n", end_timer());
  fclose(f);
  printf("Checksum: %u, answer: %u\n", check_sum, answer);
  return EXIT_SUCCESS;
}