#!/bin/bash


# Program to output a system information page
PROGNAME=$(basename $0)
TITLE="System Information Report For $HOSTNAME"
CURRENT_TIME=$(date +"%x %r %Z")
TIME_STAMP="Generated $CURRENT_TIME, by $USER"

# Functions for basic usage
usage() {
    echo "=============================================="
    echo "$PROGNAME" : usage: $PROGNAME [-f file | -i]
    echo "-f(--filename) file : output file name"
    echo "-i(--interactive) : interactive mode"
    echo "==============================================\n"

    return
}

# Functions for system information
report_uptime (){
cat << _EOF_
    <H2>System Uptime</H2>
    <PRE>$(uptime)</PRE>
_EOF_

    return    
}

report_disk_space(){
cat << _EOF_
    <H2>Disc Space Utilization</H2>
    <PRE>$(df -h)</PRE>
_EOF_

    return
}

report_home_space_legacy(){
    #슈퍼 유저인 경우(i.e 홈 디렉토리에 대한 읽기 권한이 있는 경우) : 모든 유저 정보 출력
    #테스트 방법 : sudo ./system_info_page.sh > system_info_page.html 로 html 생성 후 브라우저로 연결
    if [[ $(id -u) -eq 0 ]]; then
cat << _EOF_
    <H2>Home Space Utilization(All Users)</H2>
    <PRE>$(du -sh /home/*)</PRE>
_EOF_
    # 슈퍼 유저가 아닌 경우(i.e 홈 디렉토리에 대한 읽기 권한이 없는 경우) : 현재 유저 정보($HOME) 출력
    else
cat << _EOF_
    <H2>Home Space Utilization ($USER)</H2>
    <PRE>$(du -sh $HOME)</PRE>
_EOF_
    fi

return
}

report_home_space(){
    # 지역 변수 설정
    local format="%8s%10s%10s\n"
    local dir dir_list total_files total_dirs total_size user_name

    # 슈퍼 유저와 일반 유저에 대한 디렉토리 및 유저 이름 설정
    if [[ $(id -u) -eq 0 ]]; then
        dir_list=/home/*
        user_name="All Users"
    else
        dir_list=$HOME
        user_name=$USER
    fi

    # 기본 정보 출력
    echo "<H2>Home Space Utilization ($user_name)</H2>"

    # 하위 디렉토리의 정보
    for dir in $dir_list; do
        # 하위 디렉토리의 파일 개수
        total_files=$(find $dir -type f | wc -l)
        # 하위 디렉토리의 폴더 개수
        total_dirs=$(find $dir -type d | wc -l)
        # 하위 디렉토리의 크기
        total_size=$(du -sh $dir | cut -f 1)

        # 정보 출력
        echo "<H3>$dir</H3>"
        echo "<PRE>"
            printf "$format" "Dirs" "Files" "Size"
            printf "$format" "----" "-----" "----"
            printf "$format" $total_dirs $total_files $total_size
        echo "</PRE>"
    done

    return
}

# Write HTML page
write_html_page(){
    cat << _EOF_
<HTML>
    <HEAD>
        <TITLE>$TITLE</TITLE>
    </HEAD>
    <BODY>
        <H1>$TITLE</H1>
        <p>$TIME_STAMP</p>
        $(report_uptime)
        $(report_disk_space)
        $(report_home_space)
    </BODY>
</HTML>
_EOF_
    return
}


# Process Command Line Options
interactive=
filename=

# Process Main Loop for parameters : 매개변수를 순차적으로 탐색
while [[ -n $1 ]]; do
    case $1 in
        -f | --file)        shift
                            filename=$1
                            ;;
        -i | --interactive) interactive=1
                            ;;
        -h | --help)        usage
                            exit 
                            ;;
        *)                  usage >&2
                            exit 1
                            ;;                            
    esac
    shift
done


# interactive mode
if [[ -n $interactive ]]; then
    while true; do
        read -p "Enter name of output file : " filename

        # 파일이 존재하는 경우 : 덮어쓰기 확인
        if [[ -e $filename ]]; then
            read -p "'$filename' exits. Overwrite? [y/n/q] > "
            case $REPLY in
                Y|y)    break;
                        ;;
                Q|q)    echo "Program Terminated."
                        exit
                        ;;
                *)    continue;
                        ;;
            esac
        # 빈 파일 이름인 경우 다시 입력
        elif [[ -z $filename ]]; then
            echo "Please write valid filename."
            continue
        else
            break;
        fi
    done
fi


# print out the result
if [[ -n $filename ]]; then 
    if touch $filename && [[ -f $filename ]]; then
        write_html_page > $filename
    else
        echo "$PROGNAME: cannot write file '$filename'" >&2
        exit 1
    fi
else
    write_html_page
fi