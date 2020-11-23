/*
< Named Pipe Client >
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 1024




int _tmain(int argc, TCHAR* argv[]) {

	LPTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;
	TCHAR readDataBuf[BUFF_SIZE + 1];

	while (1) {
		// CreateFile : 클라이언트 영역에서 서버 파이프로의 연결 요청 기능
		hPipe = CreateFile(
			pipeName,						// 연결 파이프 이름
			GENERIC_READ | GENERIC_WRITE,	// 파일 개방 모드 : 읽기쓰기모드
			0,
			NULL,
			OPEN_EXISTING,					// 파일 생성 방식 : 기존 존재 파일 열기
			0,
			NULL
		);


		// CreateFile로 핸들이 제대로 만들어진 경우
		//  - 서버 파이프와 연결된 것으로 간주
		if (hPipe != INVALID_HANDLE_VALUE) {
			break;
		}

		// ERROR_PIPE_BUSY : 여분의 파이프가 없어 서버 파이프가 연결을 수락하려면 시간이 필요한 상황
		// GetLastError() != ERROR_PIPE_BUSY : 연결 실패
		if (GetLastError() != ERROR_PIPE_BUSY) {
			_tprintf(_T("GetLastError() != ERROR_PIPE_BUSY : Could not open pipe \n"));
			system("pause");
			return 0;
		}

		// GetLastError() == ERROR_PIPE_BUSY : 최대한 기다려준다
		// 20000ms 가 지난 경우 실패로 간주
		if (!WaitNamedPipe(pipeName, 20000)) {
			_tprintf(_T("!WaitNamedPipe(pipeName, 20000) : Could not open pipe \n"));
			system("pause");
			return 0;
		}
	}

	// 연결된 파이프에서의 작업
	// 파이프 모드 : 메시지 기반
	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT;

	// 파이프와 연결시 파일 관련 함수인 CreateFile 함수 사용 : 설정에 필요한 정보(파이프 모드)를 그대로 반영 불가능
	// => SetNamedPipeHandleState 함수를 통해 파이프와의 연결 속성을 변경시키는 추가 작업
	BOOL isSuccess = SetNamedPipeHandleState(
		hPipe,
		&pipeMode,
		NULL,
		NULL
	);

	if (!isSuccess) {
		_tprintf(_T("SetNamedPipeHandleState failed \n"));
		return 0;
	}

	// 서버로 전송할 파일 이름
	LPCTSTR fileName = _T("news.txt");
	DWORD bytesWritten = 0;
	isSuccess = WriteFile(
		hPipe,										// 서버 파이프와 연결된 핸들
		fileName,									// 전송할 메시지
		(_tcslen(fileName) + 1) * sizeof(TCHAR),	// 전송 메시지 길이
		&bytesWritten,								// 전송된 바이트 크기
		NULL
	);

	if (!isSuccess) {
		_tprintf(_T("WriteFile failed \n"));
		system("pause");
		return 0;
	}

	DWORD bytesRead = 0;
	while (1) {
		isSuccess = ReadFile(
			hPipe,						// 서버 파이프와 연결된 핸들
			readDataBuf,				// 데이터 수신용 버퍼
			BUFF_SIZE * sizeof(TCHAR),	// 버퍼 사이즈
			&bytesRead,					// 수신받은 데이터 크기
			NULL
		);

		if (!isSuccess && GetLastError() != ERROR_MORE_DATA) {
			break;
		}

		readDataBuf[bytesRead] = 0;		// 널문자 삽입
		_tprintf(_T("%s \n"), readDataBuf);
	}

	CloseHandle(hPipe);
	system("pause");
	return 0;
}


