#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// 실행시킬 스크립트 경로
static const char* CHECK_SCRIPT = "./check-only-one.sh";

// 스크립트 실행 함수
void run_check_one_script(char *args, char result[8])
{
    char cmd[32];
    FILE* fp;
    int i;

    sprintf(cmd, "%s %s", CHECK_SCRIPT, args);
    
    if ((fp = popen(cmd, "r")) == NULL)
    {
        fprintf(stderr, "\nrun_check_one_script() : Fail to open the pipe\n");
        strncpy(result, "NULLRES\0", 8);
        return;
    }
    
    // 결과를 얻어 올 버퍼 초기화
    for(i=0;i<4;i++)
        cmd[i] = 'F';

    // 스크립트 실행 결과 복사
    fread(cmd, 1, 7, fp);
    if(!strncmp("FFFF", cmd, 4)){
        pclose(fp);
        fprintf(stderr, "\nrun_check_one_script() : fread() failed\n");
        strncpy(result, "NULLRES\0", 8);
        return;
    }

    // 최종 결과
    strncpy(result, cmd, 8);
    pclose(fp);
}


int main(int argc, char** argv)
{
    // 인수 체크
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s [start | stop]\n", argv[0]);
        return 0;
    }
    else if(strncmp("start", argv[1], 5) && strncmp("stop", argv[1], 4))
    {
        fprintf(stderr, "usage: %s [start | stop]\n", argv[0]);
        return 0;
    }

    char result[8];
    run_check_one_script(argv[1], result);
    // 스크립트에서 반환한 에러 체크
    if(!strncmp("NOTROOT", result, 7))
    {
        fprintf(stderr, "You must be root\n");
    }
    // ALREADY
    else if(!strncmp("ALREADY", result, 7))
    {
        fprintf(stderr, "The process is already running\n");
    }
    // RUNNING
    else if(!strncmp("RUNNING", result, 7))
    {
        fprintf(stderr, "Success to run the process\n");
    }
    // STOPONE
    else if(!strncmp("STOPONE", result, 7))
    {
        fprintf(stderr, "Success to stop the process\n");
    }
    // ANYONEP
    else if(!strncmp("ANYONEP", result, 7))
    {
        fprintf(stderr, "The process is not running\n");
    }
    // NULL
    else if(!strncmp("NULL", result, 4))
    {
        fprintf(stderr, "Please check the shell script : %s\n", CHECK_SCRIPT);
    }

    return 0;
}