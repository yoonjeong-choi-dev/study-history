#include <stdio.h>
#include <string.h>

// DB에서 가져온 프로세서 정보 데이터 정의
typedef struct
{
  char proc_name[8];
  char proc_desc[64];
  char proc_alive[2];
  char proc_start_time[32];
  char proc_stop_time[32];
} PROC_LIST_T;
PROC_LIST_T proc_list;

// DB에서 가져온 에러 정보 데이터 정의
typedef struct
{
  char error_date_time[32];
  char error_cause[32];
  int  error_level;
  char error_mis[64];       // 에러가 발생한 지역을 유추할 정보
  char error_process_name[2];
  char error_code[8];
} ERROR_LIST_T;
ERROR_LIST_T error_list;

// DB를 조회하여, 구조체에 정보를 가공하여 저장하는 함수들(예제)
int get_process_info()
{
  printf("get_process_info() executed! \n");

  strcpy(proc_list.proc_name, "proc-name");
  strcpy(proc_list.proc_desc, "proc-description");
  strcpy(proc_list.proc_alive, "proc-alive");
  strcpy(proc_list.proc_start_time, "proc-start-time");
  strcpy(proc_list.proc_stop_time, "proc-stop-time"); 
  
  printf("End inquiring data from the process table ! \n");
  return 1;
}

int get_error_info()
{
  printf("get_error_info() executed! \n");

  strcpy(error_list.error_date_time, "date-time");
  strcpy(error_list.error_cause, "error-cause");
  error_list.error_level = 1;
  strcpy(error_list.error_mis, "error-mis");
  strcpy(error_list.error_process_name, "ko");
  strcpy(error_list.error_code, "code");

  printf("End inquiring data from the error table ! \n");
  return 1;
}

// DB 쿼리 관련 함수들에 대한 enum 및 대행 함수 정의
#define MAX_FUNC_NUM 2
#define DBFUNC(command, func) dbFuncMember[(command)]=(func)

int (*dbFuncMember[MAX_FUNC_NUM]) ();   // 함수 포인터 배열

enum db_func {
  GET_PROCESS_INFO,
  GET_ERROR_INFO
};

void db_func_init()
{
  int i;
  for (i=0;i<MAX_FUNC_NUM;i++)
    dbFuncMember[i] = NULL;

  DBFUNC(GET_PROCESS_INFO, get_process_info);
  DBFUNC(GET_ERROR_INFO, get_error_info);
}

int run_db_func(db_func) 
{
  int ret;

  printf("\nDB와 연결을 설정합니다\n");

  ret = (*dbFuncMember[db_func])();

  printf("\nDB와 연결을 해제합니다\n\n");
  return ret;
}

int main()
{
  db_func_init();
  run_db_func(GET_PROCESS_INFO);
  run_db_func(GET_ERROR_INFO);

  return 1;
}