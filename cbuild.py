# a project to make the compilation of code simpler

import os
import re

# find the cbuild.cb file
cbuild = open("cbuild.cb")


def findAllDirectories(filter, startdir):
    dirs = []
    for dirPath, subs, files in os.walk(startdir):
        for file in files:
            print("Checking file", file)
            if filter.split(">")[0] == "(ending)":
                if file.endswith(filter.split(">")[1].replace("\n", "")):
                    dirs.append(os.path.join(dirPath, file))
            if filter == "*":
                dirs.append(os.path.join(dirPath, file))
    print("Found", dirs)
    return dirs


lines = []

for a in cbuild:
    lines.append(a)

lineNumber = 0


def strip_string(string):
    return string.replace("\n", "")

variables = {}

def replace_vars(string):
    ret = string
    for substring in string.split(" "):
        if substring in variables:
            ret = ret.replace(substring, variables[substring])
    return strip_string(ret)


def exec_forall():
    global lineNumber
    while True:
        lineNumber += 1
        command = replace_vars(lines[lineNumber])
        if command == "endfor":
            return
        for file in dirs:
            commandNew = command.replace("$name", file).replace("$fileName", "".join(file.split("/")[-1:]))
            print(commandNew)
            os.system(commandNew)

while lineNumber < len(lines):
    data = lines[lineNumber].split(" ")
    if data[0] == "forall":
        startDir = "."
        if len(data) >= 3 and data[2] == "in":
            startDir = data[3].replace("\n", "")
        dirs = findAllDirectories(data[1], replace_vars(startDir))
        exec_forall()

    if data[0] == "mkdir":
        dirName = strip_string(data[1])
        os.makedirs(dirName)
    lineNumber += 1

    if data[0] == "run":
        programName = strip_string(" ".join(data[1:]))
        print("Running", programName)
        os.system(programName)
    if data[0].startswith("$"):
        variableName = data[0]
        variableValue = " ".join(data[2:])
        variables[variableName] = variableValue
    if data[0] == "compileAll":
        startDir = "."
        if len(data) >= 3 and data[2] == "in":
            startDir = data[3].replace("\n", "")
        sourceFiles = findAllDirectories(data[1], replace_vars(startDir))
        print(" ".join(sourceFiles))
        temp = ""
        for x in sourceFiles:
            temp += '"' + x + '" '
        os.system(replace_vars(variables["$compile"]) + " " + temp)
