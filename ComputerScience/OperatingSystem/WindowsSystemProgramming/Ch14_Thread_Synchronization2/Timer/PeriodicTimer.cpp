/*
< 주기적 타이머 >
*/

// SetWaitableTimer 함수 호출을 하기 위해서는 Windows NT 이상에서 제공
// Windows NT 이상에서 실행시키기 위한 매크로
#define _WIN32_WINNT 0x0400


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <process.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>



int _tmain(int argc, TCHAR* argv[]) {

	HANDLE hTimer = NULL;
	
	LARGE_INTEGER liDueTime;
	// - : 상대 시간 => 지금부터 1초 후
	liDueTime.QuadPart = -10000000;	

	// 타이머 오브젝트 생성
	hTimer = CreateWaitableTimer(
		NULL,				// 보안 속성 지정
		FALSE,				// 자동 리셋 모드
		_T("WaitableTimer")	// 타이머 이름 부여
	);

	if (!hTimer) {
		_tprintf(
			_T("CreateWaitableTimer Failed : %d \n"),
			GetLastError()
		);
		return 1;
	}

	_tprintf(_T("Waiting for 1 seconds....\n"));

	// 타이머 알람 설정
	SetWaitableTimer(
		hTimer,		// 타이머 오브젝트의 핸들
		&liDueTime,	// 알람이 울리는 시간 : 음수인경우 상대 시간
		5000,		// 타이머 주기 설정 : 5초
		NULL,		// 완료 루틴 타이머 생성 관련
		NULL,		// 완료 루틴 타이머 생성 관련
		FALSE		// 전원 관리 관련 매개 변수
	);

	// 타이머 알람 대기
	while (1) {
		WaitForSingleObject(hTimer, INFINITE);
		_tprintf(_T("Timer was Signaled! \n"));
		MessageBeep(MB_ICONEXCLAMATION);
	}
	
	
	return 0;
}





