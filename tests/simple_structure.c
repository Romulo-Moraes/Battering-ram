#include "./../battering_ram.h"
#include <stdbool.h>

int main() {

  char output[256] = {0};

  struct battering_ram_data data;
  prepare_battering_ram(&data, false, true, false, false);
  set_start_value(&data, "a");
  set_end_value(&data, "zzz");

  while (get_next_sequence(&data)) {
    get_data(&data, output);

    if (strcmp(output, "zzy") == 0) {
      printf("gotcha!");
      exit(0);
    }

    printf("%s\n", output);
  }

  return 0;
}
