/*
[ Prompt Project ]
- windows���� �����ϴ� ��� ������Ʈ�� �����ϴ� ������Ʈ


[ type ]
- Promt Project���� ����� type ����� ���� ���μ���
- �ؽ�Ʈ ������ �ܼ�â�� ����ϴ� ���
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