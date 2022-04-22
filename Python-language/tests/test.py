import sys
import os

P = os.path.abspath("./..")

sys.path.insert(1,P)

from battering_ram import *

my_object = battering_ram(False,False,True,False)

for x in range(126):
    print(my_object.get_data())
    my_object.get_next_sequence()




