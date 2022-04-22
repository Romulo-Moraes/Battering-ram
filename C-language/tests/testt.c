#include "./../battering_ram.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  struct battering_ram_data data;

  prepare_battering_ram(&data, false, false, true, false);

  char buffer[128] = {0};

  for (int i = 0; i < 126; i++) {
    get_data(&data, buffer);
    printf("%s\n", buffer);
    get_next_sequence(&data);
  }
}
