#!/bin/bash

EXERCISE_NUM=$1
CUR_PATH=$2/exercises


mkdir $CUR_PATH

i=1
while ((i<EXERCISE_NUM+1))
do
    touch $CUR_PATH/"exercise$i.sh"
    let i++
done