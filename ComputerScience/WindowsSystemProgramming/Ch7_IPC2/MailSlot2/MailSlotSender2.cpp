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

	// SECURITY_ATTRIBUTES : �ڵ� ��� ���� ����ü
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);		// ����ü ���� ũ�� 
	sa.lpSecurityDescriptor = NULL;	// �ڵ� ��� ���������� �ǹ̰� ����
	sa.bInheritHandle = TRUE;		// �ش� �ڵ��� ��� ���� ����

	// CreateFile : Ư�� ���Ͻ��� �ּҷ� ������ ������ ��Ʈ�� ����
	hMailSlot = CreateFile(
		MAIL_SLOT_NAME,			// ���� �� �����ϰ��� �ϴ� ���� �̸� ����
		GENERIC_WRITE,			// ������ ���� ��� ���� : ������
		FILE_SHARE_READ,
		&sa,
		OPEN_EXISTING,			// ������ ������� ���� : �̹� ������ ���Ͻ����� ���� ��
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hMailSlot == INVALID_HANDLE_VALUE) {
		_fputts(_T("Unable to create MailSlot Stream\n"), stdout);
		return 1;
	}


	// ���Ͻ����� �ڵ� ���� ��� �� ����
	_tprintf(_T("Inheritable Handle : %d \n"), hMailSlot);
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("wt"));
	_ftprintf(file, _T("%d"), hMailSlot);
	fclose(file);

	// �ڽ� ���μ��� ����
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("MailSlotSenderChild.exe");

	CreateProcess(
		NULL, command,
		NULL, NULL,
		TRUE,		// �ڵ� ���̺� ��� ����
		CREATE_NEW_CONSOLE,
		NULL, NULL,
		&si, &pi
	);
	

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


