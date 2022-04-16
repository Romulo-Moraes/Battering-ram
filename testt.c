#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

void insert_char(char *buffer) {
  size_t buffer_size = strlen(buffer);

  char *new_buffer = (char *)malloc(sizeof(char) * buffer_size + 1);
  new_buffer[0] = 'a';
  strcat(new_buffer, buffer);
  bzero(buffer, buffer_size);
  strncpy(buffer, new_buffer, buffer_size + 1);
}

void opa(int *salve) { *salve = 10; }

int main() {
  int aaa = 20;
  opa(&aaa);
  printf("%d", aaa);
  return 0;
}
