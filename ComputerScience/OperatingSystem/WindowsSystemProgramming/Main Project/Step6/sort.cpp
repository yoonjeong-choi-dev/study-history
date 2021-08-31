/*
[ Prompt Project ]
- windows���� �����ϴ� ��� ������Ʈ�� �����ϴ� ������Ʈ


[ sort ]
- Promt Project���� ����� sort ����� ���� ���μ���
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <locale.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>
#include <tlhelp32.h>


// Constant Macro
#define STR_LEN 256
#define MAX_STRING_NUM 100


void SortInputString() {
	TCHAR strArr[MAX_STRING_NUM][STR_LEN];

	// �ֿܼ��� ���ڿ� �Է� �޾ƿ���
	int numStr;
	for (numStr = 0; numStr < MAX_STRING_NUM; numStr++) {
		// ǥ�� I/0�� ���� ���ڿ� ����
		TCHAR * isEOF = _fgetts(strArr[numStr], STR_LEN, stdin);

		// Ctrl+Z�� �Է������� ��
		if (isEOF == NULL) {
			break;
		}
	}


	// Bubble Sort
	TCHAR tempStr[STR_LEN];
	for (int i = 0; i < numStr; i++) {
		for (int j = numStr - 1; j > i; j--) {

			// strArr[j - 1] > strArr[j] �� ��� swap
			if (_tcscmp(strArr[j - 1], strArr[j]) > 0) {
				_tcscpy(tempStr, strArr[j - 1]);
				_tcscpy(strArr[j - 1], strArr[j]);
				_tcscpy(strArr[j], tempStr);
			}
		}
	}

	// ���� ����� ���
	for (int i = 0; i < numStr; i++) {
		_fputts(strArr[i], stdout);
	}
}


int _tmain(int argc, TCHAR* argv) {
	SortInputString();

	return 0;
}