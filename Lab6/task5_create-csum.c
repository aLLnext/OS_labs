//
// Created by sapiest on 12.05.2020.
//


#include "task5_create-csum.h"

static int task5(){
  int res = create_csum("../../Lab6/tests/test1.txt", "../../Lab6/tests/test1_out.txt");
  res = res || create_csum("../../Lab6/tests/test2.txt", "../../Lab6/tests/test2_out.txt");
  res = res || create_csum("../../Lab6/tests/test3.txt", "../../Lab6/tests/test3_out.txt");
  return res;
}