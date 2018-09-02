#!/usr/bin/python3
import os
import shutil
import sys

base = sys.argv[-2]
platform = sys.argv[-1]
outDir = os.path.join(base, "Output", "lib", platform, "include")
inDir = os.path.join(base, "Unknown 1.0++")

try:
    shutil.rmtree(outDir)
except:
    pass

try:
    os.makedirs(outDir)
except:
    pass

for base, dirs, files in os.walk(inDir):
    for file in files:
        file = os.path.join(base, file)
        if ".h" in file:
            outFile = os.path.relpath(file, inDir)
            outFile = os.path.join(outDir, outFile)

            outFileDir = os.path.dirname(outFile)

            if not os.path.exists(outFileDir):
                try:
                    os.makedirs(outFileDir)
                except:
                    pass

            shutil.copy(file, outFile)
