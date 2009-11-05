#!/bin/sh
if (CC -V  > /dev/null 2>&1)
    then COMPILER="CC"
elif (CC -version > /dev/null 2>&1)
    then COMPILER="CC"
elif (g++3 -v > /dev/null 2>&1)
    then COMPILER="g++3"
elif (g++ -v > /dev/null 2>&1)
    then COMPILER="g++";
else COMPILER="NO_COMPILER_FOUND"
fi
echo $COMPILER