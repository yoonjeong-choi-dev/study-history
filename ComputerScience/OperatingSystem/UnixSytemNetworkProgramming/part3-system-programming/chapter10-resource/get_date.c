#include <stdio.h>
#include <time.h>

// 현재 시스템 날짜를 구하여 반환하는 함수
char* get_date()
{
    // 현재 시간을 구하기 위한 타이머 변수
    time_t cur_timer;

    // 타이머를 이용하여, 시스템 시간을 저장하는 구조체
    struct tm *local_time;

    static char date_str[10 + 1];

    cur_timer = time(NULL);
    local_time = localtime(&cur_timer);

    // 시간 데이터를 원하는 포멧으로 변환하여 문자열로 저장
    strftime(date_str, 10 + 1, "%Y%m%d", local_time);

    return date_str;
}

int main()
{
    printf("Current data : %s\n", get_date());
    return 0;
}