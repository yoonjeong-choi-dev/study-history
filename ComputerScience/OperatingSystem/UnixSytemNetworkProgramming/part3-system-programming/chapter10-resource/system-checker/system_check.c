#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// 프로그램에서 사용할 스크립트 파일 선언
static const char* DISK_USAGE_PATH = "./disk-usage.sh";
static const char* CPU_LOAD_PATH = "./cpu-load.sh";
static const char* MEM_LOAD_PATH = "./mem-load.sh";
static const char* NET_INFO_PATH = "./net-info.sh";

typedef enum _ScriptResult {
    SUCCESS,
    FAIL
}ScriptResult;

// 스크립트를 실행하고 결과를 저장하는 함수
ScriptResult run_script(char* cmd, int result_size, char* func_name)
{
    ScriptResult result = SUCCESS;

    // 셸 파일을 담당하는 파일 포인터
    FILE *fp;

    // 스크립트 실행
    if ((fp = popen(cmd, "r")) == NULL)
    {   
        pclose(fp);
        fprintf(stderr, "\n%s: Fail to open the pipe\n", func_name);
        return result = FAIL;
    }

    // 실행 결과를 저장하기 위해 문자열 초기화 : 결과 저장 시 오류 확인 용
    fread(cmd, 1, result_size, fp);
    if (!strncmp("FFFF", cmd, 4))
    {
        pclose(fp);
        fprintf(stderr, "\n%s: fread failed\n", func_name);
        return result = FAIL;
    }

    // 실행 결과가 비어 있는 경우 : 스크립트 실행 실패
    if (cmd[0] == 10){
        pclose(fp);
        fprintf(stderr, "   - %s: Error occurs in the script\n", func_name);
        return result = FAIL;
    }

    pclose(fp);
    return result;
}

// disk-usage 프로그램을 호출
void get_disk_usage(char *disk_path)
{
    int disk_usage = 0;
    char cmd[256];
    char display[4] = "    ";

    // 실행할 명령어를 문자열에 저장 및 실행
    sprintf(cmd, "%s %s", DISK_USAGE_PATH, disk_path);
    ScriptResult result = run_script(cmd, 4, "get_disk_usage");
    if (result == FAIL)
        return;

    // 실행 결과를 숫자로 변경
    strncpy(display, cmd, 4);
    disk_usage = atoi(display);
    printf("Disk Usage(%s) : %d(%%) \n", disk_path, disk_usage);
}

// cpu-load 프로그램 호출
void get_cpu_load()
{
    int cpu_idle = 0;
    char cmd[256];
    char display[4] = "    ";

    // 실행할 명령어를 문자열에 저장 및 실행
    sprintf(cmd, "%s", CPU_LOAD_PATH);
    ScriptResult result = run_script(cmd, 4, "get_cpu_load");
    if (result == FAIL)
        return;

    // 실행 결과를 숫자로 변경
    strncpy(display, cmd, 4);
    cpu_idle = atoi(display);
    printf("CPU IDLE : %d(%%)\n", cpu_idle);
}

// mem-load 프로그램 호출
void get_memory_load()
{
    int memory_usage = 0;
    float total_size, usage_size;
    char cmd[256];
    char display[20];

    // 실행할 명령어를 문자열에 저장 및 실행
    sprintf(cmd, "%s", MEM_LOAD_PATH);
    ScriptResult result = run_script(cmd, 256, "get_memory_load");
    if (result == FAIL)
        return;

    // 실행 결과를 숫자로 변경
    strncpy(display, cmd, 20);
    total_size = atof(strtok(display, " Mm\n"));
    usage_size = atof(strtok(NULL, " Mm\n"));
    memory_usage = (int)(usage_size*100 / total_size);

    printf("Memory usage : %d(%%)\n", memory_usage);
}

// net-info 프로그램 호출
void get_network_info()
{
    char cmd[256];
    char display[256], *cur_info;

    // 실행할 명령어를 문자열에 저장 및 실행
    sprintf(cmd, "%s", NET_INFO_PATH);
    ScriptResult result = run_script(cmd, 256, "get_network_info");
    if (result == FAIL)
        return;

    // 실행 결과 출력
    strncpy(display, cmd, 256);
    printf("Network information :\n");
    cur_info = strtok(display, "{}");
    while(cur_info != NULL)
    {
        printf("\t%s\n", cur_info);
        cur_info = strtok(NULL, "{}");
    }
}

int main()
{
    get_disk_usage("/");
    // get_disk_usage("/sdsfafd");
    get_cpu_load();
    get_memory_load();
    get_network_info();

    return 0;
}