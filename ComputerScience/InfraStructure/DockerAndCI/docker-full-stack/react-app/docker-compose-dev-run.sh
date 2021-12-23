#!/bin/bash

mode=""
if [ $# -eq 0 ]
then
    mode="start"
else
    mode=$1
fi

echo $mode

if [ $mode == "start" ]
then
    docker-compose -f docker-compose-dev.yaml up --build
elif [ $mode == "stop" ]
then
    docker-compose -f docker-compose-dev.yaml down
else 
    echo "mode must be either 'start' or 'stop'"
    exit 1
fi

exit 0