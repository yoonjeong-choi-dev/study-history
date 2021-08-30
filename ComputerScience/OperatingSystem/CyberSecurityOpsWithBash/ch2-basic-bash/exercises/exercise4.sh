#!/bin/bash

VAR_NUM=$#
echo "there are $VAR_NUM arguments"


i=1
for ARG
do 
    echo "arg$i: $ARG"
    let i++
done