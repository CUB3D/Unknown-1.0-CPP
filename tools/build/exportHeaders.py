#!/usr/bin/python3
import os
import shutil
import pathlib
import sys

base = sys.argv[-1]
outDir = os.path.join(base, "./Output/lib/linux/include/")
inDir = os.path.join(base, "./Unknown 1.0++/")

pathlib.Path(outDir).mkdir(parents=True, exist_ok=True)
shutil.rmtree(outDir)

for base, dirs, files in os.walk(inDir):
    for file in files:
        file = os.path.join(base, file)
        if ".h" in file:
            outFile = os.path.join(outDir, file.replace(inDir, ""))
            outFileDir = "/".join(outFile.split("/")[:-1])
            if not os.path.exists(outFileDir):
                os.mkdir(outFileDir)
            shutil.copy(file, outFile)
