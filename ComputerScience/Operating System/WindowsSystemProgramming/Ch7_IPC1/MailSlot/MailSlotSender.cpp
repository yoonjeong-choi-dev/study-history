/*
< MailSlot Sender >
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

	// CreateFile : 특정 메일슬롯 주소로 전달할 데이터 스트림 생성
	hMailSlot = CreateFile(
		MAIL_SLOT_NAME,			// 생성 및 개방하고자 하는 파일 이름 지정
		GENERIC_WRITE,			// 패일의 개방 모드 지정 : 쓰기모드
		FILE_SHARE_READ,		
		NULL,
		OPEN_EXISTING,			// 패일의 생성방식 지정 : 이미 생성된 메일슬롯을 여는 것
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hMailSlot == INVALID_HANDLE_VALUE) {
		_fputts(_T("Unable to create MailSlot Stream\n"), stdout);
		return 1;
	}

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


