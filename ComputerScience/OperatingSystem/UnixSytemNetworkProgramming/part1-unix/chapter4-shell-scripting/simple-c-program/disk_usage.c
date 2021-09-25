#include <stdio.h>
#include <string.h>

// 호출할 셸 스크립트 경로 설정
static const char *DISK_USAGE_SCRIPT_PATH = "./DiskUsage.sh";

// 셸 스크립트를 호출하여 결과를 반환
int get_disk_usage(char *dir_name)
{
  int result_val = 0;
  char cmd[256];
  char display[4] = "    ";

  // 셸 파일을 담당하는 파일 포인터
  FILE *fp;

  // 디스크 이름 널 체크
  if (dir_name == NULL)
  {
    fprintf(stderr, "\nget_disk_usage() Wrong dir_name!\n");
    return -1;
  }

  // 명령어 문자열 저장
  sprintf(cmd, "%s %s", DISK_USAGE_SCRIPT_PATH, dir_name);
  fprintf(stderr, "%s", cmd);
  // 명령어 문자열을 이용하여 파일 포인터 얻어 온다
  // 파이프를 이용하기 위해 popen 사용
  if ((fp = popen(cmd, "r")) == NULL)
  {
    fprintf(stderr, "\nget_disk_usage() Fail to open the pipe\n");
    return -1;
  }

  // 셸 프로그램 결과를 얻기 위해 cmd 앞 부분 초기화
  cmd[0] = 'F';
  cmd[1] = 'F';
  cmd[2] = 'F';
  cmd[3] = 'F';

  // 결과 저장
  fread(cmd, 1, 4, fp);

  // 결과 내용이 df이거나 FFFF 이면 셸 프로그램이 제대로 실행 되지 않은 것
  if (!strncmp("df", cmd, 2))
  {
    fprintf(stderr, "\nget_disk_usage() Shell Execution Error\n");
    return -1;
  }
  else if (!strncmp("FFFF", cmd, 4))
  {
    fprintf(stderr, "\nget_disk_usage() fread() Error\n");
    return -1;
  }

  // 에러가 없으면 결과 저장 후 정수로 변경
  strncpy(display, cmd, 4);
  result_val = atoi(display);

  return result_val;
}

// 디스크 사용량에 따른 심각도 및 조언 출력
void display_disk_usage(int level)
{
  if (level == -1)
  {
    printf("Something is wrong... Check error messages!\n");
  }
  else if (level > 90)
  {
    printf("디스크 사용량이 90%%를 넘었습니다.\n");
    printf("디스크를 추가하거나 필요없는 파일을 삭제하세요.\n");
  }
  else if (level > 70)
  {
    printf("디스크 사용량이 70%%를 넘었습니다.\n");
    printf("디스크 사용량에 유의하시기 바랍니다");
  }
  else if (level > 50)
  {
    printf("디스크 사용량이 50%%를 넘었습니다.\n");
    printf("아직 안심입니다");
  }
  else
  {
    printf("디스크 사용량이 50%%가 안됩니다.\n");
  }
}

int main(int argc, char **argv)
{
  int disk_usage_value;

  if (argc != 2)
  {
    fprintf(stderr, "\n\n\n Usage: disk_usage DiskName \n\n");
    return -1;
  }
  else
  {
    disk_usage_value = get_disk_usage(argv[1]);
    display_disk_usage(disk_usage_value);
  }
  return 0;
}