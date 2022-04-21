
## How to use it?
The lib has some main functions that gives all the functionality of the bruteforce idea.
  ### Explaning the main functions
  The prepare battering_ram function will initialize the main structure, nothing should be did without this step! this accept as first param the structure pointer, and the followings params is to allow or denie the use of some chars, like lower case, numbers, symbols...
  ```c
  void prepare_battering_ram(struct battering_ram_data *data,bool enable_uppercase, bool enable_lowercase,bool enable_symbols, bool enable_numbers);
  ```
  <br/>
  
 The set_start_value is most used when you wan't start from a offset that you already know, this accept as first param the main structure pointer and the second as the initial value. But always remember! the initial_value need match with the config of the prepare_battering_ram method.
  ```c
  void set_start_value(struct battering_ram_data *data, char *initial_value);
  ```
   <br/>
  
The set_end_value is used when you wan't stop the process just in the moment that the current data reached a limit defined by this function, this accept a pointer of the main structure and the end_value.
```c
void set_end_value(struct battering_ram_data *data, char *end_value);
```
<br/>
  

The get_next_sequence is the most important function of the library, it will get the next sequence of chars defined by the prepare_battering_ram function, this accept the only a param, that need be a pointer of main structure.
```c
void get_next_sequence(struct battering_ram_data *data);
```
<br/>  

The get_data is the complement of get_next_sequence function, the data is stored in the main struct then with this function you can get the value from it, this accept the pointer of main structure and a buffer pointer as data output
```c
void get_data(struct battering_ram_data *data, char *output);
```
<br/>

  ### The main struct
  The main data holder of this lib is a simple struct of vanilla C language, this looks like this:
  ```c
  
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
  ```
  

The library file has more methods, but it's only for internal pourposes and shouldn't be used

## Simple Battering-Ram structure


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

## Simple Battering-Ram structure
```c
#include "./../battering_ram.h"
#include <stdbool.h>

int main() {

  char output[256] = {0};

  struct battering_ram_data data;
  prepare_battering_ram(&data, false, true, false, false);
  set_start_value(&data, "a");
  set_end_value(&data, "zzz");

  while (get_next_sequence(&data)) {
    get_data(&data, output);

    if (strcmp(output, "zzy") == 0) {
      printf("gotcha!");
      exit(0);
    }

    printf("%s\n", output);
  }

  return 0;
}
```

## Splitting the work
Is also possible split the work between threads with the objective of find the final result most quickly

Code example of multithreading:
```c
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
```
## How to compile
The library don't use any special dependencies, then the compilation by only using this lib is:
```txt
gcc index.c -o index
```
