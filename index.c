#include "battering_ram.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  char buffer[256] = "a";
  char final_buffer[] = "sal";
  for (int i = 0; i < 3800000; i++) {
    if (strcmp(final_buffer, buffer) == 0) {
      printf("Found: %s", buffer);
      exit(0);
    }
    printf("%s\n", buffer);
    i = alpha_plus_alpha(i, buffer);
  }
  return 0;
}
