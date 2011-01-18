#!/usr/bin/python

import sys
import re

print """digraph interm_format_unrolled {
"""

for line in sys.stdin:
    s = line.rstrip('\r\n')
    if re.search("mips.dataflow", s):
            print re.sub(".*mips.dataflow: INFO: ", "", s), ";"

print """}"""


    
