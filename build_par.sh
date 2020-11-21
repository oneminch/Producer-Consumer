#!/bin/bash

g++ -I./ -I./CSC1310/include -c Song.cpp
g++ -I./ -I./CSC1310/include -c CD.cpp
g++ -I./ -I./random/include -I./CSC1310/include -c Parallel.cpp
g++ -L./ -L./random/lib -L./CSC1310/lib -o Parallel.exe Parallel.o Song.o CD.o -lrandom -lCSC1310 -pthread
./Parallel.exe
