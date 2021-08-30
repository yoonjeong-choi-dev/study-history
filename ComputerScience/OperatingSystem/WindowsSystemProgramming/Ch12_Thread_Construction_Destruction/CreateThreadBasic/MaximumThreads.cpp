/*
[ Prompt Project ]

*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <locale.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>


#define MAX_THREADS (1024*10)

// �������� main �Լ�
DWORD WINAPI ThreadMain(LPVOID lpParam) {
	DWORD threadNum = (DWORD)lpParam;

	while (1) {
		_tprintf(_T("Thread num : %d \n"), threadNum);
		Sleep(5000);
	}
	return 0;
}


DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[]) {

	DWORD dwThreadId[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	// ���� ������ �ִ� ������ ������ ����
	while (1) {

		// ������ ���� ��û
		hThread[cntOfThread] = CreateThread(
			NULL,					// ����Ʈ ���� : �ڵ� ��� ���� ����
			0,						// ����Ʈ ���� ������
			ThreadMain,				// ������ ���� �Լ�
			(LPVOID)cntOfThread,	// ������ ���� �Լ� ���� ����
			0,						// ����Ʈ ���� �� ���� ���� �÷���
			&dwThreadId[cntOfThread] //������ Id
		);

		// ������ ���� Ȯ��
		if (hThread	[cntOfThread] == NULL) {
			_tprintf(_T("MAXIMUM THREAD NUMBER : %d \n"), cntOfThread);
			break;
		}
		else {
			cntOfThread++;
		}
	}

	// ������ �ڵ� ����
	for (DWORD i = 0; i < cntOfThread; i++) {
		CloseHandle(hThread[i]);
	}

	return 0;
}





