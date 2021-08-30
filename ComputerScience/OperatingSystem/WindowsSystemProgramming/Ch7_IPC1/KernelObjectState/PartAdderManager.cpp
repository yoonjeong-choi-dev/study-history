


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>


int _tmain(int argc, TCHAR* argv[]) {

	// 프로세스 2개 생성
	STARTUPINFO si1 = { 0, };
	STARTUPINFO si2 = { 0, };
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;

	TCHAR command1[] = _T("PartAdder.exe 1 5");
	TCHAR command2[] = _T("PartAdder.exe 6 10");

	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);

	CreateProcess(
		NULL, command1,
		NULL, NULL, TRUE,
		0, NULL, NULL,
		&si1, &pi1
	);

	CreateProcess(
		NULL, command2,
		NULL, NULL, TRUE,
		0, NULL, NULL,
		&si2, &pi2
	);

	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hThread);

	// 프로세스가 종료될 때까지 기다린다
	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	// 종료 코드 가져오기
	DWORD return_val1, return_val2;
	GetExitCodeProcess(pi1.hProcess, &return_val1);
	GetExitCodeProcess(pi2.hProcess, &return_val2);

	if (return_val1 == -1 || return_val2 == -1) {
		return -1;
	}


	DWORD sum = return_val1 + return_val2;


	_tprintf(_T("PartAdder 1 : %d \n"), return_val1);
	_tprintf(_T("PatrAdder 2 : %d \n"), return_val2);
	_tprintf(_T("total : %d \n"), sum);

	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	_gettchar();

	return 0;
}


