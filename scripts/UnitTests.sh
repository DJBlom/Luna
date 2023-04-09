#!/bin/bash

cd test
ls -la
make clean
make -s -f Makefile UnitTests
./UnitTests -c -v

