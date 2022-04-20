#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char original_binary[9] = {0};

void bin_plus_bin(char *binary_buffer, char *output) {
  char isolate_bit[2] = {0};
  char final_buffer[9] = {0};
  size_t buffer_size = strlen(binary_buffer);
  char value_to_append[] = "00000001";
  int math_result = 0;
  bool carry = false;

  for (int i = buffer_size - 1; i >= 0; i--) {
    isolate_bit[0] = binary_buffer[i];
    math_result = atoi(isolate_bit);
    isolate_bit[0] = value_to_append[i];
    math_result += atoi(isolate_bit);
    isolate_bit[0] = '\0';

    if (math_result > 1) {
      if (carry) {
        final_buffer[i] = '1';

      } else {
        final_buffer[i] = '0';
        carry = true;
      }
    } else {
      if (carry) {
        if (math_result == 1) {
          final_buffer[i] = '0';
        } else {
          final_buffer[i] = '1';
          carry = false;
        }
      } else {
        if (math_result == 1) {
          final_buffer[i] = '1';
        } else {
          final_buffer[i] = '0';
        }
      }
    }
  }

  strncpy(output, final_buffer, 8);
}

int main() {
  printf("Type some 8 bit binary:");
  fgets(original_binary, 9, stdin);
  char buffer[] = "00000000";
  for (int i = 0; i < 256; i++) {
    if (strcmp(original_binary, buffer) == 0) {
      printf("Found: %s", buffer);
      break;
    }
    bin_plus_bin(buffer, buffer);
  }

  return 0;
}
