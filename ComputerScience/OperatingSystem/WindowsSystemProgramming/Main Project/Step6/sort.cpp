/*
[ Prompt Project ]
- windows에서 제공하는 명령 프롬프트를 구현하는 프로젝트


[ sort ]
- Promt Project에서 사용할 sort 기능을 위한 프로세스
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

	// 콘솔에서 문자열 입력 받아오기
	int numStr;
	for (numStr = 0; numStr < MAX_STRING_NUM; numStr++) {
		// 표준 I/0를 통한 문자열 저장
		TCHAR * isEOF = _fgetts(strArr[numStr], STR_LEN, stdin);

		// Ctrl+Z를 입력했으면 끝
		if (isEOF == NULL) {
			break;
		}
	}


	// Bubble Sort
	TCHAR tempStr[STR_LEN];
	for (int i = 0; i < numStr; i++) {
		for (int j = numStr - 1; j > i; j--) {

			// strArr[j - 1] > strArr[j] 인 경우 swap
			if (_tcscmp(strArr[j - 1], strArr[j]) > 0) {
				_tcscpy(tempStr, strArr[j - 1]);
				_tcscpy(strArr[j - 1], strArr[j]);
				_tcscpy(strArr[j], tempStr);
			}
		}
	}

	// 정렬 결과를 출력
	for (int i = 0; i < numStr; i++) {
		_fputts(strArr[i], stdout);
	}
}


int _tmain(int argc, TCHAR* argv) {
	SortInputString();

	return 0;
}