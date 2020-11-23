/*
< Named Mutex �� ���� ���� - ���μ��� �� ������ ����ȭ >
- 
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <process.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>


HANDLE hMutex;
DWORD dwWaitResult;

#define CREATE_MUTEX 1
#define OPEN_MUTEX 0


// ���μ��� �� ������ �Ӱ� ����
void PrcessBaseCriticalSection() {
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	// WaitForSingleObject�� ��ȯ ���� ���� ó��
	switch (dwWaitResult) {
	case WAIT_OBJECT_0:
		// �ش� �����尡 ���ؽ� ����
		_tprintf(_T("This thread got mutex ! \n"));
		break;
	case WAIT_TIMEOUT:
		// Ÿ�� �ƿ� �߻�
		_tprintf(_T("Timer expired ! \n"));
		break;
	case WAIT_ABANDONED:
		// ���ؽ��� ��ȯ�� ����� ������� ���� ���
		_tprintf(_T("Mutex is not returned - WAIT_ABANDONED \n"));
		break;
	}

	for (DWORD i = 0; i < 5; i++) {
		_tprintf(_T("Thread Running ! \n"));
		Sleep(1000);
	}

	// ���ؽ� ��ȯ
	ReleaseMutex(hMutex);
}


int _tmain(int argc, TCHAR* argv[]) {

// ���Ǻ� ������
#if OPEN_MUTEX
	// ���ؽ� ����
	hMutex = CreateMutex(
		NULL,				// ����Ʈ ����
		FALSE,				// ������ ������ �� �ִ� ����
		_T("NamedMutex")	// NamedMutex �̸� �ο�
	);
#else
	// ���ؽ� ��������
	hMutex = OpenMutex(
		MUTEX_ALL_ACCESS,	// ���� ���� ��û
		FALSE,				// �ڵ� ��� X
		_T("NamedMutex")
	);

#endif

	if (hMutex == NULL) {
		_tprintf(_T("CreateMutex Error : %d \n"), GetLastError());
		return -1;
	}

	PrcessBaseCriticalSection();

	CloseHandle(hMutex);

	system("pause");
	return 0;
}





