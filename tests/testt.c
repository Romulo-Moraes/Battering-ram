#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#define UPPER_CHARS_BEGIN 65
#define UPPER_CHARS_END 90

#define LOWER_CHARS_BEGIN 97
#define LOWER_CHARS_END 122

#define LOWER_CASE_ONLY 1
#define UPPER_CASE_ONLY 2
#define LOWER_AND_UPPER_CASE 3

void insert_char(char *buffer, int battering_ram_mode) {
  // Get size of string
  size_t buffer_size = strlen(buffer);

  // Dynamic buffer size is necessary cause default buffer don't accept size
  // defined in runtime
  char *new_buffer = (char *)malloc(sizeof(char) * buffer_size + 1);

  // Resolve the necessary char looking for choosed mode, and put the value in
  // begin of dynamic buffer
  if (battering_ram_mode == UPPER_CASE_ONLY) {
    new_buffer[0] = 'A';
  } else {
    new_buffer[0] = 'a';
  }

  // concat with original buffer
  strcat(new_buffer, buffer);

  // Zero original buffer
  bzero(buffer, buffer_size);

  // Copy everything of dynamic buffer to original buffer
  strncpy(buffer, new_buffer, buffer_size + 1);

  free(new_buffer);
}

int main() {
  char buffer[4] = "aa";
  insert_char(buffer, LOWER_CASE_ONLY);

  printf("%s", buffer);
  return 0;
}
