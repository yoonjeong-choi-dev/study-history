/*
< ���� ���� Ÿ�̸� >
*/

// SetWaitableTimer �Լ� ȣ���� �ϱ� ���ؼ��� Windows NT �̻󿡼� ����
// Windows NT �̻󿡼� �����Ű�� ���� ��ũ��
#define _WIN32_WINNT 0x0400


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <process.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>



int _tmain(int argc, TCHAR* argv[]) {

	HANDLE hTimer = NULL;
	
	LARGE_INTEGER liDueTime;
	// - : ��� �ð� => ���ݺ��� 10�� ��
	liDueTime.QuadPart = -100000000;	

	// Ÿ�̸� ������Ʈ ����
	hTimer = CreateWaitableTimer(
		NULL,				// ���� �Ӽ� ����
		FALSE,				// �ڵ� ���� ���
		_T("WaitableTimer")	// Ÿ�̸� �̸� �ο�
	);

	if (!hTimer) {
		_tprintf(
			_T("CreateWaitableTimer Failed : %d \n"),
			GetLastError()
		);
		return 1;
	}

	_tprintf(_T("Waiting for 10 seconds....\n"));

	// Ÿ�̸� �˶� ����
	SetWaitableTimer(
		hTimer,		// Ÿ�̸� ������Ʈ�� �ڵ�
		&liDueTime,	// �˶��� �︮�� �ð� : �����ΰ�� ��� �ð�
		0,			// Ÿ�̸� �ֱ� ����
		NULL,		// �Ϸ� ��ƾ Ÿ�̸� ���� ����
		NULL,		// �Ϸ� ��ƾ Ÿ�̸� ���� ����
		FALSE		// ���� ���� ���� �Ű� ����
	);

	// Ÿ�̸� �˶� ���
	WaitForSingleObject(hTimer, INFINITE);
	_tprintf(_T("Timer was Signaled! \n"));
	MessageBeep(MB_ICONEXCLAMATION);
	
	system("pause");
	return 0;
}





