#!/bin/bash

mkdir "$(echo $UNKNOWN_PROJECT_ROOT)/Libs/RapidJSON"

ln -s "$(echo $UNKNOWN_PROJECT_ROOT)/tools/libs/third_party/rapidJSON/include" "$(echo $UNKNOWN_PROJECT_ROOT)/Libs/RapidJSON/include"

sudo "$(echo $UNKNOWN_PROJECT_ROOT)/tools/setup/runAgainstFile.py" "$(echo $UNKNOWN_PROJECT_ROOT)/tools/setup/requiredPackages.list" "sudo apt -y install" i
