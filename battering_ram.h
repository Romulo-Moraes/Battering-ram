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

// Method to reset all bytes to default, in case of carry
void reset_all_bytes(char *buffer, int battering_ram_mode) {
  // Get size for iteration later
  size_t buffer_size = strlen(buffer);
  char replacement_char;

  // Resolve the necessary char looking for choosed mode
  if (battering_ram_mode == UPPER_CASE_ONLY) {
    replacement_char = 'A';
  } else {
    replacement_char = 'a';
  }

  // Reset all bytes
  for (int i = 0; i < buffer_size; i++) {
    buffer[i] = replacement_char;
  }
}

// Method to insert a byte in the begin of string, case all previous sequences
// didn't match
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

// Main structure of the module, here for each given string the next value will
// be get following the binary's carry logic
int get_next_sequence(int iteration_number, char *buffer,
                      int battering_ram_mode) {

  // Get buffer size to get max capacity of the current string
  size_t buffer_size = strlen(buffer);
  double max_capacity = 0;

  // Get max capacity of values by the choosed mode
  if (battering_ram_mode == LOWER_AND_UPPER_CASE) {
    max_capacity = pow(52, buffer_size);
  } else {
    max_capacity = pow(26, buffer_size);
  }

  // If the iteration times reach the capacity then reset all bytes and insert a
  // new char in begin of buffer
  if (iteration_number == max_capacity) {
    reset_all_bytes(buffer, battering_ram_mode);
    insert_char(buffer, battering_ram_mode);

    // Return 0 to 'i' to start again the count
    return 0;
  } else {

    //    char *final_buffer = (char *)malloc(sizeof(char) * buffer_size);
    int current_buffer_location = buffer_size - 1;

    // Necessary variables for carry detection and current char
    bool carry = false;
    int current_ascii_representation = 0;

    // Always get the less significant char and append one value in ascii
    // representation
    current_ascii_representation = (int)buffer[current_buffer_location];
    current_ascii_representation += 1;

    // Switch to handle the next instruction in the choosed mode
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
