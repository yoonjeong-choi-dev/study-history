#!/bin/bash

GOOS=js GOARCH=wasm go build -o go-to-wasm.wasm web-assembly.go

echo "Check the .wasm file!"
file go-to-wasm.wasm