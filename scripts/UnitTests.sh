#!/bin/bash

cd test
pwd
make clean
make -s -f Makefile UnitTests
./UnitTests -c -v

