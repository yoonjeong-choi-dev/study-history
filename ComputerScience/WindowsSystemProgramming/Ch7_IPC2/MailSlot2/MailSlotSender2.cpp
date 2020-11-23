/*
< MailSlot Sender >
- Parent Process
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>

#define MAIL_SLOT_NAME _T("\\\\.\\mailslot\\mailbox")
#define MESSAGE_SIZE 50


int _tmain(int argc, TCHAR* argv[]) {

	HANDLE hMailSlot;
	TCHAR message[MESSAGE_SIZE];
	DWORD bytesWritten;

	// SECURITY_ATTRIBUTES : 핸들 상속 관련 구조체
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);		// 구조체 변수 크기 
	sa.lpSecurityDescriptor = NULL;	// 핸들 상속 관점에서는 의미가 없음
	sa.bInheritHandle = TRUE;		// 해당 핸들의 상속 여부 결정

	// CreateFile : 특정 메일슬롯 주소로 전달할 데이터 스트림 생성
	hMailSlot = CreateFile(
		MAIL_SLOT_NAME,			// 생성 및 개방하고자 하는 파일 이름 지정
		GENERIC_WRITE,			// 패일의 개방 모드 지정 : 쓰기모드
		FILE_SHARE_READ,
		&sa,
		OPEN_EXISTING,			// 패일의 생성방식 지정 : 이미 생성된 메일슬롯을 여는 것
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hMailSlot == INVALID_HANDLE_VALUE) {
		_fputts(_T("Unable to create MailSlot Stream\n"), stdout);
		return 1;
	}


	// 메일슬롯의 핸들 정보 출력 및 저장
	_tprintf(_T("Inheritable Handle : %d \n"), hMailSlot);
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("wt"));
	_ftprintf(file, _T("%d"), hMailSlot);
	fclose(file);

	// 자식 프로세스 생성
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("MailSlotSenderChild.exe");

	CreateProcess(
		NULL, command,
		NULL, NULL,
		TRUE,		// 핸들 테이블 상속 결정
		CREATE_NEW_CONSOLE,
		NULL, NULL,
		&si, &pi
	);
	

	while (1) {
		_fputts(_T("MY MESSAGE >> "), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

		// WriteFile : 메일 슬롯의 핸들을 이용하여 메시지 전달
		if (!WriteFile(hMailSlot, message,
			_tcslen(message) * sizeof(TCHAR), &bytesWritten, NULL)) {
			_fputts(_T("Unable to write!\n"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		if (!_tcscmp(message, _T("exit"))) {
			_fputts(_T("Good Bye~ \n"), stdout);
			break;
		}

	}

	CloseHandle(hMailSlot);

	return 0;
}


