#!/bin/bash

rm -f testfile

echo "$(date): start write (file creation)"
dd if=/dev/zero of=testfile oflag=direct bs=1M count=1K
echo "$(date): end write"

echo "Before access"
free

echo "First access"
time cat testfile > /dev/null
free

echo "Second access"
time cat testfile > /dev/null
free


rm -f testfile