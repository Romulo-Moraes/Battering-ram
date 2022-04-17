#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define UPPER_CHARS_BEGIN 65
#define UPPER_CHARS_END 90

#define LOWER_CHARS_BEGIN 97
#define LOWER_CHARS_END 122

#define LOWER_CASE_ONLY 1
#define UPPER_CASE_ONLY 2
#define LOWER_AND_UPPER_CASE 3

void reset_all_bytes(char *buffer, int battering_ram_mode) {
  size_t buffer_size = strlen(buffer);
  char replacement_char;

  if (battering_ram_mode == UPPER_CASE_ONLY) {
    replacement_char = 'A';
  } else {
    replacement_char = 'a';
  }

  for (int i = 0; i < buffer_size; i++) {
    buffer[i] = replacement_char;
  }
}

void insert_char(char *buffer, int battering_ram_mode) {
  size_t buffer_size = strlen(buffer);

  char *new_buffer = (char *)malloc(sizeof(char) * buffer_size + 1);
  if (battering_ram_mode == UPPER_CASE_ONLY) {
    new_buffer[0] = 'A';
  } else {
    new_buffer[0] = 'a';
  }
  strcat(new_buffer, buffer);
  bzero(buffer, buffer_size);
  strncpy(buffer, new_buffer, buffer_size + 1);
}

int alpha_plus_alpha(int iteration_number, char *buffer,
                     int battering_ram_mode) {
  size_t buffer_size = strlen(buffer);
  double max_capacity = 0;
  if (battering_ram_mode == LOWER_AND_UPPER_CASE) {
    max_capacity = pow(52, buffer_size);
  } else {
    max_capacity = pow(26, buffer_size);
  }

  if (iteration_number == max_capacity) {
    reset_all_bytes(buffer, battering_ram_mode);
    insert_char(buffer, battering_ram_mode);
    return 0;
  } else {

    char *final_buffer = (char *)malloc(sizeof(char) * buffer_size);
    int current_buffer_location = buffer_size - 1;

    bool carry = false;
    int current_ascii_representation = 0;

    current_ascii_representation = (int)buffer[current_buffer_location];
    current_ascii_representation += 1;

    switch (battering_ram_mode) {
    case LOWER_CASE_ONLY:

      if (current_ascii_representation > LOWER_CHARS_END) {
        carry = true;
        current_ascii_representation = LOWER_CHARS_BEGIN;
      }
      break;

    case UPPER_CASE_ONLY:
      if (current_ascii_representation > UPPER_CHARS_END) {
        carry = true;
        current_ascii_representation = UPPER_CHARS_BEGIN;
      }
      break;

    case LOWER_AND_UPPER_CASE:
      if (current_ascii_representation > LOWER_CHARS_END) {
        current_ascii_representation = UPPER_CHARS_BEGIN;
      } else {
        if (current_ascii_representation > UPPER_CHARS_END &&
            current_ascii_representation < LOWER_CHARS_BEGIN) {
          current_ascii_representation = LOWER_CHARS_BEGIN;
          carry = true;
        }
      }
      break;
    }
    buffer[current_buffer_location] = (char)current_ascii_representation;

    if (carry) {
      for (int i = current_buffer_location - 1; i >= 0; i--) {
        if (carry == true) {
          current_ascii_representation = (int)buffer[i];
          current_ascii_representation += 1;

          switch (battering_ram_mode) {
          case LOWER_CASE_ONLY:

            if (current_ascii_representation > LOWER_CHARS_END) {
              current_ascii_representation = LOWER_CHARS_BEGIN;
            } else {
              carry = false;
            }
            break;

          case UPPER_CASE_ONLY:
            if (current_ascii_representation > UPPER_CHARS_END) {
              current_ascii_representation = UPPER_CHARS_BEGIN;
            } else {
              carry = false;
            }
            break;
          case LOWER_AND_UPPER_CASE:
            if (current_ascii_representation > LOWER_CHARS_END) {
              current_ascii_representation = UPPER_CHARS_BEGIN;
              carry = false;
            } else {
              if (current_ascii_representation > UPPER_CHARS_END &&
                  current_ascii_representation < LOWER_CHARS_BEGIN) {
                current_ascii_representation = LOWER_CHARS_BEGIN;
              } else {
                carry = false;
              }
            }
            break;
          }

          buffer[i] = (char)current_ascii_representation;
        } else {
          break;
        }
      }
    }
  }
  return iteration_number;
}
