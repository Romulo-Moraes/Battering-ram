#include "./../battering_ram.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  char buffer[256] = "a";
  char final_buffer[] = "ROMU";
  int i = 0;
  while (1) {
    if (strcmp(buffer, final_buffer) == 0) {
      printf("Found: %s", buffer);
      exit(0);
    }
    i = alpha_plus_alpha(i, buffer, UPPER_CASE_ONLY);
    printf("%s\n", buffer);
    i += 1;
    //   usleep(10000);
  }

  return 0;
}
