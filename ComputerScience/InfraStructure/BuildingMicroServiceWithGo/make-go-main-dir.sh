#!/bin/bash

dir_name=$1

mkdir ${dir_name}
touch ${dir_name}/${dir_name}.go
echo "package main" >> ${dir_name}/${dir_name}.go