/*


*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <locale.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>




// 쓰레드의 main 함수
DWORD WINAPI ThreadMain(LPVOID lpParam) {
	// 배열의 인접한 두 요소와 그 사이의 숫자들을 더하여 반환
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


	// 쓰레드 3개 생성 : [1,3], [4,7], [8, 10] 에 대한 연산
	hThread[0] = CreateThread(
		NULL,					// 디폴트 보안 : 핸들 상속 여부 결정
		0,						// 디폴트 스택 사이즈
		ThreadMain,				// 쓰레드 메인 함수
		(LPVOID)(&paramThread[0]),	// 쓰레드 메인 함수 전달 인자
		0,						// 디폴트 생성 및 실행 조절 플래그
		&dwThreadId[0] //쓰레드 Id
	);

	hThread[1] = CreateThread(
		NULL,					// 디폴트 보안 : 핸들 상속 여부 결정
		0,						// 디폴트 스택 사이즈
		ThreadMain,				// 쓰레드 메인 함수
		(LPVOID)(&paramThread[2]),	// 쓰레드 메인 함수 전달 인자
		0,						// 디폴트 생성 및 실행 조절 플래그
		&dwThreadId[1] //쓰레드 Id
	);

	hThread[2] = CreateThread(
		NULL,					// 디폴트 보안 : 핸들 상속 여부 결정
		0,						// 디폴트 스택 사이즈
		ThreadMain,				// 쓰레드 메인 함수
		(LPVOID)(&paramThread[4]),	// 쓰레드 메인 함수 전달 인자
		0,						// 디폴트 생성 및 실행 조절 플래그
		&dwThreadId[2] //쓰레드 Id
	);

	// 쓰레드 생성 실패시 
	for (DWORD i = 0; i < 3; i++) {
		if (hThread[i] == NULL) {
			_tprintf(_T("%d th Thread creation fault! \n"), i);
			return -1;
		}
	}
	
	// 각 쓰레드가 연산을 모두 수행할 때까지 기다린다
	WaitForMultipleObjects(
		3,			// 기다릴 쓰레드의 갯수
		hThread,	// 핸들의 배열 정보
		TRUE,		// 모든 커널 오브젝트의 상태가 signaled가 될때까지 
		INFINITE	// 영원히 기다린다
	);


	// 결과 코드를 이용한 연산
	for (DWORD i = 0; i < 3; i++) {
		GetExitCodeThread(hThread[i], &result);
		total += result;
	}

	_tprintf(_T("total (1 ~ 10) : %d \n"), total);

	// 쓰레드 핸들 해제
	for (DWORD i = 0; i < 3; i++) {
		CloseHandle(hThread[i]);
	}

	return 0;
}





