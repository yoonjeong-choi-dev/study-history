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

	// ���Ͻ��� �ڵ�
	HANDLE hMailSlot;	
	// ���Ͻ����� ���� ���Ź��� �޽���
	TCHAR messageBox[MESSAGE_SIZE];
	// ���Ź��� �޽����� ũ��
	DWORD bytesRead;

	// Create MailSlot
	hMailSlot = CreateMailslot(
		MAIL_SLOT_NAME,			// ���� ���� �̸�
		0,						// ���Ͻ����� ���� ũ��
		MAILSLOT_WAIT_FOREVER,	// �ִ� ���ŷ �ð� : ���ۿ� �����Ͱ� ������ ������ ���ŷ
		NULL					// �ڵ� ����� ���� �뵵
	);

	if (hMailSlot == INVALID_HANDLE_VALUE) {
		_fputts(_T("Unable to create mailslot\n"), stdout);
		return 1;
	}

	
	// Message Recieve
	_fputts(_T("************ Message ************\n"), stdout);

	while (1) {
		// ReadFile : ���Ͻ������� ���޵� �����͸� �д� �Լ�
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


