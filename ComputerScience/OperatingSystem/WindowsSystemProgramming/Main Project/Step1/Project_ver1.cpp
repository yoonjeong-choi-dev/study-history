/*
[ Prompt Project ]
- windows에서 제공하는 명령 프롬프트를 구현하는 프로젝트


[ Version 1 ]
- 골격 만들기
- 

*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <locale.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>


// Constant Macro
#define STR_LEN 256
#define CMD_TOKEN_NUM 10

// Global variables
TCHAR ERROR_CMD[] = _T("'%s'은(는) 실행할 수 있는 프로그램이 아닙니다.\n");

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" , \t\n");


/* ■■■■■■■■■■■■■■■■■■■■■■
		 Functions 
   ■■■■■■■■■■■■■■■■■■■■■■ */ 
int CmdProcessing(void);
TCHAR* StrLower(TCHAR*);



int _tmain(int argc, TCHAR* arvg[]) {
	
	// 한글 입력을 가능하게 하기 위한 설정
	_tsetlocale(LC_ALL, _T("Korean"));

	DWORD isExit;

	while (1) {
		isExit = CmdProcessing();

		if (isExit == TRUE) {
			_fputts(_T("명령어 처리를 종료합니다\n"), stdout);
			break;
		}
	}


	return 0;
}




/*
function : int CmdProcessing(void)
- 명령어를 입력 받아 해당 명령어에 지정된 기능을 수행해주는 함수
- exit이 입력되면 프로그램 종료
*/
int CmdProcessing(void) {
	_fputts(_T("Best command prompt>> "), stdout);

	// _getts(gets, getws)는 VS2015부터 삭제됨.
	_getts_s(cmdString, STR_LEN - 1);	// 입력 문자열 받아오기

	// 쉼표, 탭, 엔터를 기준으로 입력 문자열 토큰화
	TCHAR* token = _tcstok(cmdString, seps);

	int tokenNum = 0;
	while (token != NULL) {
		// 현재 토큰을 토큰 리스트에 저장
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));

		// 다음 토큰에 저장할 문자열을 구한다
		token = _tcstok(NULL, seps);
	}

	// 각 명령어에 대한 기능 수행
	if (!_tcscmp(cmdTokenList[0], _T("exit"))) {
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("added command 1"))) {

	}
	else if (!_tcscmp(cmdTokenList[0], _T("added command 2"))) {

	}
	else {
		_tprintf(ERROR_CMD, cmdTokenList[0]);
	}

	return FALSE;
}

/*
function : TCHAR* StrLower(TCHAR*)
- 문자열 내부의 모든 대문자를 소문자로 변경
- 변경된 문자열의 포인터 반환
*/
TCHAR* StrLower(TCHAR* pStr) {
	TCHAR* ret = pStr;

	while (*pStr) {
		if (_istupper(*pStr)) {
			*pStr = _totlower(*pStr);
		}
		pStr++;
	}

	return ret;
}
