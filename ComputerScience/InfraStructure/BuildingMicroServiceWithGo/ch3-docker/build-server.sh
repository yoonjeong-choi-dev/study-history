#!/bin/bash

CGO_ENABLED=0 GOOS=linux COARCH=386 go build -a -installsuffix cgo -ldflags '-s' -o server