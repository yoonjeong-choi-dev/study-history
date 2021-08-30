#!/bin/bash

testfile="../system-info-page/system_info_page.sh"
echo "test file : $testfile"

echo "original file using 'strings' to calculate the length of a word"
time ./find-longest-word.sh $testfile

echo "improved file using '\${#'word'} to calculate the length of a word"
time ./find-longest-word-improved.sh $testfile