#!/bin/bash


cd go-with-cfile-workspace
gcc -c myCLib/*.c
ar rs callC.a *.o
rm callC.o