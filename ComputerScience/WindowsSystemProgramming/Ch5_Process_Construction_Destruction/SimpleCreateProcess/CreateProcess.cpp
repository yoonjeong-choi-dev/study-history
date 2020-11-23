// Header for Standard Programming
#include <stdio.h>

// Header for Windows System Programming
#include <tchar.h>
#include <Windows.h>




#define DIR_LEN MAX_PATH+1


int _tmain(int argc, TCHAR* argv[]) {
	// STARTUPINFO : 프로세스의 속성을 지정하기 위한 구조체
	STARTUPINFO si = { 0, };

	PROCESS_INFORMATION pi;

	// 프로세스 속성 지정
	// 구조체 변수 크기 : 확장성을 고려한 형식적인 설정
	si.cb = sizeof(si);

	// STARTF_USEPOISTION : dwX,dwY 참조해서 윈도우 위치 결정
	// STARTF_USESIZE : dwXSize, dwYSize 참조해서 윈도우 크기 결정
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 100; si.dwY = 200;			// 프로세스 윈도우 좌표
	si.dwXSize = 300; si.dwYSize = 200;	// 프로세스 윈도우 가로,세로 길이
	si.lpTitle = _T("I am a child");		// 프로세스 타이틀

	// 프로세스 실행 커맨드 설정
	TCHAR command[] = _T("AdderProcess.exe 10 20");
	TCHAR cDir[DIR_LEN];
	

	// 현재 디렉토리 확인
	GetCurrentDirectory(DIR_LEN, cDir);
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	// 현재 디렉토리 설정 : 자식 프로세스가 있는 디렉토리
	BOOL dirSetting;
	dirSetting = SetCurrentDirectory(_T("D:\\VisualStudio2015\\WinSystem"));

	if (dirSetting != 0) {
		_fputts(_T("SetCurrentDirectory OK!\n"), stdout);
	}
	else {
		_fputts(_T("SetCurrentDirectory ERROR!\n"), stdout);
	}

	// 현재 디렉토리 확인
	GetCurrentDirectory(DIR_LEN, cDir);
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	BOOL state;
	state = CreateProcess(
		NULL,				// 프로세스 경로 설정( NULL: 현재 디렉토리)
		command,			// 프로세스 실행을 위한 커맨드
		NULL, NULL, TRUE,	// 보안속성, 쓰레드, 핸들 상속 여부
		CREATE_NEW_CONSOLE,	// 생성 프로세스의 특성(우선순위) 결정 옵션 : 현재는 콘솔 기반으로 생성
		NULL, NULL,			// 메모리 블록 관리, 생성 프로세스 디렉토리
		&si,				// 생성 프로세스 속성 결정
		&pi					// 생성하는 프로세스 정보 받아오기
	);

	if (state != 0) {
		_fputts(_T("Creation OK!\n"), stdout);
	}
	else {
		_fputts(_T("Creation ERROR!\n"), stdout);
	}

	return 0;
}



