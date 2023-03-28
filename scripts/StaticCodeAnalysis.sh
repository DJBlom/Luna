#!/bin/bash

MAIN_FILE=$(pwd)/source/main.c
SOURCE_DIR=$(pwd)/source/src

if cppcheck --enable=all --std=c++20 --error-exitcode=1 --platform=mips32 --suppress=missingInclude $SOURCE_DIR $MAIN_FILE;
then
    echo "No Issues Found";
    exit 0;
else
    echo "Some Issues Found";
    exit 1;
fi
