#!/bin/bash

i=1
target=2
for ARG
do 
    if ((i==target))
    then
        echo "arg$i: $ARG"
        let target=target+2
    fi
    let i++
done