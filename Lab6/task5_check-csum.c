//
// Created by sapiest on 13.05.2020.
//
#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include "task5_create-csum.h"
#define BUFF_SIZE 4096

static int check_csum(const char *file_name, const char *file_answer_name);

static int task5_check() {
  int res = check_csum("../../Lab6/tests/test1.txt", "../../Lab6/tests/test1_out.txt");
  res = res || check_csum("../../Lab6/tests/test2.txt", "../../Lab6/tests/test2_out.txt");
  res = res || check_csum("../../Lab6/tests/test3.txt", "../../Lab6/tests/test3_out.txt");
  return res;
}

static int check_csum(const char *file_name, const char *file_answer_name) {
  FILE *in, *ans;
  unsigned char buff[BUFF_SIZE];
  unsigned int size;
  if (!(in = fopen(file_name, "r"))) {
    fprintf(stderr, "File's not open\n");

    return EXIT_FAILURE;
  }

  if (!(ans = fopen(file_answer_name, "r"))) {
    fprintf(stderr, "File's not open\n");

    return EXIT_FAILURE;
  }
  unsigned char expected_sum, check_sum;
  while ((size = fread(&buff, 1, BUFF_SIZE, in))!=0){
    check_sum = crc8(buff, size);
    if((fscanf(ans, "%c", &expected_sum)) == 0){
      fprintf(stderr, "Can`t get csum\n");

      return EXIT_FAILURE;
    }

    if(expected_sum != check_sum){
      fprintf(stderr, "Wrong csum\n");

      return EXIT_FAILURE;
    }
  }

  if(fscanf(ans, "%c", &expected_sum) != EOF){
    fprintf(stderr, "Count of csum more then answer\n");

    return EXIT_FAILURE;
  }

  fclose(in);
  fclose(ans);

  return EXIT_SUCCESS;
}