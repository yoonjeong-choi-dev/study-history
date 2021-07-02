#!/bin/bash

echo "==========================="
echo "각 데이터 구조체에 대한 GC 성능측정!"
echo "메모리 공간을 많이 사용 할수록 GC 호출이 많아진다."
echo "==========================="

echo "슬라이스"
time go run slice-example/slice-example.go

echo "포인터를 저장한 맵"
time go run map-with-pointer/map-with-pointer.go

echo "값을 저장한 맵"
time go run map-without-pointer/map-without-pointer.go

echo "맵을 저장한 맵"
time go run map-in-map/map-in-map.go