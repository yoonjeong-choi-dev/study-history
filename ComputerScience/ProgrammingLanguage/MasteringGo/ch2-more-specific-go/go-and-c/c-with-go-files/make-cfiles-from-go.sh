#!/bin/bash

go build -o my-go-lib.o -buildmode=c-shared my-go-lib.go

echo "Check Object file"
file my-go-lib.o