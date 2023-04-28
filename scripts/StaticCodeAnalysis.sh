#!/bin/bash

MAIN_FILE=$(pwd)/source/main.cpp
FEATURES_SOURCE_DIR=$(pwd)/source/features/src
CORE_SYSTEM_SOURCE_DIR=$(pwd)/source/coreSystem/src
DRIVERS_SOURCE_DIR=$(pwd)/drivers/src

if cppcheck --enable=all --std=c++20 --error-exitcode=1 --platform=mips32 --suppress=missingInclude $CORE_SYSTEM_SOURCE_DIR $DRIVERS_SOURCE_DIR $FEATURES_SOURCE_DIR $MAIN_FILE;
then
    echo -e "\e[32mNo Issues Found \e[0m";
    exit 0;
else
    echo -e "\e[31mSome Issues Found \e[0m";
    exit 1;
fi
