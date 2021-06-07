#!/bin/bash

# 매개변수로는 파일 이름들을 받아온다
for filename; do
    # 해당 파일이 존재하는 경우에만 검색
    if [[ -r $1 ]]; then
        max_word=
        max_len=0

        # 파일의 내용 검색
        for word in $(strings $1); do
            # 단어 길이 계산 및 비교
            len=$(echo $word | wc -c)

            if (( len > max_len )); then
                max_len=$len
                max_word=$word
            fi
        done

        # 결과 출력
        echo "$filename: '$max_word' ($max_len characters)"
    fi
done