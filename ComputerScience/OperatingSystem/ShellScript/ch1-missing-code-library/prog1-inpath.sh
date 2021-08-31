#!/bin/bash

# 특정 프로그램이 유효한지 판별하는 프로그램
# 주어진 프로그램이 시스템 PATH에 정의되어 있는지 테스트

in_path()
{
  # 주어진 명렬어와 PATH에서 해당 명령어를 탐색
  # 발견된 경우(실행 가능) 0 반환
  # 발견되지 않은 경우(실행 불가능) 1 반환
  cmd=$1  ourpath=$2  result=1

  # IFS(구분자)를 일시적으로 수정 : PATH 환경변수는 :를 구분자로 사용
  oldIFS=$IFS IFS=":"

  for directory in $ourpath
   do
     if [ -x $directory/$cmd ] ; then
       result=0
     fi
   done



  IFS=$oldIFS
  return $result
}


checkForCmdInPath()
{
  # 인자로 받은 프로그램 이름
  var=$1

  # 프로그램 이름이 공백이 아닌 경우에만 실행
  if [ "$var" != "" ] ; then
    # 프로그램 이름이 /로 시작하는 경우
    if [ "${var:0:1}" = "/" ] ; then
      # -x : 해당 프로그램이 존재하고 실행 가능한 경우 => 정상 프로그램!
      if [ ! -x $var ] ; then
        return 1
      fi
    # 프로그램 이름이 절대 경로가 아닌 경우, PATH 환경 변수 참조
    elif ! in_path $var "$PATH" ; then
      return 2
    fi
  fi
}

# 인자로 프로그램 이름을 받아야 한다
if [ $# -ne 1 ] ; then
  echo "Usage: $0 command" >&2
  exit 1
fi

# 인자로 받은 검사할 프로그램 이름으로 수행
checkForCmdInPath "$1"

# 결과에 대한 출력
case $? in
  0) echo "$1 found in PATH";;
  1) echo "$1 not found or not executable";;
  2) echo "$1 not found in PATH";;
esac

exit 0