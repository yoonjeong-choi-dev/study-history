/*
[ Prompt Project ]
- windows���� �����ϴ� ��� ������Ʈ�� �����ϴ� ������Ʈ


[ Version 1 ]
- ��� �����

[ Version 2 ]
- ǥ�� ��� �˻��� �ִ� ���μ��� �̸� �Է½� �ش� ���μ��� ���� ���

[ Version 3 ]
- start ��ɾ� �߰�
	: �Էµ� ��ɾ ������ �츮�� ���������Ʈ�� ��� �����ϵ��� �䱸�ϴ� ��ɾ�
- echo ��ɾ� �߰�
	: echo �� ���ڿ����� �״�� ����ϴ� ��ɾ�


[ Version 4 ]
- lp ��ɾ� �߰�
	: ���� �������� ���μ��� ������ ����ϴ� ��ɾ�
- kp "���μ��� �̸�"
	: ���μ��� �̸��� ���� �ش� ���μ����� �����Ű�� ��ɾ�
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
#define CMD_TOKEN_NUM 10

// Global variables
TCHAR ERROR_CMD[] = _T("'%s'��(��) ������ �� �ִ� ���α׷��� �ƴմϴ�.\n");

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
int tokenNum;	// len(cmdTokenList)
TCHAR seps[] = _T(" , \t\n");

// ���� ���μ����� �����Ű�� ���� ������Ʈ �̸� : �ʿ�� ���� �� ����
TCHAR myProcessName[] = _T("Project_ver4");	
//TCHAR myProcessName[] = _T("Re_WindowsSystemProgramming");	


/* �����������������������
	Functions
����������������������� */
void CmdReadTokenize(void);

int CmdProcessing(void);
TCHAR* StrLower(TCHAR*);

BOOL CreateMyProcess(TCHAR* commandStringOptions);
BOOL CreateCommonProcess(TCHAR*);
void EchoCommand(void);

void ShowAllProcess(void);
void KillProcess(TCHAR*);

int _tmain(int argc, TCHAR* argv[]) {

	// �ѱ� �Է��� �����ϰ� �ϱ� ���� ����
	_tsetlocale(LC_ALL, _T("Korean"));


	// �Ű� ���� ���� ó��
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			_tcscpy(cmdTokenList[i - 1], argv[i]);
		}
		tokenNum = argc - 1;
		CmdProcessing();
	}

	DWORD isExit = NULL;

	while (1) {

		CmdReadTokenize();

		if (tokenNum == 0)
			continue;


		isExit = CmdProcessing();

		if (isExit == TRUE) {
			_fputts(_T("��ɾ� ó���� �����մϴ�.\n"), stdout);
			break;
		}
	}

	system("pause");

	return 0;
}



/*
function : void CmdReadTokenize(void)
- ver2�� CmdProcessing���� ������� �Է��� �޴� ����� �и��� �Լ�
- �Է� ���ڿ��� ��ū ����Ʈ�� ��ū ����Ʈ�� ���̸� ������Ʈ
*/

void CmdReadTokenize(void) {
	_fputts(_T("Best command prompt>> "), stdout);

	// �Է� ���ڿ� �޾ƿ���
	// _getts(gets, getws)�� VS2015���� ������.
	_getts_s(cmdString, STR_LEN - 1);

	// ��ǥ, ��, ���͸� �������� �Է� ���ڿ� ��ūȭ
	TCHAR* token = _tcstok(cmdString, seps);

	// ��ū�� ����
	tokenNum = 0;
	while (token != NULL) {
		// ���� ��ū�� ��ū ����Ʈ�� ����
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));

		// ���� ��ū�� ������ ���ڿ��� ���Ѵ�
		token = _tcstok(NULL, seps);
	}
}


