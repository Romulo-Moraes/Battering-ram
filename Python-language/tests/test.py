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
