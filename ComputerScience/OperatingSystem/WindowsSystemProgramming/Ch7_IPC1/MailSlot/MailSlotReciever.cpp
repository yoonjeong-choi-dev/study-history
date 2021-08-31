/*
< MailSlot Receiver >
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

	// 메일슬롯 핸들
	HANDLE hMailSlot;	
	// 메일슬롯을 통해 수신받을 메시지
	TCHAR messageBox[MESSAGE_SIZE];
	// 수신받은 메시지의 크기
	DWORD bytesRead;

	// Create MailSlot
	hMailSlot = CreateMailslot(
		MAIL_SLOT_NAME,			// 메일 슬롯 이름
		0,						// 메일슬롯의 버퍼 크기
		MAILSLOT_WAIT_FOREVER,	// 최대 블로킹 시간 : 버퍼에 데이터가 존재할 때까지 블로킹
		NULL					// 핸들 상속을 위한 용도
	);

	if (hMailSlot == INVALID_HANDLE_VALUE) {
		_fputts(_T("Unable to create mailslot\n"), stdout);
		return 1;
	}

	
	// Message Recieve
	_fputts(_T("************ Message ************\n"), stdout);

	while (1) {
		// ReadFile : 메일슬롯으로 전달된 데이터를 읽는 함수
		if (!ReadFile(hMailSlot, messageBox, sizeof(TCHAR)*MESSAGE_SIZE,
			&bytesRead, NULL)) {
			_fputts(_T("Unable to read \n"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}
			
		if (!_tcsncmp(messageBox, _T("exit"), 4)) {
			_fputts(_T("Good bye~\n"), stdout);
			break;
		}

		// Insert NULL
		messageBox[bytesRead / sizeof(TCHAR)] = 0;
		_fputts(messageBox, stdout);

	}
	
	CloseHandle(hMailSlot);

	return 0;
}


