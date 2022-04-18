<div align="center">
  <h1>Battering-Ram</h1>
  <img width="300px" src="./assets/Battering-Ram image.jpeg"/>
  <h3>Bruteforce module for C programming</h3>
</div>

## What's that ?
This program is an single file header-only module for C language whose will get the next sequence of a string with the target of Bruteforce. Created with inspiration in the binary base, on yours carrys. This module can find value with "Only lower case", "Only upper case" and "Lower and upper case".

## How to use it?
The use of it is really simple, the main structure need be inside of a loop which each iteration the next value will be returned on your buffer with the pourpose of test in some bruteforce situation.

Example:
```c
#include "./../battering_ram.h"
#include <string.h>

int main() {
  char buffer[5] = "a";
  char final_buffer[] = "FOOO";
  int i = 0;

  while (1) {
    if (strcmp(buffer, final_buffer) == 0) {
      printf("Found: %s", buffer);
      exit(0);
    }
    i = get_next_sequence(i, buffer, UPPER_CASE_ONLY);
    printf("%s\n", buffer);
    i += 1;
  }

  return 0;
}
```
Pay attention that the main method need a integer variable that need be incremented in each iteration, it's to know the time of some operations in the buffer.

### The Chars Cases
Some times you need each only lower case words, other times only upper case, then to save process time you can choose when use each of them, or in the last option, both of them. here is the options:

```c
#define LOWER_CASE_ONLY 1
#define UPPER_CASE_ONLY 2
#define LOWER_AND_UPPER_CASE 3
```

## Splitting the work
Is pretty possible use more than a thread to do the work, using strategy to reach more quick in the final target.

Example: start a thread from 'a' and start another thread from 'aaaaa', who reach the value first win.

Code example of multithreading:
```c
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
  char buffer[5] = "a";
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
  char buffer[5] = "a";
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
