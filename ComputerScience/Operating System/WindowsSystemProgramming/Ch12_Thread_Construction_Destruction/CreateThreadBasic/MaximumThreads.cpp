/*
[ Prompt Project ]

*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <locale.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>


#define MAX_THREADS (1024*10)

// 쓰레드의 main 함수
DWORD WINAPI ThreadMain(LPVOID lpParam) {
	DWORD threadNum = (DWORD)lpParam;

	while (1) {
		_tprintf(_T("Thread num : %d \n"), threadNum);
		Sleep(5000);
	}
	return 0;
}


DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[]) {

	DWORD dwThreadId[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	// 생성 가능한 최대 개수의 쓰레드 생성
	while (1) {

		// 쓰레드 생성 요청
		hThread[cntOfThread] = CreateThread(
			NULL,					// 디폴트 보안 : 핸들 상속 여부 결정
			0,						// 디폴트 스택 사이즈
			ThreadMain,				// 쓰레드 메인 함수
			(LPVOID)cntOfThread,	// 쓰레드 메인 함수 전달 인자
			0,						// 디폴트 생성 및 실행 조절 플래그
			&dwThreadId[cntOfThread] //쓰레드 Id
		);

		// 쓰레드 생성 확인
		if (hThread	[cntOfThread] == NULL) {
			_tprintf(_T("MAXIMUM THREAD NUMBER : %d \n"), cntOfThread);
			break;
		}
		else {
			cntOfThread++;
		}
	}

	// 쓰레드 핸들 해제
	for (DWORD i = 0; i < cntOfThread; i++) {
		CloseHandle(hThread[i]);
	}

	return 0;
}





