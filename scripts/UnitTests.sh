#!/bin/bash

echo $CPPUTEST_HOME
cd test
make clean
make -s -f Makefile UnitTests
./UnitTests -c -v

