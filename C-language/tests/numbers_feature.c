#include <stdio.h>

#define NUMBERS_BEGIN 48
#define NUMBERS_END 57

int main() {
  for (int i = NUMBERS_BEGIN; i <= NUMBERS_END; i++) {
    printf("%c\n", i);
  }
  return 0;
}
