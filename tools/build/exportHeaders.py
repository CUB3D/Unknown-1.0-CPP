#!/usr/bin/python3
import os
import shutil
import pathlib
import sys

base = sys.argv[-1]
outDir = os.path.join(base, "Output", "lib", "linux", "include")
inDir = os.path.join(base, "Unknown 1.0++")

try:
	shutil.rmtree(outDir)
except:
	pass

try:
    os.makedirs(outDir, exist_ok=True)
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
			    os.makedirs(outFileDir, exist_ok=True)
			shutil.copy(file, outFile)
