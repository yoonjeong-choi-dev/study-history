#include <stdio.h>


/*
리눅스에서는 mknod를 이용해서 디렉터리 생성 불가능
there is no ability to generate a (sub-)directory here is the link to that man page: man7.org/linux/man-pages/man2/mknod.2.html
*/
int main()
{
    int access_mode, file_descriptor;

    // 생성할 임시 디렉터리 및 파일 경로 정의
    char* dir_path = "./temp_dir";
    char* file_name = "./temp_file";

    // 디렉터리 생성
    if(mknod(dir_path, 040755) < 0)
    {
        printf("mknod() failed\n");
        return -1;
    }
    else
    {
        printf("%s directory is created\n", dir_path);
    }

    // 생성한 디렉터리로 현재 작업 디렉터리 이동
    if(chdir(dir_path) <0)
    {
        printf("chdir() failed\n");
        return -1;
    }
    else
    {
        printf("Current directory is changed to '%s'\n", dir_path);
    }

    // 현재 디렉터리에 임시 파일 생성
    file_descriptor = creat(file_name, 0644);
    if(file_descriptor < 0)
    {
        printf("creat() failed\n");
        return -1;
    }
    else{
        printf("%s file is created in %s", file_name, dir_path);
    }

    // 리로스 정리
    close(file_descriptor);
    return 0;
}