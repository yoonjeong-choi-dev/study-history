#!/bin/bash

file_name=$1
if [[ $file_name == *".java" ]]; then
    file_name=`basename $file_name .java`

else
    file_name=`basename $file_name`
fi

javac "$file_name".java
java "$file_name"
rm "$file_name".class