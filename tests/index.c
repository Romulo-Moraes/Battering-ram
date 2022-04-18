#include "./../battering_ram.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static bool can_stop = false;
static char target1[] = "romu";
static char target2[] = "umor";

// Thread to reach "romu"
void *another_thread() {
  char buffer[4] = "a";
  int i = 0;
  while (true) {
    if (strcmp(buffer, target1) == 0) {
      printf("value 1: %s\n", buffer);
      can_stop = true;
      break;
    }
    i = get_next_sequence(i, buffer, LOWER_CASE_ONLY);
    i += 1;
  }
  pthread_exit(0);
}

int main() {
  // Start a new thread to reach the first target
  pthread_t thread1;
  pthread_create(&thread1, NULL, another_thread, NULL);
  pthread_detach(thread1);

  // Code segment to reach the second target
  char buffer[4] = "a";
  int i = 0;
  while (true) {
    if (strcmp(buffer, target2) == 0) {
      printf("value 2: %s\n", buffer);
      break;
    }
    i = get_next_sequence(i, buffer, LOWER_CASE_ONLY);
    i += 1;
  }

  // Wait or do something...
  while (!can_stop) {
    sleep(2);
  }

  // End
  printf("Both value found!\n");

  return 0;
}
