#include "./../battering_ram.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdbool.h>

// Fictional target
static char target[] = "note";
bool value_not_found = true;

void *another_worker() {
  char output[128] = {0};

  struct battering_ram_data data;
  prepare_battering_ram(&data, false, true, false, false);

  set_start_value(&data, "aazz");

  // Fictional target
  set_end_value(&data, "note");

  while (get_next_sequence(&data)) {

    get_data(&data, output);
    if (strcmp(output, target) == 0) {
      value_not_found = false;
      printf("Found: %s! thread 2\n", output);
      exit(0);
    }
    printf("%s\n", output);
  }
}

int main() {

  pthread_t thread;
  pthread_create(&thread, NULL, another_worker, NULL);
  pthread_detach(thread);

  char output[128] = {0};

  struct battering_ram_data data;
  prepare_battering_ram(&data, false, true, false, false);

  set_start_value(&data, "a");

  // Fictional target
  set_end_value(&data, "aazz");

  while (get_next_sequence(&data)) {

    get_data(&data, output);
    if (strcmp(output, target) == 0) {
      value_not_found = false;
      printf("Found: %s! thread 1\n", output);
      exit(0);
    }
    printf("%s\n", output);
  }
  while (value_not_found) {
    sleep(1);
  }

  return 0;
}
