/*
< ī��Ʈ �������� �� ���� ���� - �ùķ��̼� >
- ���̺��� �� 10���̰�, ���ÿ� �� 10���� �մԸ� �޴´�
- �մ� ���� ���� 50��
- �� �մ��� �Ļ� �ð��� 10~30�� ����
- �մ� <=> ������, ���̺� <=> �������� ���� ����
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <process.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_TABLES 10
#define NUM_OF_CUSTOMERS 50
#define RANGE_MIN 10
#define RANGE_MAX (30 - RANGE_MIN)

// �������� �ڵ�
HANDLE hSemaphore;

// �� �մ��� �Ļ� �ð�
DWORD randTimeArr[NUM_OF_CUSTOMERS];


// �մ��� �Ļ� �ð�
void TakeMeal(DWORD time) {

	// Step 2 : ���� ��� ���� ���� ȹ�� : ���̺� ����
	WaitForSingleObject(hSemaphore, INFINITE);

	// �Ӱ� ���� : �� ��° �մ�(������)�� ������ �Դ��� ���
	_tprintf(_T("Enter %d Customer\n"), GetCurrentThreadId());
	_tprintf(_T("Customer %d  Having Lauch \n"), GetCurrentThreadId());
	Sleep(1000 * time);
	
	// Step 3 : ���� ��� ���� ���� ��ȯ(ī��Ʈ -1) : ���̺� ����
	ReleaseSemaphore(hSemaphore, 1, NULL);
	_tprintf(_T("Leave %d Customer \n"), GetCurrentThreadId());
}


// �������� main �Լ� : IncreseGlobalCount�� 1000�� ȣ��
// _beginthreadex�� ����ϱ� ������ ��ȯ���� unsigned int�� �Ѵ�
unsigned int WINAPI ThreadMain(LPVOID lpParam) {

	TakeMeal((DWORD)lpParam);
	return 0;
}


int _tmain(int argc, TCHAR* argv[]) {

	DWORD dwThreadId[NUM_OF_CUSTOMERS];
	HANDLE hThread[NUM_OF_CUSTOMERS];

	// �մ��� �Ļ� �ð� ���� �Ҵ�
	srand((unsigned)time(NULL));
	for (int i = 0; i < NUM_OF_CUSTOMERS; i++) {
		randTimeArr[i] = (DWORD)(
			((double)rand() / (double)RAND_MAX) * RANGE_MAX + RANGE_MIN
			);
	}

	// Step 1 : �������� ������Ʈ �ʱ�ȭ
	hSemaphore = CreateSemaphore(
		NULL,			// ����Ʈ ����
		NUM_OF_TABLES,	// ���� ���� ī��Ʈ �ʱⰪ
		NUM_OF_TABLES,	// ���� ���� ī��Ʈ �ִ밪
		NULL			// �̸����� ��������
	);

	if (hSemaphore == NULL) {
		_tprintf(_T("CreateSemaphore Err : %d \n"), GetLastError());
	}


	_tprintf(_T("====================== START ======================\n"));

	// NUM_OF_CUSTOMERS �� ��ŭ ������ ����
	for (DWORD i = 0; i < NUM_OF_CUSTOMERS; i++) {
		hThread[i] = (HANDLE) _beginthreadex(
			NULL,						// ����Ʈ ���� : �ڵ� ��� ���� ����
			0,							// ����Ʈ ���� ������
			ThreadMain,					// ������ ���� �Լ�
			(void*)randTimeArr[i],		// ������ ���� �Լ� ���� ����
			CREATE_SUSPENDED,			// ����Ʈ ���� �� ���� ���� �÷��� : �ٷ� ���� x, ResumeThread�� ȣ���Ͽ� ����
			(unsigned*)&dwThreadId[i]	// ������ Id
		);

		if (hThread[i] == NULL) {
			_tprintf(_T("%d th Thread creation fault! \n"), i);
			return -1;
		}
	}

	// ������ ���� : �����带 �����ϴµ� �ð��� �ɸ��� ������ ���� �� �����Ű�� ���� ����
	for (DWORD i = 0; i < NUM_OF_CUSTOMERS; i++) {
		ResumeThread(hThread[i]);
	}

	// ��� �����尡 ����� �� ���� ��ٷ��ش�
	WaitForMultipleObjects(NUM_OF_CUSTOMERS, hThread, TRUE, INFINITE);


	_tprintf(_T("====================== END ======================\n"));

	// ������ �ڵ� ����
	for (DWORD i = 0; i < NUM_OF_CUSTOMERS; i++) {
		CloseHandle(hThread[i]);
	}

	// Step 4 : ���ؽ� ������Ʈ ���ҽ� ����
	CloseHandle(hSemaphore);


	return 0;
}





