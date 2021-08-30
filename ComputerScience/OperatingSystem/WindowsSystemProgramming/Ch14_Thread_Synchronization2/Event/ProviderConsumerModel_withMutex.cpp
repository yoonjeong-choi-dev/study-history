/*
< Event+Mutex �� ���� ���� - ������/�Һ��� �� >
- ������ ������ : �ܺο��� ���ڿ��� �Է¹޾� ����(���� ������)
- �Һ��� ������1 : ����� ���ڿ��� ȭ�鿡 ���
- �Һ��� ������2 : ����� ���ڿ��� ���̸� ȭ�� ���
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <process.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>



// ������/�Һ��� ���� �����ϴ� ���ڿ� �迭�� �� �迭�� �����ϴ� �̺�Ʈ �� ���ؽ��� ���� ����ü
typedef struct _SynchString {
	TCHAR string[100];
	HANDLE hEvent;
	HANDLE hMutex;
} SynchString;

SynchString gSync;

// �Һ��� ������1 ���� �Լ�
unsigned int WINAPI ConsumerThreadFunction_Print(LPVOID lpParam) {
	// event signaled ���°� �� ������ ���
	WaitForSingleObject(gSync.hEvent, INFINITE);

	// mutex�� ��� �Ӱ迵�� ����
	WaitForSingleObject(gSync.hMutex, INFINITE);

	// �Ӱ� ����
	_fputts(_T("Output string : "), stdout);
	_fputts(gSync.string, stdout);

	// mutex ��ȯ
	ReleaseMutex(gSync.hMutex);

	return 0;
}

// �Һ��� ������2 ���� �Լ�
unsigned int WINAPI ConsumerThreadFunction_Count(LPVOID lpParam) {
	// event signaled ���°� �� ������ ���
	WaitForSingleObject(gSync.hEvent, INFINITE);

	// mutex�� ��� �Ӱ迵�� ����
	WaitForSingleObject(gSync.hMutex, INFINITE);

	// �Ӱ� ����
	_tprintf(
		_T("Output string length : %d \n"),
		_tcslen(gSync.string) - 1
	);

	// mutex ��ȯ
	ReleaseMutex(gSync.hMutex);

	return 0;
}


int _tmain(int argc, TCHAR* argv[]) {

	HANDLE hThread[2];
	DWORD dwThreadId[2];

	// Event ������Ʈ ����
	gSync.hEvent = CreateEvent(
		NULL,		// ��� �Ұ�
		TRUE,		// �ڵ� ���� ���
		FALSE,		// non-signaled ���·� ����
		NULL		// �̸� X
	);


	// Mutex ������Ʈ ����
	gSync.hMutex = CreateMutex(
		NULL,		// ����Ʈ ����
		FALSE,		// ������ ������ �� �ִ� ����
		NULL		// �̸����� ���ؽ�
	);

	if (gSync.hEvent == NULL || gSync.hMutex == NULL) {
		_fputts(_T("Kernel object Creation Error \n"), stdout);
		return -1;
	}

	// �Һ��� ������ ����
	hThread[0] = (HANDLE)_beginthreadex(
		NULL,							// ����Ʈ ���� : �ڵ� ��� ���� ����
		0,								// ����Ʈ ���� ������
		ConsumerThreadFunction_Print,	// ������ ���� �Լ�
		NULL,							// ������ ���� �Լ� ���� ����
		0,								// ����Ʈ ���� �� ���� ���� �÷���
		(unsigned*)&dwThreadId[0]		// ������ Id
	);

	hThread[1] = (HANDLE)_beginthreadex(
		NULL,							// ����Ʈ ���� : �ڵ� ��� ���� ����
		0,								// ����Ʈ ���� ������
		ConsumerThreadFunction_Count,	// ������ ���� �Լ�
		NULL,							// ������ ���� �Լ� ���� ����
		0,								// ����Ʈ ���� �� ���� ���� �÷���
		(unsigned*)&dwThreadId[1]		// ������ Id
	);

	if (hThread[0] == NULL || hThread[1] ==NULL) {
		_fputts(_T("Thread Creation Error \n"), stdout);
		return -1;
	}


	// ���� ������ : ������ ����
	_fputts(_T("Insert string : "), stdout);
	_fgetts(gSync.string, 30, stdin);

	// Event ���� signaled�� ���� : ���ڿ� ����(�Է�) �Ϸ�
	SetEvent(gSync.hEvent);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	// ���ҽ� ����
	CloseHandle(gSync.hEvent);
	CloseHandle(gSync.hMutex);
	CloseHandle(hThread[0]); CloseHandle(hThread[1]);

	system("pause");
	return 0;
}





