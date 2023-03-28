#!/bin/bash

SOURCE_DIR=$(pwd)/source/

if cppcheck --enable=all --std=c++20 --error-exitcode=1 --platform=mips32 --suppress=missingInclude $SOURCE_DIR;
then
    echo "No Issues Found";
    exit 0;
else
    echo "Some Issues Found";
    exit 1;
fi
