#!/bin/bash

MAIN_FILE=$(pwd)/source/main.cpp
SOURCE_DIR=$(pwd)/source/src
RM_SYSTEM_SOURCE_DIR=$(pwd)/rmSystem/src
DRIVERS_SOURCE_DIR=$(pwd)/drivers/src

if cppcheck --enable=all --std=c++20 --error-exitcode=1 --platform=mips32 --suppress=missingInclude $RM_SYSTEM_SOURCE_DIR $DRIVERS_SOURCE_DIR $SOURCE_DIR $MAIN_FILE;
then
    echo -e "\e[32mNo Issues Found \e[0m";
    exit 0;
else
    echo -e "\e[31mSome Issues Found \e[0m";
    exit 1;
fi
