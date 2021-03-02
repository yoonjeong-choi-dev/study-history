/*
< Named Pipe Server >
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

int CommunicateToClient(HANDLE);



int _tmain(int argc, TCHAR* argv[]) {

	LPTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;

	// 한 스텝 당 한 클라이언트와만 통신 가능
	while (1) {
		hPipe = CreateNamedPipe(
			pipeName,					// 파이프 이름
			PIPE_ACCESS_DUPLEX,			// 읽기, 쓰기 모드 지정 : 읽기,쓰기 모두 가능 i.e 양방향
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE
			| PIPE_WAIT,				// 전송 및 수신 : 메시지 기반
			PIPE_UNLIMITED_INSTANCES,	// 최대 파이프 개수 : 시스템 리소스 최대한
			BUFF_SIZE,					// 출력 버퍼 사이즈
			BUFF_SIZE,					// 입력 버퍼 사이즈
			20000,						// 클라이언트 타임아웃
			NULL						// 디폴트 보안 속성
		);

		if (hPipe == INVALID_HANDLE_VALUE) {
			_tprintf(_T("Create NamedPipe Error"));
			return -1;
		}

		BOOL isSuccess = FALSE;
		// 클라이언트의 연결 요청 수락
		// 수락 실패인 경우 GetLastError() == ERROR_PIPE_CONNECTED 대입
		// GetLastError() == ERROR_PIPE_CONNECTED : 연결 요청이 없는 경우
		isSuccess =
			ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (isSuccess) {
			CommunicateToClient(hPipe);
		}
		else {
			CloseHandle(hPipe);
		}
	}


	return 0;
}

int CommunicateToClient(HANDLE hPipe) {
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUFF_SIZE];

	BOOL isSuccess;
	DWORD fileNameSize;
	isSuccess = ReadFile(
		hPipe,						// 파이프 핸들
		fileName,					// read 버퍼 지정
		MAX_PATH * sizeof(TCHAR),	// read 버퍼 사이즈
		&fileNameSize,				// 수신한 데이터 사이즈
		NULL
	);

	if (!isSuccess || fileNameSize == 0) {
		_tprintf(_T("Pipe read message ERROR\n"));
		return -1;
	}

	FILE* filePtr = _tfopen(fileName, _T("r"));
	if (filePtr == NULL) {
		_tprintf(_T("File open fault! \n"));
		_tprintf(_T("File name : %s \n"), fileName);
		return -1;
	}

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;

	// 클라이언트에서 보낸 파일 이름을 통해 파일의 내용을 읽어오는 작업
	while (!feof(filePtr)) {
		// 버프 사이즈만큼 파일에서 데이터를 읽어 dataBuf에 저장
		bytesRead = fread(dataBuf, 1, BUFF_SIZE, filePtr);

		WriteFile(
			hPipe,			// 파이프 핸들
			dataBuf,		// 전송할 데이터 버퍼
			bytesRead,		// 데이터 버퍼 사이즈
			&bytesWritten,	// 전송된 데이터 사이즈
			NULL
		);

		// 마지막 데이터가 버퍼에 저장된 경우 끝
		if (bytesRead != bytesWritten) {
			_tprintf(_T("Pipe write message error \n"));
			break;
		}
	}

	// 출력 버퍼를 비우는 역할 : 목적지로의 전송을 으미
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}


