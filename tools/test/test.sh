#!/bin/bash

export LD_LIBRARY_PATH="$(echo $UNKNOWN_PROJECT_ROOT)/Output/lib/linux/."
cd "Unknown Test"
./a.out
cd ..
