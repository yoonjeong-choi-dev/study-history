/*
< 쓰레드 풀링 >
- 쓰레드의 생성과 소멸은 시스템에 부담을 준다
- 다수의 쓰레드를 미리 생성하고 필요할 때 꺼내 쓰는 개념
- 풀에 존재하는 쓰레드 수보다 처리해야 할 일이 많은 경우 처리하는 일을 분배하는 방법을 디자인 가능

< 구현 관련 >
- 최대 등록 가능 WORK는 10000개, 쓰레드 풀의 쓰레드 갯수는 50개
- WORK : 쓰레드가 수행하는 일은 void func(void) 형
- WorkerThread : 생성된 쓰레드의 정보를 담기 위한 구조체
- gThreadPool : 쓰레드 풀에 해당하는 자료구조
	- 전역 변수로 선언
	- WORK 관련 멤버 변수
		- WORK workList[WORK_MAX]	: WORK 대기열
		- DWORD idxOfCurrentWork	: 대기 1순위 WORK 인덱스
		- DWORD idxOfLastAddWork	: 마지막 추가된 WORK 인덱스
	- 쓰레드 관련 멤버 변수
		- WorkerThread workerThreadList[THREAD_MAX] : Thread 정보 
		- HANDLE workerEventList[THREAD_MAX]		: Thread별 Event 오브젝트
		- DWORD threadIdx							: 존재하는 Thread 갯수

< 쓰레드 풀 함수 관련 >
- WORK GetWorkFromPool(void)
	- 쓰레드 풀에서 WORK를 가져올 때 호출하는 함수
- DWORD AddWorkToPool(WORK work)
	- 새로운 WORK를 쓰레드 풀에 등록할 때 호출하는 함수
	- 구현 상 문제 : 최대 등록 가능 WORK 갯수를 초과한 경우 등록 불가 => 원형 리스트로 개선 필요
- DWORD MakeThreadToPool(DWORD numOfThread)
	- 쓰레드 풀이 생생된 이후 numOfThread 만큼 쓰레드를 생성하는 함수
- void WorkerThreadFunction(LPVOID pParam)
	- 쓰레드가 생성되자마자 호출하는 쓰레드의 main 함수

< 쓰레드 풀 동시 접근에 대한 동기화 - Mutex >
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




// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// 생성된 쓰레드의 정보를 담기 위한 구조체
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
typedef struct __WorkerThread {
	HANDLE hThread;
	DWORD idThread;
} WorkerThread;



// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// Work와 Thread 관리를 위한 구조체 : 전역 변수로 선언
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// 쓰레드가 수행하는 work 정의 : 쓰레드에게 일을 시키기 위한 작업의 기본 단위
typedef void(*WORK)(void);

struct __ThreadPool {
	// WORK를 등록하기 위한 배열
	WORK workList[WORK_MAX];

	// Thread 정보 
	WorkerThread workerThreadList[THREAD_MAX];
	// Thread별 Event 오브젝트 : 쓰레드에게 일을 시키기 위한 이벤트 오브젝트
	HANDLE workerEventList[THREAD_MAX];

	// WORK에 대한 정보 : 대기 1순위 및 마지막 추가된 WORK 인덱스
	DWORD idxOfCurrentWork;
	DWORD idxOfLastAddWork;

	// 쓰레드 풀에 존재하는 쓰레드 갯수
	DWORD threadIdx;
} gThreadPool;



// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// 쓰레드 풀 동시 접근에 대한 동기화 - Mutex
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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


// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// 쓰레드 풀 함수 관련
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
WORK GetWorkFromPool(void);
DWORD AddWorkToPool(WORK work);
DWORD MakeThreadToPool(DWORD numOfThread);
void WorkerThreadFunction(LPVOID pParam);


WORK GetWorkFromPool(void) {
	WORK work = NULL;

	// 뮤텍스 획득
	AcquireMutex();

	// 현재 처리해야하는 WORK가 존재하지 않으면 NULL 반환
	if (!(gThreadPool.idxOfCurrentWork < gThreadPool.idxOfLastAddWork)) {
		// 뮤텍스 반환
		ReleaseMutex();
		return NULL;
	}

	// 현재 처리해야하는 WORK 반환
	work = gThreadPool.workList[gThreadPool.idxOfCurrentWork++];

	// 뮤텍스 반환
	ReleaseMutex();
	return work;
}


DWORD AddWorkToPool(WORK work) {
	// 뮤텍스 획득
	AcquireMutex();

	// 최대 등록 가능 WORK 갯수를 초과한 경우 등록 불가
	if (gThreadPool.idxOfLastAddWork >= WORK_MAX) {
		_tprintf(_T("AddWorkToPool Fail : TOO BUSY~ \n"));
		return NULL;
	}

	// WORK 등록
	// 구현 상 문제 : 최대 등록 가능 WORK 갯수를 초과한 경우 등록 불가 => 원형 리스트로 개선 필요
	gThreadPool.workList[gThreadPool.idxOfLastAddWork++] = work;

	// WORK 등록 후 대기 중인 쓰레드들을 모두 깨워 일을 시작
	// => 모두 깨울 필요는 없어 효율성 떨어짐
	for (DWORD i = 0; i < gThreadPool.threadIdx; i++) {
		SetEvent(gThreadPool.workerEventList[i]);
	}

	// 뮤텍스 반환
	ReleaseMutex();
	return 1;
}


DWORD MakeThreadToPool(DWORD numOfThread) {
	// 뮤텍스 초기화
	InitMutex();

	// 현재 등록 가능한 WORK 용량 계산
	DWORD capacity = WORK_MAX - (gThreadPool.threadIdx);

	// 용량 초과면 최대 용량으로 맞춰준다
	if (capacity < numOfThread) {
		numOfThread = capacity;
	}

	// numOfThread 만큼 쓰레드 생성
	for (DWORD i = 0; i < numOfThread; i++) {
		DWORD idThread;
		HANDLE hThread;

		// 쓰레드에게 일을 시킬 이벤트 오브젝트 생성
		gThreadPool.workerEventList[gThreadPool.threadIdx] 
			= CreateEvent(
				NULL,	// 상속 불가
				FALSE,	// 자동 리셋 모드
				FALSE,	// non-signaled 상태로 생성
				NULL	// 이름 X
			);

		// 쓰레드 생성
		hThread = CreateThread(
			NULL,											// 디폴트 보안 : 핸들 상속 여부 결정
			0,												// 디폴트 스택 사이즈
			(LPTHREAD_START_ROUTINE)WorkerThreadFunction,	// 쓰레드 메인 함수
			(LPVOID)gThreadPool.threadIdx,					// 쓰레드 메인 함수 전달 인자
			0,												// 디폴트 생성 및 실행 조절 플래그
			&idThread										// 쓰레드 Id
		);
		
		// 쓰레드 풀에 쓰레드 핸들 및 id 등록
		gThreadPool.workerThreadList[gThreadPool.threadIdx].hThread = hThread;
		gThreadPool.workerThreadList[gThreadPool.threadIdx].idThread = idThread;

		// 쓰레드 인덱스 증가
		gThreadPool.threadIdx++;
	}

	return numOfThread;
}

void WorkerThreadFunction(LPVOID pParam) {
	WORK workFunction;

	// pParam에 해당하는 이벤트 핸들 
	HANDLE event = gThreadPool.workerEventList[(DWORD)pParam];

	// 쓰레드는 생성되자 마자 바로 활성화 상태
	// 현재 처리해야하는 work를 이벤트 오브젝트를 통해 인식하면 일을 시작
	while (1) {
		// 현재 처리해야하는 1순위 WORK 반환
		workFunction = GetWorkFromPool();

		// 현재 처리해야하는 WORK가 존재하지 않으면
		if (workFunction == NULL) {
			// Work가 할당될 때까지 해당 쓰레드 Blocked 상태
			WaitForSingleObject(event, INFINITE);
			continue;
		}
		workFunction();
	}
}




// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// Test WORK function
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
		NULL,		// 디폴트 보안
		FALSE,		// 누구나 소유할 수 있는 상태
		NULL		// 이름없는 뮤텍스
	);


	MakeThreadToPool(3);
	for (int i = 0; i < 100; i++) {
		AddWorkToPool(TestFunction);
	}
	
	// 메인 쓰레드 소멸 방지
	Sleep(5000);
	
	CloseHandle(testMutex);
	return 0;
}





