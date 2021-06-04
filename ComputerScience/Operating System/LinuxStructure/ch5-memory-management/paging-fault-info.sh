#!/bin/bash

# 가상 메모리양, 확보된 물리 페이지 양, 페이지 폴트 횟수 확인 스크립트

while true; do
    DATE=$(date | tr -d '\n')
    INFO=$(ps -eo pid,comm,vsz,rss,maj_flt,min_flt | grep demand-paging | grep -v grep)

    if [ -z "$INFO" ]; then
        echo "$DATE: target process seems to be finished"
        break
    fi

    echo "${DATE}: ${INFO}"
    sleep 1
done
