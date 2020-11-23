/*
< Named Mutex 에 대한 이해 - 프로세스 간 쓰레드 동기화 >
- 
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <process.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>


HANDLE hMutex;
DWORD dwWaitResult;

#define CREATE_MUTEX 1
#define OPEN_MUTEX 0


// 프로세스 간 접근할 임계 영역
void PrcessBaseCriticalSection() {
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	// WaitForSingleObject의 반환 값에 따라 처리
	switch (dwWaitResult) {
	case WAIT_OBJECT_0:
		// 해당 쓰레드가 뮤텍스 소유
		_tprintf(_T("This thread got mutex ! \n"));
		break;
	case WAIT_TIMEOUT:
		// 타임 아웃 발생
		_tprintf(_T("Timer expired ! \n"));
		break;
	case WAIT_ABANDONED:
		// 뮤텍스의 반환이 제대로 실행되지 않은 경우
		_tprintf(_T("Mutex is not returned - WAIT_ABANDONED \n"));
		break;
	}

	for (DWORD i = 0; i < 5; i++) {
		_tprintf(_T("Thread Running ! \n"));
		Sleep(1000);
	}

	// 뮤텍스 반환
	ReleaseMutex(hMutex);
}


int _tmain(int argc, TCHAR* argv[]) {

// 조건부 컴파일
#if OPEN_MUTEX
	// 뮤텍스 생성
	hMutex = CreateMutex(
		NULL,				// 디폴트 보안
		FALSE,				// 누구나 소유할 수 있는 상태
		_T("NamedMutex")	// NamedMutex 이름 부여
	);
#else
	// 뮤텍스 가져오기
	hMutex = OpenMutex(
		MUTEX_ALL_ACCESS,	// 접근 권한 요청
		FALSE,				// 핸들 상속 X
		_T("NamedMutex")
	);

#endif

	if (hMutex == NULL) {
		_tprintf(_T("CreateMutex Error : %d \n"), GetLastError());
		return -1;
	}

	PrcessBaseCriticalSection();

	CloseHandle(hMutex);

	system("pause");
	return 0;
}





