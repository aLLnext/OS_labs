//
// Created by sapiest on 12.05.2020.
//

#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
void start_timer();

double end_timer();

static int check_xor(const char* file_name, unsigned char answer);

static int task1(){
  int res = check_xor("../../Lab6/tests/test1.txt", 97);
  res = res || check_xor("../../Lab6/tests/test2.txt", 50);
  res = res || check_xor("../../Lab6/tests/test3.txt", 89);
  return res;
}

static int check_xor(const char* file_name, unsigned char answer){
  FILE *f;
  unsigned char check_sum = 0; //начальное значение чек суммы
  //открываем файл
  if(!(f = fopen(file_name, "r"))){
    fprintf(stderr, "File's not open\n");

    return EXIT_FAILURE;
  }

  char c;
  start_timer();
  //считали символ
  while ((c = fgetc(f)) != EOF){
    //добавили XOR
    check_sum ^= c;
  }
  printf("time: %f\n", end_timer());
  fclose(f);
  printf("Checksum: %u, answer: %u\n", check_sum, answer);

  return EXIT_SUCCESS;
}