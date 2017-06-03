import os
import shutil

outDir = "../Output/lib/linux/include/"
inDir = "../Unknown 1.0++/"

for base, dirs, files in os.walk(inDir):
    for file in files:
        file = os.path.join(base, file)
        if ".h" in file:
            outFile = os.path.join(outDir, file.replace(inDir, ""))
            outFileDir = "/".join(outFile.split("/")[:-1])
            if not os.path.exists(outFileDir):
                os.mkdir(outFileDir)
            shutil.copy(file, outFile)