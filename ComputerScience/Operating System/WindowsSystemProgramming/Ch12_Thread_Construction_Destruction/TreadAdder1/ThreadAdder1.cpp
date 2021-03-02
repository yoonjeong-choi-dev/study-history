/*


*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <locale.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>




// �������� main �Լ�
DWORD WINAPI ThreadMain(LPVOID lpParam) {
	// �迭�� ������ �� ��ҿ� �� ������ ���ڵ��� ���Ͽ� ��ȯ
	DWORD* nPtr = (DWORD*)lpParam;

	DWORD num1 = *nPtr;
	DWORD num2 = *(nPtr + 1);

	DWORD total = 0;

	for (DWORD i = num1; i <= num2; i++) {
		total += i;
	}

	return total;
}


DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[]) {

	DWORD dwThreadId[3];
	HANDLE hThread[3];

	DWORD paramThread[] = { 1,3,4,7,8,10 };
	DWORD total = 0;
	DWORD result = 0;


	// ������ 3�� ���� : [1,3], [4,7], [8, 10] �� ���� ����
	hThread[0] = CreateThread(
		NULL,					// ����Ʈ ���� : �ڵ� ��� ���� ����
		0,						// ����Ʈ ���� ������
		ThreadMain,				// ������ ���� �Լ�
		(LPVOID)(&paramThread[0]),	// ������ ���� �Լ� ���� ����
		0,						// ����Ʈ ���� �� ���� ���� �÷���
		&dwThreadId[0] //������ Id
	);

	hThread[1] = CreateThread(
		NULL,					// ����Ʈ ���� : �ڵ� ��� ���� ����
		0,						// ����Ʈ ���� ������
		ThreadMain,				// ������ ���� �Լ�
		(LPVOID)(&paramThread[2]),	// ������ ���� �Լ� ���� ����
		0,						// ����Ʈ ���� �� ���� ���� �÷���
		&dwThreadId[1] //������ Id
	);

	hThread[2] = CreateThread(
		NULL,					// ����Ʈ ���� : �ڵ� ��� ���� ����
		0,						// ����Ʈ ���� ������
		ThreadMain,				// ������ ���� �Լ�
		(LPVOID)(&paramThread[4]),	// ������ ���� �Լ� ���� ����
		0,						// ����Ʈ ���� �� ���� ���� �÷���
		&dwThreadId[2] //������ Id
	);

	// ������ ���� ���н� 
	for (DWORD i = 0; i < 3; i++) {
		if (hThread[i] == NULL) {
			_tprintf(_T("%d th Thread creation fault! \n"), i);
			return -1;
		}
	}
	
	// �� �����尡 ������ ��� ������ ������ ��ٸ���
	WaitForMultipleObjects(
		3,			// ��ٸ� �������� ����
		hThread,	// �ڵ��� �迭 ����
		TRUE,		// ��� Ŀ�� ������Ʈ�� ���°� signaled�� �ɶ����� 
		INFINITE	// ������ ��ٸ���
	);


	// ��� �ڵ带 �̿��� ����
	for (DWORD i = 0; i < 3; i++) {
		GetExitCodeThread(hThread[i], &result);
		total += result;
	}

	_tprintf(_T("total (1 ~ 10) : %d \n"), total);

	// ������ �ڵ� ����
	for (DWORD i = 0; i < 3; i++) {
		CloseHandle(hThread[i]);
	}

	return 0;
}





