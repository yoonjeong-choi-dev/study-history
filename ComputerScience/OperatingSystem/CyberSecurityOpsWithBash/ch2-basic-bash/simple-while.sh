#!/bin/bash

if (( $# != 1))
then
    echo "[usage] <num of loop>"
    exit 100
fi

LOOP_NUM=$1

i=0
while ((i<LOOP_NUM))
do
    echo "$i-th loop"
    let i++
done