#!/usr/bin/env python
#list of characters in order. 0->61

import sys

ALIGN = ord('0')
MAX = 75;

s = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
values = {}
for index, i in enumerate(s):
  values[ord(i)-ALIGN] = index

sys.stdout.write('{');
for i in xrange(MAX):
  terminator = ","
  if i == MAX-1:
    terminator = ""
  if i in values:
    sys.stdout.write(str(values[i])+terminator)
  else:
    sys.stdout.write("255"+terminator)
  
sys.stdout.write('}');
