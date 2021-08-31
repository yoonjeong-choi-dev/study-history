/*
< ������ Ǯ�� >
- �������� ������ �Ҹ��� �ý��ۿ� �δ��� �ش�
- �ټ��� �����带 �̸� �����ϰ� �ʿ��� �� ���� ���� ����
- Ǯ�� �����ϴ� ������ ������ ó���ؾ� �� ���� ���� ��� ó���ϴ� ���� �й��ϴ� ����� ������ ����

< ���� ���� >
- �ִ� ��� ���� WORK�� 10000��, ������ Ǯ�� ������ ������ 50��
- WORK : �����尡 �����ϴ� ���� void func(void) ��
- WorkerThread : ������ �������� ������ ��� ���� ����ü
- gThreadPool : ������ Ǯ�� �ش��ϴ� �ڷᱸ��
	- ���� ������ ����
	- WORK ���� ��� ����
		- WORK workList[WORK_MAX]	: WORK ��⿭
		- DWORD idxOfCurrentWork	: ��� 1���� WORK �ε���
		- DWORD idxOfLastAddWork	: ������ �߰��� WORK �ε���
	- ������ ���� ��� ����
		- WorkerThread workerThreadList[THREAD_MAX] : Thread ���� 
		- HANDLE workerEventList[THREAD_MAX]		: Thread�� Event ������Ʈ
		- DWORD threadIdx							: �����ϴ� Thread ����

< ������ Ǯ �Լ� ���� >
- WORK GetWorkFromPool(void)
	- ������ Ǯ���� WORK�� ������ �� ȣ���ϴ� �Լ�
- DWORD AddWorkToPool(WORK work)
	- ���ο� WORK�� ������ Ǯ�� ����� �� ȣ���ϴ� �Լ�
	- ���� �� ���� : �ִ� ��� ���� WORK ������ �ʰ��� ��� ��� �Ұ� => ���� ����Ʈ�� ���� �ʿ�
- DWORD MakeThreadToPool(DWORD numOfThread)
	- ������ Ǯ�� ������ ���� numOfThread ��ŭ �����带 �����ϴ� �Լ�
- void WorkerThreadFunction(LPVOID pParam)
	- �����尡 �������ڸ��� ȣ���ϴ� �������� main �Լ�

< ������ Ǯ ���� ���ٿ� ���� ����ȭ - Mutex >
- void InitMutex()
- void DeInitMutex()
- void AcquireMutex()
- void ReleaseMutex()
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <process.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>

#define WORK_MAX 10000
#define THREAD_MAX 50




// ���������������������������������������������������
// ������ �������� ������ ��� ���� ����ü
// ���������������������������������������������������
typedef struct __WorkerThread {
	HANDLE hThread;
	DWORD idThread;
} WorkerThread;



// ���������������������������������������������������
// Work�� Thread ������ ���� ����ü : ���� ������ ����
// ���������������������������������������������������
// �����尡 �����ϴ� work ���� : �����忡�� ���� ��Ű�� ���� �۾��� �⺻ ����
typedef void(*WORK)(void);

struct __ThreadPool {
	// WORK�� ����ϱ� ���� �迭
	WORK workList[WORK_MAX];

	// Thread ���� 
	WorkerThread workerThreadList[THREAD_MAX];
	// Thread�� Event ������Ʈ : �����忡�� ���� ��Ű�� ���� �̺�Ʈ ������Ʈ
	HANDLE workerEventList[THREAD_MAX];

	// WORK�� ���� ���� : ��� 1���� �� ������ �߰��� WORK �ε���
	DWORD idxOfCurrentWork;
	DWORD idxOfLastAddWork;

	// ������ Ǯ�� �����ϴ� ������ ����
	DWORD threadIdx;
} gThreadPool;



// ���������������������������������������������������
// ������ Ǯ ���� ���ٿ� ���� ����ȭ - Mutex
// ���������������������������������������������������
static HANDLE mutex = NULL;

void InitMutex() {
	mutex = CreateMutex(NULL, FALSE, NULL);
}

void DeInitMutex() {
	BOOL ret = CloseHandle(mutex);
}

void AcquireMutex() {
	DWORD ret = WaitForSingleObject(mutex, INFINITE);
	if (ret == WAIT_FAILED) {
		_tprintf(_T("WaitForSingleObject Error Occur ! \n"));
	}
}

void ReleaseMutex() {
	BOOL ret = ReleaseMutex(mutex);
	if (ret == 0) {
		_tprintf(_T("ReleaseMutex Error Occur ! \n"));
	}
}


// ���������������������������������������������������
// ������ Ǯ �Լ� ����
// ���������������������������������������������������
WORK GetWorkFromPool(void);
DWORD AddWorkToPool(WORK work);
DWORD MakeThreadToPool(DWORD numOfThread);
void WorkerThreadFunction(LPVOID pParam);


WORK GetWorkFromPool(void) {
	WORK work = NULL;

	// ���ؽ� ȹ��
	AcquireMutex();

	// ���� ó���ؾ��ϴ� WORK�� �������� ������ NULL ��ȯ
	if (!(gThreadPool.idxOfCurrentWork < gThreadPool.idxOfLastAddWork)) {
		// ���ؽ� ��ȯ
		ReleaseMutex();
		return NULL;
	}

	// ���� ó���ؾ��ϴ� WORK ��ȯ
	work = gThreadPool.workList[gThreadPool.idxOfCurrentWork++];

	// ���ؽ� ��ȯ
	ReleaseMutex();
	return work;
}


DWORD AddWorkToPool(WORK work) {
	// ���ؽ� ȹ��
	AcquireMutex();

	// �ִ� ��� ���� WORK ������ �ʰ��� ��� ��� �Ұ�
	if (gThreadPool.idxOfLastAddWork >= WORK_MAX) {
		_tprintf(_T("AddWorkToPool Fail : TOO BUSY~ \n"));
		return NULL;
	}

	// WORK ���
	// ���� �� ���� : �ִ� ��� ���� WORK ������ �ʰ��� ��� ��� �Ұ� => ���� ����Ʈ�� ���� �ʿ�
	gThreadPool.workList[gThreadPool.idxOfLastAddWork++] = work;

	// WORK ��� �� ��� ���� ��������� ��� ���� ���� ����
	// => ��� ���� �ʿ�� ���� ȿ���� ������
	for (DWORD i = 0; i < gThreadPool.threadIdx; i++) {
		SetEvent(gThreadPool.workerEventList[i]);
	}

	// ���ؽ� ��ȯ
	ReleaseMutex();
	return 1;
}


DWORD MakeThreadToPool(DWORD numOfThread) {
	// ���ؽ� �ʱ�ȭ
	InitMutex();

	// ���� ��� ������ WORK �뷮 ���
	DWORD capacity = WORK_MAX - (gThreadPool.threadIdx);

	// �뷮 �ʰ��� �ִ� �뷮���� �����ش�
	if (capacity < numOfThread) {
		numOfThread = capacity;
	}

	// numOfThread ��ŭ ������ ����
	for (DWORD i = 0; i < numOfThread; i++) {
		DWORD idThread;
		HANDLE hThread;

		// �����忡�� ���� ��ų �̺�Ʈ ������Ʈ ����
		gThreadPool.workerEventList[gThreadPool.threadIdx] 
			= CreateEvent(
				NULL,	// ��� �Ұ�
				FALSE,	// �ڵ� ���� ���
				FALSE,	// non-signaled ���·� ����
				NULL	// �̸� X
			);

		// ������ ����
		hThread = CreateThread(
			NULL,											// ����Ʈ ���� : �ڵ� ��� ���� ����
			0,												// ����Ʈ ���� ������
			(LPTHREAD_START_ROUTINE)WorkerThreadFunction,	// ������ ���� �Լ�
			(LPVOID)gThreadPool.threadIdx,					// ������ ���� �Լ� ���� ����
			0,												// ����Ʈ ���� �� ���� ���� �÷���
			&idThread										// ������ Id
		);
		
		// ������ Ǯ�� ������ �ڵ� �� id ���
		gThreadPool.workerThreadList[gThreadPool.threadIdx].hThread = hThread;
		gThreadPool.workerThreadList[gThreadPool.threadIdx].idThread = idThread;

		// ������ �ε��� ����
		gThreadPool.threadIdx++;
	}

	return numOfThread;
}

void WorkerThreadFunction(LPVOID pParam) {
	WORK workFunction;

	// pParam�� �ش��ϴ� �̺�Ʈ �ڵ� 
	HANDLE event = gThreadPool.workerEventList[(DWORD)pParam];

	// ������� �������� ���� �ٷ� Ȱ��ȭ ����
	// ���� ó���ؾ��ϴ� work�� �̺�Ʈ ������Ʈ�� ���� �ν��ϸ� ���� ����
	while (1) {
		// ���� ó���ؾ��ϴ� 1���� WORK ��ȯ
		workFunction = GetWorkFromPool();

		// ���� ó���ؾ��ϴ� WORK�� �������� ������
		if (workFunction == NULL) {
			// Work�� �Ҵ�� ������ �ش� ������ Blocked ����
			WaitForSingleObject(event, INFINITE);
			continue;
		}
		workFunction();
	}
}




// ���������������������������������������������������
// Test WORK function
// ���������������������������������������������������
static int countTestFunction = 0;
HANDLE testMutex;

void TestFunction() {
	WaitForSingleObject(testMutex, INFINITE);

	countTestFunction++;

	_tprintf(
		_T("Good Test -- %d : Processing thread : %d --\n\n"),
		countTestFunction, GetCurrentThreadId()
	);

	ReleaseMutex(testMutex);
}

int _tmain(int argc, TCHAR* argv[]) {

	testMutex = CreateMutex(
		NULL,		// ����Ʈ ����
		FALSE,		// ������ ������ �� �ִ� ����
		NULL		// �̸����� ���ؽ�
	);


	MakeThreadToPool(3);
	for (int i = 0; i < 100; i++) {
		AddWorkToPool(TestFunction);
	}
	
	// ���� ������ �Ҹ� ����
	Sleep(5000);
	
	CloseHandle(testMutex);
	return 0;
}





