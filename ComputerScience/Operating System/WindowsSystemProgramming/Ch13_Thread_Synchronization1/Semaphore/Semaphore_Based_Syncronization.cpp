/*
< 카운트 세마포어 에 대한 이해 - 시뮬레이션 >
- 테이블이 총 10개이고, 동시에 총 10명의 손님만 받는다
- 손님 예상 수는 50명
- 각 손님의 식사 시간은 10~30분 사이
- 손님 <=> 쓰레드, 테이블 <=> 세마포어 열쇠 갯수
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

// 세마포어 핸들
HANDLE hSemaphore;

// 각 손님의 식사 시간
DWORD randTimeArr[NUM_OF_CUSTOMERS];


// 손님의 식사 시간
void TakeMeal(DWORD time) {

	// Step 2 : 세마 포어에 대한 열쇠 획득 : 테이블 입장
	WaitForSingleObject(hSemaphore, INFINITE);

	// 임계 영역 : 몇 번째 손님(쓰레드)이 음식을 먹는지 출력
	_tprintf(_T("Enter %d Customer\n"), GetCurrentThreadId());
	_tprintf(_T("Customer %d  Having Lauch \n"), GetCurrentThreadId());
	Sleep(1000 * time);
	
	// Step 3 : 세마 포어에 대한 열쇠 반환(카운트 -1) : 테이블 퇴장
	ReleaseSemaphore(hSemaphore, 1, NULL);
	_tprintf(_T("Leave %d Customer \n"), GetCurrentThreadId());
}


// 쓰레드의 main 함수 : IncreseGlobalCount를 1000번 호출
// _beginthreadex를 사용하기 때문에 반환형을 unsigned int로 한다
unsigned int WINAPI ThreadMain(LPVOID lpParam) {

	TakeMeal((DWORD)lpParam);
	return 0;
}


int _tmain(int argc, TCHAR* argv[]) {

	DWORD dwThreadId[NUM_OF_CUSTOMERS];
	HANDLE hThread[NUM_OF_CUSTOMERS];

	// 손님의 식사 시간 랜덤 할당
	srand((unsigned)time(NULL));
	for (int i = 0; i < NUM_OF_CUSTOMERS; i++) {
		randTimeArr[i] = (DWORD)(
			((double)rand() / (double)RAND_MAX) * RANGE_MAX + RANGE_MIN
			);
	}

	// Step 1 : 세마포어 오브젝트 초기화
	hSemaphore = CreateSemaphore(
		NULL,			// 디폴트 보안
		NUM_OF_TABLES,	// 세마 포어 카운트 초기값
		NUM_OF_TABLES,	// 세마 포어 카운트 최대값
		NULL			// 이름없는 세마포어
	);

	if (hSemaphore == NULL) {
		_tprintf(_T("CreateSemaphore Err : %d \n"), GetLastError());
	}


	_tprintf(_T("====================== START ======================\n"));

	// NUM_OF_CUSTOMERS 수 만큼 쓰레드 생성
	for (DWORD i = 0; i < NUM_OF_CUSTOMERS; i++) {
		hThread[i] = (HANDLE) _beginthreadex(
			NULL,						// 디폴트 보안 : 핸들 상속 여부 결정
			0,							// 디폴트 스택 사이즈
			ThreadMain,					// 쓰레드 메인 함수
			(void*)randTimeArr[i],		// 쓰레드 메인 함수 전달 인자
			CREATE_SUSPENDED,			// 디폴트 생성 및 실행 조절 플래그 : 바로 실행 x, ResumeThread를 호출하여 실행
			(unsigned*)&dwThreadId[i]	// 쓰레드 Id
		);

		if (hThread[i] == NULL) {
			_tprintf(_T("%d th Thread creation fault! \n"), i);
			return -1;
		}
	}

	// 쓰레드 실행 : 쓰레드를 생성하는데 시간이 걸리기 때문에 생성 후 실행시키기 위한 절차
	for (DWORD i = 0; i < NUM_OF_CUSTOMERS; i++) {
		ResumeThread(hThread[i]);
	}

	// 모든 쓰레드가 실행될 때 까지 기다려준다
	WaitForMultipleObjects(NUM_OF_CUSTOMERS, hThread, TRUE, INFINITE);


	_tprintf(_T("====================== END ======================\n"));

	// 쓰레드 핸들 해제
	for (DWORD i = 0; i < NUM_OF_CUSTOMERS; i++) {
		CloseHandle(hThread[i]);
	}

	// Step 4 : 뮤텍스 오브젝트 리소스 해제
	CloseHandle(hSemaphore);


	return 0;
}





