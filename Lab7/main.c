//
// Created by sapiest on 27.05.2020.
//

#include <stdint.h>
#include <stdio.h>

#define mask64  0b0010000000100000001000000010000000100000001000000010000000100000
#define mask32  0b00100000001000000010000000100000
#define mask8  0b00100000

int task1(char *str, size_t n);

int task1_just_letters(char *str, size_t n);

int main() {
  char string[] = "testT13 myTEST sISJdsougdWUhdeIWGHDSUDglIkhsjxdgw8ew";
  printf("%s\n", string);
  task1(string, sizeof(string) - 1);
  printf("%s\n", string);

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
      *(str - n) ^= (char)1 << 5u;
    }
  }
}

int task1_just_letters(char *str, size_t n) {
  //пробегаемся по всем 8 байтам в uint64
  str += n;
  for (n; n >= 8; n -= 8) {
    *((uint64_t *)(str - n)) ^= (uint64_t)1 << mask64;
  }
  for (n; n >= 4; n -= 4) {
    *((uint32_t *)(str - n)) ^= (uint32_t)1 << mask32;
  }
  for (n; n > 0; n--) {
    *(str - n) ^= (uint8_t)1 << mask8;
  }
}