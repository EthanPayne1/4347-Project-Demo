#!/bin/bash

BUILD_TYPE="Run"

#if [[ "build" ]]; then
#  mkdir build
#fi
mkdir build
cd build
cmake ..

make  
