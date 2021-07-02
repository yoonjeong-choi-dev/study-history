#!/bin/bash

# GC는 병렬 실행 => 출력문과 섞여서 출력할 가능성 있음
# GODEBUG=gctrace=1 를 통해 진행되는 동안 할당된 힙의 크기 추적 가능
GODEBUG=gctrace=1 go run gc-info.go