/*
function : int CmdProcessing()
- �Է¹��� �ش� ��ɾ ������ ����� �������ִ� �Լ�
- tokenNum : ��ūȭ�� ��ɾ� ��ū�� ����(2�̻��̸� �߰� ��ɾ �ִ� ��)
	- cmdTokenList �迭�� ���� ����
- exit�� �ԷµǸ� TRUE�� ��ȯ�ϰ� �̴� ���α׷��� ����� �̾�����.

������ 1 : tokenNum�� 2�̻��϶��� �׻� �߰� ��ɾ ����ؾ��Ѵ�.
 1) commadStringOptions : ��ū�� ����(�����̽�)�� ����鼭 ���ڿ��� ������ش�
	e.g cmdTokenList=={"start", "echo", "This", "is", "a" "echo" "test"}
	=> start echo This is a echo test.
	- �ش� ������ cmd ���μ��� ������

�̸� ���� ���ֱ� ���� �ڵ�
{
	_tcscpy(commandStringOptions, cmdTokenList[0]);

	for (int i = 1; i < tokenNum; i++) {
		_stprintf(commandStringOptions, _T("%s %s"),
		commandStringOptions, cmdTokenList[i]);
	}
}

 2) optionString : ���� Ŀ�ǵ带 ������ �ɼų� Ŀ�ǵ带 �������ִ� �Լ�
	e.g cmdTokenList=={"start", "echo", "This", "is", "a" "echo" "test"}
	=> echo This is a echo test.

����� ����� ������ 1-1)�� �̿��Ѵ�
*/
int CmdProcessing() {

	BOOL isRun;

	// ���μ��� ������ �ʿ��� ������
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	TCHAR optionString[STR_LEN] = { 0, };


	// �� ��ɾ ���� ��� ����
	// exit : ���μ��� ����
	if (!_tcscmp(cmdTokenList[0], _T("exit"))) {
		return TRUE;
	}
	// start ��ɾ� ���
	else if (!_tcscmp(cmdTokenList[0], _T("start"))) {

		// start ���Ŀ� �߰� Ŀ�ǵ尡 �ִ� ���
		if (tokenNum > 1) {
			// start ������ ��ū�� ����
			for (int i = 1; i < tokenNum; i++) {
				_stprintf(optionString,
					_T("%s %s"), optionString, cmdTokenList[i]
				);
			}

			// ���ο� myCMD�� ���� �ش� optionString ������ ���� �۾�
			_stprintf(cmdStringWithOptions, _T("%s %s"),
				myProcessName, optionString);
		}
		// start Ŀ�ǵ常 �ִ� ��� => �ܼ��� myProcessName�� ����
		else {
			_stprintf(cmdStringWithOptions, _T("%s"), myProcessName);
		}

		// myProcessName ����
		CreateMyProcess(cmdStringWithOptions);
	}
	// echo : echo �ڿ� ������ ���ڿ��� ���
	else if (!_tcscmp(cmdTokenList[0], _T("echo"))) {
		EchoCommand();
	}
	// lp : ���� ���� ���� ���η��� ���� ���
	else if (!_tcscmp(cmdTokenList[0], _T("lp"))) {
		ShowAllProcess();
	}
	// kp : kp �ڿ� ������ ���ڿ��� �ش��ϴ� ���μ��� ����
	else if (!_tcscmp(cmdTokenList[0], _T("kp"))) {
		// kp �ڿ� ���ڰ� ���� ���
		if (tokenNum < 2) {
			_tprintf(_T("[usage] : kp <process name> \n"));
		}
		KillProcess(cmdTokenList[1]);
	}
	// ��ɾ �ƴ� ���
	else {
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);
		for (int i = 1; i < tokenNum; i++) {
			_stprintf(cmdStringWithOptions,
				_T("%s %s"), cmdStringWithOptions, cmdTokenList[i]
			);
		}

		//_tprintf(_T("command : %s\n tokenNum: %d\n"), cmdStringWithOptions, tokenNum);

		BOOL ret = CreateCommonProcess(cmdStringWithOptions);
		if (ret == FALSE) {
			_tprintf(ERROR_CMD, cmdStringWithOptions);
		}
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


/*
function : BOOL CreateCommonProcess(TCHAR*)
- ���ڿ��� �����Ǵ� ���μ��� ����
*/
BOOL CreateCommonProcess(TCHAR* process) {
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	BOOL isRun = CreateProcess(
		NULL,
		process,
		NULL, NULL, TRUE,
		0,
		NULL, NULL,
		&si, &pi
	);

	// Ŀ�� ������Ʈ�� ��ȯ.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return isRun;
}


/*
function : BOOL CreateMyProcess(TCHAR* )
- ���ڿ��� ��������ִ� �츮�� cmd �������� ���μ��� ����
*/
BOOL CreateMyProcess(TCHAR* commandStringOptions) {

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	BOOL isRun = CreateProcess(
		NULL,
		commandStringOptions,
		NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE,
		NULL, NULL,
		&si, &pi
	);

	// Ŀ�� ������Ʈ�� ��ȯ.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return isRun;

}


/*
function : void EchoCommand(void)
- echo ��ɿ� ���� ���
- echo �� ���ڿ��� �״�� ���
*/

void EchoCommand(void) {
	TCHAR optionString[STR_LEN] = { 0, };

	for (int i = 1; i < tokenNum; i++) {
		_stprintf(optionString, _T("%s %s"),
			optionString, cmdTokenList[i]);
	}


	_tprintf(_T("Echo message :%s \n"), optionString);
}



/*
function : void ShowAllProcess(void)
- ps ��ɾ ���� ���
- ���� �������� ��� ���μ����� �̸� �� ID ������ ����Ѵ�
*/
void ShowAllProcess(void) {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		_tprintf(_T("CreateToolHelp32Snapshot error! \n"));
		return;
	}


	// ���μ��� ������ ��� ���� ����ü ���� ����
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	// ù��° ���μ��� ���� ����
	if (!Process32First(hProcessSnap, &pe32)) {
		_tprintf(_T("Process32First error! \n"));
		CloseHandle(hProcessSnap);
		return;
	}

	// ���μ��� ������ ���������� ���
	do {
		_tprintf(_T("%25s %5d \n"), pe32.szExeFile, pe32.th32ProcessID);

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return;
}


/*
function : void KillProcess(TCHAR* process)
- kp ��ɾ ���� ���
- process�� �ش��ϴ� ���μ��� ����
*/
void KillProcess(TCHAR* process) {
	// �켱 ���� �������� ���μ��� ����Ʈ�� ���´�

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		_tprintf(_T("CreateToolHelp32Snapshot error! \n"));
		return;
	}


	// ���μ��� ������ ��� ���� ����ü ���� ����
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	// ù��° ���μ��� ���� ����
	if (!Process32First(hProcessSnap, &pe32)) {
		_tprintf(_T("Process32First error! \n"));
		CloseHandle(hProcessSnap);
		return;
	}

	
	// process�� ���� ���������� �Ǻ��ϴ� �÷���
	bool isRunning = FALSE;
	HANDLE hProcess;

	// ���μ��� ������ ���������� process�� ���Ѵ�
	do {

		// �Էµ� process�� ���� �������� ���μ����� �̸� ��
		if (_tcscmp(pe32.szExeFile, process) == 0) {
			// ���μ����� ID�� ���� �ڵ� ���� ��� ���� ����
			hProcess = OpenProcess(
				PROCESS_ALL_ACCESS,
				FALSE,
				pe32.th32ProcessID		// open�� ���μ����� ID
			);

			// �ش� �ڵ��� ���� ���μ��� ����
			if (hProcess != NULL) {
				TerminateProcess(hProcess, -1);
				isRunning = TRUE;
			}

			CloseHandle(hProcess);
			break;
		}

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);

	// ���� ���� ���� ���
	if (isRunning) {
		_tprintf(_T("\tKill the process : %s \n"), process);
	}
	else {
		_tprintf(_T("\tThere is no running process : %s \n"), process);
	}

	return;
}