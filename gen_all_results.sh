#!/usr/bin/env bash

dirlist=$(find $1 -mindepth 1 -maxdepth 1 -type d)
root=$(pwd)
for dir in $dirlist
do
    if [[ "$dir" =~ ^./llvm.* ]]; then
        printf "$dir\n"
        cd $dir
        make all
        cd $root
    fi
done
