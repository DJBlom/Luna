#!/bin/bash

CMAKE=cmake
IMAGE_DIR=debug
BUILD_TYPE=DEBUG
BUILD_DIR=$(pwd)/build
TESTING_DIR=Testing
TOOLCHAIN=ProjectToolchain.cmake

rm -rf $BUILD_DIR/*
rm -rf $TESTING_DIR
mkdir $BUILD_DIR/$IMAGE_DIR
$CMAKE -S . -B $BUILD_DIR/$IMAGE_DIR --warn-uninitialized -DBUILD_LUNA=ON -DUSE_RTOS=ON -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN
$CMAKE --build $BUILD_DIR/$IMAGE_DIR
