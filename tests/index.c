#include "./../battering_ram.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static bool can_stop = false;
static char target1[] = "romu";
static char target2[] = "r0m8";

int main() {

  char buffer[5] = "a";
  int i = 0;

  while (true) {

    if (strcmp(buffer, target2) == 0) {
      printf("value 2: %s\n", buffer);
      break;
    }

    printf("%s\n", buffer);
    //    usleep(10000);

    i = get_next_sequence(i, buffer, LOWER_CASE_ONLY, true);
    i += 1;
  }

  return 0;
}
