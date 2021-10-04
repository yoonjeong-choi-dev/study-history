#include <stdio.h>

#include <sys/stat.h>
#include <fcntl.h>


int main()
{
    // 생성할 파일 이름 및 접근 권한 설정
    char* file_name = "./create_test.txt";
    int access_mode = 0777;

    // 파일 생성 : 초기모드는 644
    int init_mode = 0644;
    int file_descriptor;
    file_descriptor = creat(file_name, init_mode);
    if (file_descriptor < 0)
    {
        printf("File create Error\n");
        return -1;
    }
    else 
    {
        printf("File %s is created with mode %#o\n", file_name, init_mode);
    }


    // 생성된 파일의 모드를 777로 변경
    if(chmod(file_name, access_mode) < 0)
    {
        close(file_descriptor);
        printf("File mode change error\n");
        return -1;
    }
    
    printf("File mode is changed to %#o\n", access_mode);

    close(file_descriptor);
    return 0;
}