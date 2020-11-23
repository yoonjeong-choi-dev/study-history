/*
[ Prompt Project ]
- windows에서 제공하는 명령 프롬프트를 구현하는 프로젝트


[ type ]
- Promt Project에서 사용할 type 기능을 위한 프로세스
- 텍스트 파일을 콘솔창에 출력하는 기능
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>

// Header for Standard Programming
#include <stdio.h>


#define BUFF_SIZE 1024

void TYPE(TCHAR* fileName) {
	TCHAR StringBuff[BUFF_SIZE];

	FILE* filePtr = _tfopen(fileName, _T("rt"));
	while (_fgetts(StringBuff, 1024, filePtr)) {
		_fputts(StringBuff, stdout);
	}
}




int _tmain(int argc, TCHAR* argv[]) {

	if (argc < 2)
		return -1;

	TYPE(argv[1]);

	return 0;
}