#!/bin/bash

echo "Hello World"

# 서브 셸을 이용하여 명령을 실행하고, 서브 셸의 결과를 첫 번째 명령을 이용
echo $(which neqn)
cat $(which neqn)