import os
import shutil
import json

input("Please confirm that the release build is up to date")

projectDir = "Unknown Test"

exeFilePath = ""
projectOutput = ""
libraryDependencies = []
resources = []
is32Bit = False

with open(os.path.join(projectDir, "publish.json")) as handle:
    json = json.load(handle)
    #TODO: Get current os
    currentOSPublishConf = json["WIN"]
    exeFilePath = currentOSPublishConf["MainBinary"]
    projectOutput = currentOSPublishConf["ProjectOutput"]
    libraryDependencies = currentOSPublishConf["Libs"]
    resources = currentOSPublishConf["Resources"]

with open(exeFilePath, "rb") as handle:
    while True:
        byte = handle.read(1)
        if byte == b'':
            break
        if byte == b'P':
            if handle.read(1) == b'E':
                if handle.read(1) == b'\0':
                    if handle.read(1) == b'\0':
                        if handle.read(1) == b'L':
                            print("32 bit binary detected")
                            is32Bit = True
if not is32Bit:
    print("64 bit binary detected")

if not os.path.exists(projectOutput):
    os.mkdir(projectOutput)

print(":Copying libs")
for lib in libraryDependencies:
    inputPath = lib.replace("$arch$", "x86" if is32Bit else "x64")
    print("-" + inputPath)
    shutil.copy(inputPath, projectOutput)
print(":Copying binary")
shutil.copy(exeFilePath, projectOutput)
print(":Copying resources")
for resource in resources:
    inputPath = os.path.join(projectDir, resource)
    print("-" + inputPath)
    shutil.copy(inputPath, projectOutput)
