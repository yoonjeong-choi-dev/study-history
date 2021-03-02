/*
< Event+Mutex 에 대한 이해 - 생산자/소비자 모델 >
- 생산자 쓰레드 : 외부에서 문자열을 입력받아 저장(메인 쓰레드)
- 소비자 쓰레드1 : 저장된 문자열을 화면에 출력
- 소비자 쓰레드2 : 저장된 문자열의 길이를 화면 출력
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <process.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>



// 생산자/소비자 모델을 구성하는 문자열 배열과 이 배열에 접근하는 이벤트 및 뮤텍스에 대한 구조체
typedef struct _SynchString {
	TCHAR string[100];
	HANDLE hEvent;
	HANDLE hMutex;
} SynchString;

SynchString gSync;

// 소비자 쓰레드1 메인 함수
unsigned int WINAPI ConsumerThreadFunction_Print(LPVOID lpParam) {
	// event signaled 상태가 될 때까지 대기
	WaitForSingleObject(gSync.hEvent, INFINITE);

	// mutex를 얻어 임계영역 접근
	WaitForSingleObject(gSync.hMutex, INFINITE);

	// 임계 영역
	_fputts(_T("Output string : "), stdout);
	_fputts(gSync.string, stdout);

	// mutex 반환
	ReleaseMutex(gSync.hMutex);

	return 0;
}

// 소비자 쓰레드2 메인 함수
unsigned int WINAPI ConsumerThreadFunction_Count(LPVOID lpParam) {
	// event signaled 상태가 될 때까지 대기
	WaitForSingleObject(gSync.hEvent, INFINITE);

	// mutex를 얻어 임계영역 접근
	WaitForSingleObject(gSync.hMutex, INFINITE);

	// 임계 영역
	_tprintf(
		_T("Output string length : %d \n"),
		_tcslen(gSync.string) - 1
	);

	// mutex 반환
	ReleaseMutex(gSync.hMutex);

	return 0;
}


int _tmain(int argc, TCHAR* argv[]) {

	HANDLE hThread[2];
	DWORD dwThreadId[2];

	// Event 오브젝트 생성
	gSync.hEvent = CreateEvent(
		NULL,		// 상속 불가
		TRUE,		// 자동 리셋 모드
		FALSE,		// non-signaled 상태로 생성
		NULL		// 이름 X
	);


	// Mutex 오브젝트 생성
	gSync.hMutex = CreateMutex(
		NULL,		// 디폴트 보안
		FALSE,		// 누구나 소유할 수 있는 상태
		NULL		// 이름없는 뮤텍스
	);

	if (gSync.hEvent == NULL || gSync.hMutex == NULL) {
		_fputts(_T("Kernel object Creation Error \n"), stdout);
		return -1;
	}

	// 소비자 쓰레드 생성
	hThread[0] = (HANDLE)_beginthreadex(
		NULL,							// 디폴트 보안 : 핸들 상속 여부 결정
		0,								// 디폴트 스택 사이즈
		ConsumerThreadFunction_Print,	// 쓰레드 메인 함수
		NULL,							// 쓰레드 메인 함수 전달 인자
		0,								// 디폴트 생성 및 실행 조절 플래그
		(unsigned*)&dwThreadId[0]		// 쓰레드 Id
	);

	hThread[1] = (HANDLE)_beginthreadex(
		NULL,							// 디폴트 보안 : 핸들 상속 여부 결정
		0,								// 디폴트 스택 사이즈
		ConsumerThreadFunction_Count,	// 쓰레드 메인 함수
		NULL,							// 쓰레드 메인 함수 전달 인자
		0,								// 디폴트 생성 및 실행 조절 플래그
		(unsigned*)&dwThreadId[1]		// 쓰레드 Id
	);

	if (hThread[0] == NULL || hThread[1] ==NULL) {
		_fputts(_T("Thread Creation Error \n"), stdout);
		return -1;
	}


	// 메인 쓰레드 : 생산자 역할
	_fputts(_T("Insert string : "), stdout);
	_fgetts(gSync.string, 30, stdin);

	// Event 상태 signaled로 변경 : 문자열 생산(입력) 완료
	SetEvent(gSync.hEvent);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	// 리소스 해제
	CloseHandle(gSync.hEvent);
	CloseHandle(gSync.hMutex);
	CloseHandle(hThread[0]); CloseHandle(hThread[1]);

	system("pause");
	return 0;
}





