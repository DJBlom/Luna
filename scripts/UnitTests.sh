#!/bin/bash

cd test
make clean
make -s -f Makefile UnitTests
./UnitTests -c -v

