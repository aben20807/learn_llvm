#!/usr/bin/env bash

dirlist=$(find $1 -mindepth 1 -maxdepth 1 -type d)
root=$(pwd)

# color: https://stackoverflow.com/questions/4332478/read-the-current-text-color-in-a-xterm/4332530#4332530
BLUE=$(tput setaf 153)
GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
NORMAL=$(tput sgr0)

for dir in $dirlist
do
    if [[ "$dir" =~ ^./llvm.* ]]; then
        printf "${BLUE}\n--- $dir ---\n${NORMAL}"
        cd $dir
        make all VERBOSE=0 2>&1 1>/dev/null
        if [ $? -ne 0 ]; then
            printf "${RED}error occurred!\n${NORMAL}"
            make all VERBOSE=1
        else
            printf "${GREEN}passed!\n${NORMAL}"
        fi
        cd $root
    fi
done
