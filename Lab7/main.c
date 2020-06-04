//
// Created by sapiest on 27.05.2020.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//
//#define mask64  0b0010000000100000001000000010000000100000001000000010000000100000
//#define mask32  0b00100000001000000010000000100000
//#define mask8  0b00100000

int task1(char *str, size_t n);

int task1_just_letters(char *str, size_t n);

static u_int32_t mask32b;
static u_int64_t mask64b;

int main() {
  for (int byte = 0; byte < 4; ++byte) {
    mask32b |= (u_int32_t) 1 << (byte * 8u + 5u);
  }

  for (int byte = 0; byte < 8; ++byte) {
    mask64b |= (u_int64_t) 1 << (byte * 8u + 5u);
  }



  char string[] = "testT13 myTEST sISJdsougdWUhdeIWGHDSUDglIkhsjxdgw8ew";
  printf("%s\n", string);
  task1(string, sizeof(string) - 1);
  printf("%s\n", string);

  char str_test[] = "test";
  printf("%s\n", str_test);
  task1_just_letters(str_test, sizeof(str_test) - 1);
  printf("%s\n", str_test);


  uint8_t str_without_numbers[] = "udhiSLDhsnlajcmlkdsjskdlJWeulEIW";
  printf("%s\n", str_without_numbers);
  task1_just_letters(str_without_numbers, sizeof(str_without_numbers) - 1);
  printf("%s\n", str_without_numbers);
}

int isletter(char *str) {
  //проверяем что это буква
  char symbol = (char)str;
  if (symbol >= 'A' && symbol <= 'z') {
    return 0;
  }
  return 1;
}

int task1(char *str, size_t n) {
  str += n; //переводим указатель на конец строки
  for (n; n > 0; n--) {
    if (isletter(*(str - n)) == 0) {
      //делаем сдвиг на символ. После смещаем на 6 бит и делаем XOR
      *(str - n) ^= (uint8_t)1 << 5u;
    }
  }
  return EXIT_SUCCESS;
}

int task1_just_letters(char *str, size_t n) {
  //пробегаемся по всем 8 байтам в uint64
  str += n;
  for (n; n >= 8; n -= 8) {
    *((uint64_t *)(str - n)) ^= mask64b;
  }
  for (n; n >= 4; n -= 4) {
    *((uint32_t *)(str - n)) ^=  mask32b;
  }
  for (n; n > 0; n--) {
    *(str - n) ^= (uint8_t)1 << 5u;
  }

  return EXIT_SUCCESS;
}