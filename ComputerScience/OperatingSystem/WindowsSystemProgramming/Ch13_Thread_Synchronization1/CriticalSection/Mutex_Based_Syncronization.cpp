/*
< Critical Section 에 대한 이해 >
- 6개의 쓰레드
- 쓰레드들은 gTotalCount 라는 전역 변수를 공유하여 접근

< Method : 뮤텍스 기반 동기화 >
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

// 뮤텍스 핸들 정보
HANDLE hMutex;

// 쓰레드에서 호출하는 함수로 전역 변수를 +1 한다
void IncreseGlobalCount() {

	// Step 2 : 열쇠 획득
	// 뮤텍스가 signaled 상태가 될 때 까지 대기
	WaitForSingleObject(hMutex, INFINITE);

	// 임계 영역
	gTotalCount++;	

	// Step 3 : 열쇠 반환
	// WaitForSingleObject 종료시 뮤텍스는 non-signaled 상태이기 때문에 siganled로 바꿔줘야 함
	// WaitForSingleObject의 되돌림 특성 때문에
	ReleaseMutex(hMutex);

}

// 쓰레드의 main 함수 : IncreseGlobalCount를 1000번 호출
// _beginthreadex를 사용하기 때문에 반환형을 unsigned int로 한다
unsigned int WINAPI ThreadMain(LPVOID lpParam) {

	for (DWORD i = 0; i < 1000; i++) {
		IncreseGlobalCount();
	}

	return 0;
}


int _tmain(int argc, TCHAR* argv[]) {

	DWORD dwThreadId[NUM_OF_GATE];
	HANDLE hThread[NUM_OF_GATE];

	// Step 1 : 뮤텍스 오브젝트 초기화
	hMutex = CreateMutex(
		NULL,		// 디폴트 보안
		FALSE,		// 누구나 소유할 수 있는 상태
		NULL		// 이름없는 뮤텍스
	);

	// NUM_OF_GATE 수 만큼 쓰레드 생성
	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		hThread[i] = (HANDLE) _beginthreadex(
			NULL,						// 디폴트 보안 : 핸들 상속 여부 결정
			0,							// 디폴트 스택 사이즈
			ThreadMain,					// 쓰레드 메인 함수
			NULL,						// 쓰레드 메인 함수 전달 인자
			CREATE_SUSPENDED,			// 디폴트 생성 및 실행 조절 플래그 : 바로 실행 x, ResumeThread를 호출하여 실행
			(unsigned*)&dwThreadId[i]	// 쓰레드 Id
		);

		if (hThread[i] == NULL) {
			_tprintf(_T("%d th Thread creation fault! \n"), i);
			return -1;
		}
	}

	// 쓰레드 실행 : 쓰레드를 생성하는데 시간이 걸리기 때문에 생성 후 실행시키기 위한 절차
	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		ResumeThread(hThread[i]);
	}

	// 모든 쓰레드가 실행될 때 까지 기다려준다
	WaitForMultipleObjects(NUM_OF_GATE, hThread, TRUE, INFINITE);

	// 결과 출력
	_tprintf(_T("Total Count : %d \n"), gTotalCount);


	// 쓰레드 핸들 해제
	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		CloseHandle(hThread[i]);
	}

	// Step 4 : 뮤텍스 오브젝트 리소스 해제
	CloseHandle(hMutex);


	return 0;
}





