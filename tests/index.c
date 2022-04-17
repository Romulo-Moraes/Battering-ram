#include "./../battering_ram.h"
#include <string.h>

int main() {
  char buffer[5] = "a";
  char final_buffer[] = "FOOO";
  int i = 0;

  while (1) {
    if (strcmp(buffer, final_buffer) == 0) {
      printf("Found: %s", buffer);
      exit(0);
    }
    i = get_next_sequence(i, buffer, UPPER_CASE_ONLY);
    printf("%s\n", buffer);
    i += 1;
  }

  return 0;
}
