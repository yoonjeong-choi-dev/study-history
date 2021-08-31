#!/bin/bash

if (( $# != 2))
then
    echo "[usage] <number1> <number2>"
    exit 100
fi

NUM1=$1
NUM2=$2

if (( NUM1 < NUM2 ))
then
    echo "$NUM1 < $NUM2"
else
    echo "$NUM1 > $NUM2"
fi