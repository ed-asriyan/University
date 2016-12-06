#!/usr/bin/env bash

cmake CMakelists.txt
make

echo
echo

for ((k=0;k<10;k+=2))
do
    i=$(bc <<<"scale=2; $k / 100" )
    ./Matrix $i
done

for ((k=10;k<40;k+=5))
do
    i=$(bc <<<"scale=2; $k / 100" )
    ./Matrix $i
done

rm Matrix
rm CMakeCache.txt
rm cmake_install.cmake
rm -rf CMakeFiles/
