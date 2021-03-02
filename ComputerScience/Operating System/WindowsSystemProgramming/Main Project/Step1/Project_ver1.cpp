/*
[ Prompt Project ]
- windows���� �����ϴ� ��� ������Ʈ�� �����ϴ� ������Ʈ


[ Version 1 ]
- ��� �����
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
TCHAR ERROR_CMD[] = _T("'%s'��(��) ������ �� �ִ� ���α׷��� �ƴմϴ�.\n");

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" , \t\n");


/* �����������������������
		 Functions 
   ����������������������� */ 
int CmdProcessing(void);
TCHAR* StrLower(TCHAR*);



int _tmain(int argc, TCHAR* arvg[]) {
	
	// �ѱ� �Է��� �����ϰ� �ϱ� ���� ����
	_tsetlocale(LC_ALL, _T("Korean"));

	DWORD isExit;

	while (1) {
		isExit = CmdProcessing();

		if (isExit == TRUE) {
			_fputts(_T("��ɾ� ó���� �����մϴ�\n"), stdout);
			break;
		}
	}


	return 0;
}




/*
function : int CmdProcessing(void)
- ��ɾ �Է� �޾� �ش� ��ɾ ������ ����� �������ִ� �Լ�
- exit�� �ԷµǸ� ���α׷� ����
*/
int CmdProcessing(void) {
	_fputts(_T("Best command prompt>> "), stdout);

	// _getts(gets, getws)�� VS2015���� ������.
	_getts_s(cmdString, STR_LEN - 1);	// �Է� ���ڿ� �޾ƿ���

	// ��ǥ, ��, ���͸� �������� �Է� ���ڿ� ��ūȭ
	TCHAR* token = _tcstok(cmdString, seps);

	int tokenNum = 0;
	while (token != NULL) {
		// ���� ��ū�� ��ū ����Ʈ�� ����
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));

		// ���� ��ū�� ������ ���ڿ��� ���Ѵ�
		token = _tcstok(NULL, seps);
	}

	// �� ��ɾ ���� ��� ����
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
- ���ڿ� ������ ��� �빮�ڸ� �ҹ��ڷ� ����
- ����� ���ڿ��� ������ ��ȯ
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
