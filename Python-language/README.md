<div align="center"><h1>This is the Python version of the Battering-Ram</h1></div>

## How to use it?
The lib has some main functions that gives all the functionality of the bruteforce idea.
  ### Explaning the main functions
  The battering_ram class is the main structure of the library, it has a constructor that accept some boolean values, basically to enable and disable the chars types that will be used on the algorithm
  ```py
  def __init__(self,enable_upper_case,enable_lower_case,enable_symbols,enable_numbers) 
  ```
  <br/>
  
 The set_start_value is a method that will put a default value in the Battering-Ram data space, all next's values will be started from there,if not used then the first value will be defined by the class constructor looking for  compatibility with the chars config
  ```py
  def set_start_value(self,initial_value)
  ```
   <br/>
  
The set_end_value function will set a max value to the algorithm, the main function will gives a flag which alerts you that the program reached the end, if not used the program never alerts you and probally will run forever.
```py
def set_end_value(self,end_value)
```
<br/>
  

The get_next_sequence is the main function of the library, this will always get next next logical sequence of chars and put in a buffer that can be caught after. if set_end_value used then this function will return False when reached the target, if not then will always return True
```py
def get_next_sequence(self)
```
<br/>  

The get_data function is the complement of the previous function, after of get_next_sequence you can use get_data to fetch the results
```py
def get_data(self):
```
<br/>

## Simple Battering-Ram structure

Example:
```py
import os
import sys

# Some config stuff...
path = os.path.abspath("..")
sys.path.insert(1,path)

from battering_ram import *

# Setting to lib to run only lower case chars
br = battering_ram(False,True,False,False)

data_fetch = ""

# Set max value
br.set_end_value("fooo")

# This will run until reach the "fooo"
while(br.get_next_sequence()):

    # Store the data
    data_fetch = br.get_data()

    # Fictional target value
    if(data_fetch == "eeee"):
        print("Gotcha!")
        exit(0)
    else:
        print(data_fetch)
```
The output of the program above is:
```txt
a
b
c
...
...
...
eedx
eedy
eedz
eeea
eeeb
eeec
eeed
Gotcha!
```



## Splitting the work
Is also possible split the work between threads with the objective of find the final result most quickly

In the following moment i will show a code (poor) of multithread, got in mind that thread 2 always find the value in first place, because it started in front of thread 1. Using this strategy is possible make greater workers

Code example of multithreading:
```py
import os
import sys
from threading import Thread
import time

path = os.path.abspath("..")

sys.path.insert(1,path)

from battering_ram import *

can_stop = False

# Fictional target_value
fictional_target_value = "baar"

def another_worker():
    
    br = battering_ram(False,True,False,False)

    data_fetch = ""

    # Start from another pointer to reduce possible process time
    br.set_start_value("zzz")
    br.set_end_value("zzzzzzzz")

    while(br.get_next_sequence()):
        data_fetch = br.get_data()
    
        if(data_fetch == fictional_target_value):
            print("Gotcha! Thread 2")

            global can_stop
            can_stop = True
            exit(0)
        else:
            print(data_fetch)   


th1 = Thread(target=another_worker)
th1.start()

br = battering_ram(False,True,False,False)

data_fetch = ""

br.set_end_value("zzzzz")
while(br.get_next_sequence() and not can_stop):
    data_fetch = br.get_data()

    if(data_fetch == fictional_target_value):
        print("Gotcha! Thread 1")

        can_stop = True
        while(not can_stop):
           time.sleep(1) 
        exit(0)
    else:
        print(data_fetch)
```
