<div align="center">
  <h1>Battering-Ram</h1>
  <img width="300px" src="./assets/Battering-Ram image.jpeg"/>
  <h3>Bruteforce module for C programming</h3>
</div>

## What's that ?
This program is an single file header-only module for C language whose will get the next sequence of a string with the target of Bruteforce. Created with inspiration in the binary base, on yours carrys. This module can find values with Lower case, Upper case, Numbers and Symbols.

## How to use it?
The lib has some main functions that gives all the functionality of the bruteforce idea, is the following methods:
```c
// Prepare the tool to start with some chars types enabled of disabled
void prepare_battering_ram(struct battering_ram_data *data,bool enable_uppercase, bool enable_lowercase,bool enable_symbols, bool enable_numbers);

// Set an initial value which will start the algorithm
void set_start_value(struct battering_ram_data *data, char *initial_value);

// Set the max value that the tool can reach
void set_end_value(struct battering_ram_data *data, char *end_value);

// Get the next sequence of the current string
void get_next_sequence(struct battering_ram_data *data);

// Get the data after get_next_sequence from lib struct
void get_data(struct battering_ram_data *data, char *output);
```
The library file has more methods, but it's only for internal pourposes and shouldn't be used

Example:
```c
#include "./../battering_ram.h"
#include <stdbool.h>

int main() {
  char buffer[256] = {0};

  struct battering_ram_data data;
  prepare_battering_ram(&data, false, 1, false, false);

  // The struct already start with an initial value and can be catched by get_data
  get_data(&data, buffer);

  printf("%s\n", buffer);

  get_next_sequence(&data);

  get_data(&data, buffer);

  printf("%s", buffer);
  return 0;
}
```
The output of the program above is:
```txt
a
b
```

## Splitting the work
Is also possible split the work between threads with the objective of find the final result most quickly

Code example of multithreading:
```c
#include "./../battering_ram.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdbool.h>

static char target[] = "note";
bool value_not_found = true;

void *another_worker() {
  char output[128] = {0};

  struct battering_ram_data data;
  prepare_battering_ram(&data, false, true, false, false);

  set_start_value(&data, "aazz");

  while (value_not_found) {
    get_next_sequence(&data);

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

  while (value_not_found) {
    get_next_sequence(&data);

    get_data(&data, output);
    if (strcmp(output, target) == 0) {
      value_not_found = false;
      printf("Found: %s! thread 1\n", output);
      exit(0);
    }
    printf("%s\n", output);
  }

  return 0;
}
```

## Warning!
Sometimes a while True can be dangerous because a char buffer has fixed length and a overflow can happens. Just use math to reach some target.

Example:
  To find the name romulo 26⁶ is the enough (Lower case only) which 6 is the number of position in char array. on doubt create a buffer of 256 or more positions, but got in mind that is a bad practice
  
## How to compile
The compilation of the module is pretty easy, the only difference of a normal gcc index.c -o index is that the module use math.h, then the compilation command is like that:

```txt
gcc index.c -o index -lm 
```
Linking the math module with "-lm"
