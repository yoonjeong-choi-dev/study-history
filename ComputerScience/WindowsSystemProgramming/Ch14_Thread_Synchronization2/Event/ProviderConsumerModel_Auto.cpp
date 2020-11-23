/*
< Event 에 대한 이해 - 생산자/소비자 모델 >
- 생산자 쓰레드 : 외부에서 문자열을 입력받아 저장(메인 쓰레드)
- 소비자 쓰레드 : 저장된 문자열을 화면에 출력
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <process.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>

// 생산자 쓰레드가 생산하고 소비자 쓰레드가 소비하는 문자열
TCHAR string[100];
HANDLE hEvent;

// 소비자 쓰레드 메인 함수
unsigned int WINAPI ConsumerThreadFunction(LPVOID lpParam) {
	// event가 signaled 상태가 될 때까지 대기
	WaitForSingleObject(hEvent, INFINITE);

	_fputts(_T("Output string : "), stdout);
	_fputts(string, stdout);

	return 0;
}



int _tmain(int argc, TCHAR* argv[]) {

	HANDLE hThread;
	DWORD dwThreadId;

	// Event 오브젝트 생성
	hEvent = CreateEvent(
		NULL,		// 상속 불가
		TRUE,		// 자동 리셋 모드
		FALSE,		// non-signaled 상태로 생성
		NULL		// 이름 X
	);

	if (hEvent == NULL) {
		_fputts(_T("Event object Creation Error \n"), stdout);
		return -1;
	}

	// 소비자 쓰레드 생성
	hThread = (HANDLE)_beginthreadex(
		NULL,						// 디폴트 보안 : 핸들 상속 여부 결정
		0,							// 디폴트 스택 사이즈
		ConsumerThreadFunction,		// 쓰레드 메인 함수
		NULL,						// 쓰레드 메인 함수 전달 인자
		0,							// 디폴트 생성 및 실행 조절 플래그
		(unsigned*)&dwThreadId		// 쓰레드 Id
	);

	if (hThread == NULL) {
		_fputts(_T("Thread Creation Error \n"), stdout);
		return -1;
	}


	// 메인 쓰레드 : 생산자 역할
	_fputts(_T("Insert string : "), stdout);
	_fgetts(string, 30, stdin);

	// Event 상태 signaled로 변경 : 문자열 생산(입력) 완료
	SetEvent(hEvent);

	WaitForSingleObject(hThread, INFINITE);

	// 리소스 해제
	CloseHandle(hEvent);
	CloseHandle(hThread);

	system("pause");
	return 0;
}





