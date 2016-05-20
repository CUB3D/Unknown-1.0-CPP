#!/usr/bin/python3.4
# a project to make the compilation of code simpler

import os
import sys

verboseOutput = False

if "-v" in sys.argv:
    verboseOutput = True

projects = [x for x in sys.argv[1:] if not x.startswith("-")]

if verboseOutput:
    print("Compiling ", " ".join(projects))

# find the cbuild.cb file
cbuild = open("cbuild-" + projects[0] + ".cb")

lines = []

for a in cbuild:
    lines.append(a)

lineNumber = 0

def findAllDirectories(filter, startdir):
    dirs = []
    for dirPath, subs, files in os.walk(startdir):
        for file in files:
            if verboseOutput:
                print("Checking file", file)
            if filter.split(">")[0] == "(ending)":
                if file.endswith(filter.split(">")[1].replace("\n", "")):
                    dirs.append(os.path.join(dirPath, file))
            if filter == "*":
                dirs.append(os.path.join(dirPath, file))
    print("Found", dirs)
    return dirs

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
            print("[EXEC]", commandNew)
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
        print("[EXEC]", programName)
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
        temp = ""
        for x in sourceFiles:
            temp += '"' + x + '" '
        os.system(replace_vars(variables["$compile"]) + " " + temp)
    if data[0] == "log":
        print("[INFO]", " ".join(data[1:]))
    if data[0] == "rpl":
        os.system("tools/build/rpl.py " + " ".join(data[1:]))
