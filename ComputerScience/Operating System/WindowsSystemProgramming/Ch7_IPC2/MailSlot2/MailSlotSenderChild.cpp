/*
< MailSlot Sender >
- Child Process
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

	// �ڵ��� ��� �ڵ�
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("rt"));
	_ftscanf(file, _T("%d"), &hMailSlot);
	fclose(file);
	_tprintf(_T("Inheriable Handle : %d \n"), hMailSlot);



	while (1) {
		_fputts(_T("MY CHILD MESSAGE >> "), stdout);
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


