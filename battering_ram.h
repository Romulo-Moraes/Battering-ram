#include <ctype.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define PRINTABLES_BEGIN 32
#define PRINTABLES_END 126

#define NUMBERS_BEGIN 48
#define NUMBERS_END 57

#define UPPER_CHARS_BEGIN 65
#define UPPER_CHARS_END 90

#define LOWER_CHARS_BEGIN 97
#define LOWER_CHARS_END 122

#define SYMBOLS_BEGIN_STEP1 32
#define SYMBOLS_BEGIN_END1 47

#define SYMBOLS_BEGIN_STEP2 58
#define SYMBOLS_BEGIN_END2 64

#define SYMBOLS_BEGIN_STEP3 91
#define SYMBOLS_BEGIN_END3 96

#define SYMBOLS_BEGIN_STEP4 123
#define SYMBOLS_BEGIN_END4 126

#define BUFFER_SIZE 512

struct battering_ram_data {
  char *possible_chars;
  char buffer[BUFFER_SIZE];
  char end_value[BUFFER_SIZE];
  bool upper_chars_enabled;
  bool lower_chars_enabled;
  bool numbers_enabled;
  bool symbols_enabled;
  bool initial_value_triggered;
  bool end_value_triggered;
};

void prepare_battering_ram(struct battering_ram_data *data,
                           bool enable_uppercase, bool enable_lowercase,
                           bool enable_symbols, bool enable_numbers) {
  int max_size = 0;
  int dynamic_buffer_index = 0;

  bzero(data->buffer, BUFFER_SIZE);
  bzero(data->end_value, BUFFER_SIZE);
  data->numbers_enabled = enable_numbers;
  data->lower_chars_enabled = enable_lowercase;
  data->upper_chars_enabled = enable_uppercase;
  data->symbols_enabled = enable_symbols;
  data->initial_value_triggered = false;
  data->end_value_triggered = false;

  if (enable_numbers)
    max_size += 10;
  if (enable_uppercase)
    max_size += 26;
  if (enable_lowercase)
    max_size += 26;
  if (enable_symbols)
    max_size += 29;

  data->possible_chars = (char *)malloc(sizeof(char) * max_size);
  bzero(data->possible_chars, max_size);

  if (enable_numbers) {
    short i = NUMBERS_BEGIN;
    for (short j = 0; j < NUMBERS_END - NUMBERS_BEGIN + 1; j++) {
      data->possible_chars[dynamic_buffer_index] = (char)i;

      i += 1;
      dynamic_buffer_index += 1;
    }
  }

  if (enable_uppercase) {
    short i = UPPER_CHARS_BEGIN;
    for (short j = 0; j < UPPER_CHARS_END - UPPER_CHARS_BEGIN + 1; j++) {
      data->possible_chars[dynamic_buffer_index] = (char)i;
      i += 1;
      dynamic_buffer_index += 1;
    }
  }

  if (enable_lowercase) {
    short i = LOWER_CHARS_BEGIN;
    for (short j = 0; j < LOWER_CHARS_END - LOWER_CHARS_BEGIN + 1; j++) {
      data->possible_chars[dynamic_buffer_index] = (char)i;
      i += 1;
      dynamic_buffer_index += 1;
    }
  }
  data->buffer[0] = data->possible_chars[0];
}
void get_data(struct battering_ram_data *data, char *output) {
  strncpy(output, data->buffer, strlen(data->buffer));
}

// Method to reset all bytes to default, in case of carry
void reset_all_bytes(struct battering_ram_data *data) {
  if (data->possible_chars != NULL) {
    char char_to_use = data->possible_chars[0];
    size_t buffer_size = strlen(data->buffer);

    for (short i = 0; i < buffer_size; i++) {
      data->buffer[i] = char_to_use;
    }
  } else {
    printf("Battering ram data segment is NULL");
    exit(1);
  }
}

// Method to insert a byte in the begin of string, case all previous sequences
// didn't match

