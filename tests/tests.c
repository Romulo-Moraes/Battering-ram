#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

char original_sequence[4];

#define UPPER_CHARS_BEGIN 65
#define UPPER_CHARS_END 90

#define LOWER_CHARS_BEGIN 97
#define LOWER_CHARS_END 122

void reset_all_bytes(char *buffer);
void insert_char(char *buffer);
int alpha_plus_alpha(int iteration_number, char *buffer);

int main() {
  int i = 0;
  char buffer[7] = {0};
  fgets(buffer, 7, stdin);
  buffer[strcspn(buffer, "\n")] = '\0';

  char bruteforce_buffer[256] = "a";

  for (i = 0; i < 308915776; i++) {
    if (strcmp(buffer, bruteforce_buffer) == 0) {
      printf("Found: %s", bruteforce_buffer);
      exit(0);
    }
    printf("%s\n", bruteforce_buffer);
    i = alpha_plus_alpha(i, bruteforce_buffer);
    //    usleep(50000);
  }
  return 0;
}

void reset_all_bytes(char *buffer) {
  size_t buffer_size = strlen(buffer);
  for (int i = 0; i < buffer_size; i++) {
    buffer[i] = 'a';
  }
}

void insert_char(char *buffer) {
  size_t buffer_size = strlen(buffer);

  char *new_buffer = (char *)malloc(sizeof(char) * buffer_size + 1);
  new_buffer[0] = 'a';
  strcat(new_buffer, buffer);
  bzero(buffer, buffer_size);
  strncpy(buffer, new_buffer, buffer_size + 1);
}

int alpha_plus_alpha(int iteration_number, char *buffer) {
  size_t buffer_size = strlen(buffer);
  double max_capacity = pow(26, buffer_size);
  //  printf(">>> %d\n", buffer_size);

  if (iteration_number == max_capacity) {
    reset_all_bytes(buffer);
    insert_char(buffer);
    return 0;
  } else {

    char *final_buffer = (char *)malloc(sizeof(char) * buffer_size);
    int current_buffer_location = buffer_size - 1;

    bool carry = false;
    int current_ascii_representation = 0;

    current_ascii_representation = (int)buffer[current_buffer_location];
    current_ascii_representation += 1;
    if (current_ascii_representation > LOWER_CHARS_END) {
      carry = true;
      current_ascii_representation = LOWER_CHARS_BEGIN;
    }

    buffer[current_buffer_location] = (char)current_ascii_representation;

    if (carry) {
      for (int i = current_buffer_location - 1; i >= 0; i--) {
        if (carry == true) {
          current_ascii_representation = (int)buffer[i];
          current_ascii_representation += 1;
          if (current_ascii_representation > LOWER_CHARS_END) {
            current_ascii_representation = LOWER_CHARS_BEGIN;
          } else {
            carry = false;
          }
          buffer[i] = (char)current_ascii_representation;
        } else {
          break;
        }
      }
    }
  }
  return iteration_number;
  //  final_buffer[i] = (char)current_ascii_representation;
}
