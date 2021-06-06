#!/bin/bash


# Program to output a system information page
TITLE="System Information Report For $HOSTNAME"
CURRENT_TIME=$(date +"%x %r %Z")
TIME_STAMP="Generated $CURRENT_TIME, by $USER"

# function 
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

report_home_space(){
    # 슈퍼 유저인 경우(i.e 홈 디렉토리에 대한 읽기 권한이 있는 경우) : 모든 유저 정보 출력
    # 테스트 방법 : sudo ./system_info_page.sh > system_info_page.html 로 html 생성 후 브라우저로 연결
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