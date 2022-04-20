#include "./../battering_ram.h"
#include <stdio.h>

int main() {
  struct battering_ram_data data;
  prepare_battering_ram(&data, false, true, false, true);

  char output[256] = {0};

  while (true) {
    get_next_sequence(&data);
    get_data(&data, output);

    if (strcmp(output, "r0mu") == 0) {
      printf("Found: %s", output);
      exit(0);
    } else {
      printf("%s\n", output);
    }
  }

  return 0;
}
