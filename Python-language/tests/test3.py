import os
import sys
from threading import Thread
import time

path = os.path.abspath("..")

sys.path.insert(1,path)

from battering_ram import *

br = battering_ram(False,True,False,False)
br.set_start_value("zzzz")

print(br.get_data())


