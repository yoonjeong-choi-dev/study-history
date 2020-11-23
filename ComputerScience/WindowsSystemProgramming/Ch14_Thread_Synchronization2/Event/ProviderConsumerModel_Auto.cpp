/*
< Event �� ���� ���� - ������/�Һ��� �� >
- ������ ������ : �ܺο��� ���ڿ��� �Է¹޾� ����(���� ������)
- �Һ��� ������ : ����� ���ڿ��� ȭ�鿡 ���
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <process.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>

// ������ �����尡 �����ϰ� �Һ��� �����尡 �Һ��ϴ� ���ڿ�
TCHAR string[100];
HANDLE hEvent;

// �Һ��� ������ ���� �Լ�
unsigned int WINAPI ConsumerThreadFunction(LPVOID lpParam) {
	// event�� signaled ���°� �� ������ ���
	WaitForSingleObject(hEvent, INFINITE);

	_fputts(_T("Output string : "), stdout);
	_fputts(string, stdout);

	return 0;
}



int _tmain(int argc, TCHAR* argv[]) {

	HANDLE hThread;
	DWORD dwThreadId;

	// Event ������Ʈ ����
	hEvent = CreateEvent(
		NULL,		// ��� �Ұ�
		TRUE,		// �ڵ� ���� ���
		FALSE,		// non-signaled ���·� ����
		NULL		// �̸� X
	);

	if (hEvent == NULL) {
		_fputts(_T("Event object Creation Error \n"), stdout);
		return -1;
	}

	// �Һ��� ������ ����
	hThread = (HANDLE)_beginthreadex(
		NULL,						// ����Ʈ ���� : �ڵ� ��� ���� ����
		0,							// ����Ʈ ���� ������
		ConsumerThreadFunction,		// ������ ���� �Լ�
		NULL,						// ������ ���� �Լ� ���� ����
		0,							// ����Ʈ ���� �� ���� ���� �÷���
		(unsigned*)&dwThreadId		// ������ Id
	);

	if (hThread == NULL) {
		_fputts(_T("Thread Creation Error \n"), stdout);
		return -1;
	}


	// ���� ������ : ������ ����
	_fputts(_T("Insert string : "), stdout);
	_fgetts(string, 30, stdin);

	// Event ���� signaled�� ���� : ���ڿ� ����(�Է�) �Ϸ�
	SetEvent(hEvent);

	WaitForSingleObject(hThread, INFINITE);

	// ���ҽ� ����
	CloseHandle(hEvent);
	CloseHandle(hThread);

	system("pause");
	return 0;
}





