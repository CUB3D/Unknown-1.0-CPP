#!/usr/bin/python3

import sys
import os
import locale
from dialog import Dialog

locale.setlocale(locale.LC_ALL, '')

d = Dialog(dialog="dialog")

d.gauge_start("Installing stuff", percent=0)

file = open(sys.argv[1], "r")
command = sys.argv[2]
mode = sys.argv[3]

percent = 0.0

lines = []

for line in file:
    lines.append(line.rstrip("\n"))


if mode == "compound" or mode == "c":
    fullCommand = command + " " + (" ".join(lines))
    os.system(fullCommand + " > /dev/null 2>&1")
    d.gauge_update(100)
elif mode == "individual" or mode == "i":
    done = 0
    for line in lines:
        os.system(command + " " + line + " > /dev/null 2>&1")
        done += 1
        percent = done / len(lines) * 100
        d.gauge_update(int(percent))
