#!/bin/bash
mkdir build/
cd build/
cmake ../src -G Ninja
ninja
./ASCII-Engine