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

	// CreateFile : Ư�� ���Ͻ��� �ּҷ� ������ ������ ��Ʈ�� ����
	hMailSlot = CreateFile(
		MAIL_SLOT_NAME,			// ���� �� �����ϰ��� �ϴ� ���� �̸� ����
		GENERIC_WRITE,			// ������ ���� ��� ���� : ������
		FILE_SHARE_READ,		
		NULL,
		OPEN_EXISTING,			// ������ ������� ���� : �̹� ������ ���Ͻ����� ���� ��
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

		// WriteFile : ���� ������ �ڵ��� �̿��Ͽ� �޽��� ����
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