void insert_char(struct battering_ram_data *data) {
  if (data->possible_chars != NULL) {
    char char_to_use = data->possible_chars[0];

    size_t buffer_size = strlen(data->buffer);
    char *new_buffer = (char *)malloc(sizeof(char) * buffer_size + 1);
    bzero(new_buffer, buffer_size + 1);

    new_buffer[0] = char_to_use;

    strcat(new_buffer, data->buffer);
    bzero(data->buffer, buffer_size);

    strncpy(data->buffer, new_buffer, buffer_size + 1);

    free(new_buffer);
  } else {
    printf("Battering ram data segment is NULL");
    exit(1);
  }
}

// Return true if the next char is outside of possible_chars with the meaning of
// carry
bool get_next_char(struct battering_ram_data *data, char *the_char) {
  if (data->possible_chars != NULL) {
    size_t next_char_position = strcspn(data->possible_chars, the_char) + 1;

    if (next_char_position == strlen(data->possible_chars)) {

      the_char[0] = data->possible_chars[0];

      return true;
    } else {

      the_char[0] = data->possible_chars[next_char_position];
      return false;
    }
  } else {
    printf("Battering ram data segment is NULL\n");
    exit(1);
  }
}

bool is_the_max_possible_matchs(struct battering_ram_data *data) {
  size_t buffer_size = strlen(data->buffer);
  size_t possible_chars_size = strlen(data->possible_chars);

  bool is_the_end = true;

  for (short i = 0; i < buffer_size; i++) {
    if (data->buffer[i] != data->possible_chars[possible_chars_size - 1]) {
      is_the_end = false;
    }
  }

  return is_the_end;
}

bool get_next_sequence(struct battering_ram_data *data) {
  if (data->possible_chars != NULL) {

    if (data->end_value_triggered &&
        strcmp(data->buffer, data->end_value) == 0) {
      return false;
    }

    if (is_the_max_possible_matchs(data)) {
      reset_all_bytes(data);

      insert_char(data);
    } else {

      size_t buffer_size = strlen(data->buffer);
      char current_char = data->buffer[buffer_size - 1];

      bool carry_status = get_next_char(data, &current_char);

      data->buffer[buffer_size - 1] = current_char;

      if (carry_status) {
        for (short i = buffer_size - 2; i >= 0; i--) {
          current_char = data->buffer[i];

          carry_status = get_next_char(data, &current_char);

          data->buffer[i] = current_char;
          if (!carry_status)
            break;
        }
      }
    }
  } else {
    printf("Battering ram data segment is NULL\n");
    exit(1);
  }

  return true;
}

void check_allowed_chars(struct battering_ram_data *data, char *buffer) {
  if (data->possible_chars != NULL) {

    size_t buffer_size = strlen(buffer);
    char error_buffer[15] = "";

    for (int i = 0; i < buffer_size; i++) {

      if (isdigit(buffer[i])) {
        if (!data->numbers_enabled) {
          strcpy(error_buffer, "numbers");
        }
      }

      if (islower((buffer[i]))) {
        if (!data->lower_chars_enabled) {
          strcpy(error_buffer, "lower chars");
        }
      }

      if (isupper((buffer[i]))) {
        if (!data->upper_chars_enabled) {
          strcpy(error_buffer, "upper chars");
        }
      }
    }

    if (strcmp(error_buffer, "") != 0) {
      printf("Char array has not allowed chars! (%s)", error_buffer);
      exit(1);
    }

  } else {
    printf("Battering ram data segment is NULL\n");
    exit(1);
  }
}

void set_start_value(struct battering_ram_data *data, char *initial_value) {

  check_allowed_chars(data, initial_value);

  data->initial_value_triggered = true;
  strncpy(data->buffer, initial_value, strlen(initial_value));
}

void set_end_value(struct battering_ram_data *data, char *end_value) {
  check_allowed_chars(data, end_value);

  data->end_value_triggered = true;
  strncpy(data->end_value, end_value, strlen(end_value));
}
