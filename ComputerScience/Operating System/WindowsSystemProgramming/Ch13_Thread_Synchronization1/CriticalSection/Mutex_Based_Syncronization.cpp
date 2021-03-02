/*
< Critical Section �� ���� ���� >
- 6���� ������
- ��������� gTotalCount ��� ���� ������ �����Ͽ� ����

< Method : ���ؽ� ��� ����ȭ >
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <process.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>


#define NUM_OF_GATE 6

LONG gTotalCount = 0;

// ���ؽ� �ڵ� ����
HANDLE hMutex;

// �����忡�� ȣ���ϴ� �Լ��� ���� ������ +1 �Ѵ�
void IncreseGlobalCount() {

	// Step 2 : ���� ȹ��
	// ���ؽ��� signaled ���°� �� �� ���� ���
	WaitForSingleObject(hMutex, INFINITE);

	// �Ӱ� ����
	gTotalCount++;	

	// Step 3 : ���� ��ȯ
	// WaitForSingleObject ����� ���ؽ��� non-signaled �����̱� ������ siganled�� �ٲ���� ��
	// WaitForSingleObject�� �ǵ��� Ư�� ������
	ReleaseMutex(hMutex);

}

// �������� main �Լ� : IncreseGlobalCount�� 1000�� ȣ��
// _beginthreadex�� ����ϱ� ������ ��ȯ���� unsigned int�� �Ѵ�
unsigned int WINAPI ThreadMain(LPVOID lpParam) {

	for (DWORD i = 0; i < 1000; i++) {
		IncreseGlobalCount();
	}

	return 0;
}


int _tmain(int argc, TCHAR* argv[]) {

	DWORD dwThreadId[NUM_OF_GATE];
	HANDLE hThread[NUM_OF_GATE];

	// Step 1 : ���ؽ� ������Ʈ �ʱ�ȭ
	hMutex = CreateMutex(
		NULL,		// ����Ʈ ����
		FALSE,		// ������ ������ �� �ִ� ����
		NULL		// �̸����� ���ؽ�
	);

	// NUM_OF_GATE �� ��ŭ ������ ����
	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		hThread[i] = (HANDLE) _beginthreadex(
			NULL,						// ����Ʈ ���� : �ڵ� ��� ���� ����
			0,							// ����Ʈ ���� ������
			ThreadMain,					// ������ ���� �Լ�
			NULL,						// ������ ���� �Լ� ���� ����
			CREATE_SUSPENDED,			// ����Ʈ ���� �� ���� ���� �÷��� : �ٷ� ���� x, ResumeThread�� ȣ���Ͽ� ����
			(unsigned*)&dwThreadId[i]	// ������ Id
		);

		if (hThread[i] == NULL) {
			_tprintf(_T("%d th Thread creation fault! \n"), i);
			return -1;
		}
	}

	// ������ ���� : �����带 �����ϴµ� �ð��� �ɸ��� ������ ���� �� �����Ű�� ���� ����
	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		ResumeThread(hThread[i]);
	}

	// ��� �����尡 ����� �� ���� ��ٷ��ش�
	WaitForMultipleObjects(NUM_OF_GATE, hThread, TRUE, INFINITE);

	// ��� ���
	_tprintf(_T("Total Count : %d \n"), gTotalCount);


	// ������ �ڵ� ����
	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		CloseHandle(hThread[i]);
	}

	// Step 4 : ���ؽ� ������Ʈ ���ҽ� ����
	CloseHandle(hMutex);


	return 0;
}





