// Header for Standard Programming
#include <stdio.h>

// Header for Windows System Programming
#include <tchar.h>
#include <Windows.h>




#define DIR_LEN MAX_PATH+1


int _tmain(int argc, TCHAR* argv[]) {
	// STARTUPINFO : ���μ����� �Ӽ��� �����ϱ� ���� ����ü
	STARTUPINFO si = { 0, };

	PROCESS_INFORMATION pi;

	// ���μ��� �Ӽ� ����
	// ����ü ���� ũ�� : Ȯ�强�� ����� �������� ����
	si.cb = sizeof(si);

	// STARTF_USEPOISTION : dwX,dwY �����ؼ� ������ ��ġ ����
	// STARTF_USESIZE : dwXSize, dwYSize �����ؼ� ������ ũ�� ����
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 100; si.dwY = 200;			// ���μ��� ������ ��ǥ
	si.dwXSize = 300; si.dwYSize = 200;	// ���μ��� ������ ����,���� ����
	si.lpTitle = _T("I am a child");		// ���μ��� Ÿ��Ʋ

	// ���μ��� ���� Ŀ�ǵ� ����
	TCHAR command[] = _T("AdderProcess.exe 10 20");
	TCHAR cDir[DIR_LEN];
	

	// ���� ���丮 Ȯ��
	GetCurrentDirectory(DIR_LEN, cDir);
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	// ���� ���丮 ���� : �ڽ� ���μ����� �ִ� ���丮
	BOOL dirSetting;
	dirSetting = SetCurrentDirectory(_T("D:\\VisualStudio2015\\WinSystem"));

	if (dirSetting != 0) {
		_fputts(_T("SetCurrentDirectory OK!\n"), stdout);
	}
	else {
		_fputts(_T("SetCurrentDirectory ERROR!\n"), stdout);
	}

	// ���� ���丮 Ȯ��
	GetCurrentDirectory(DIR_LEN, cDir);
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	BOOL state;
	state = CreateProcess(
		NULL,				// ���μ��� ��� ����( NULL: ���� ���丮)
		command,			// ���μ��� ������ ���� Ŀ�ǵ�
		NULL, NULL, TRUE,	// ���ȼӼ�, ������, �ڵ� ��� ����
		CREATE_NEW_CONSOLE,	// ���� ���μ����� Ư��(�켱����) ���� �ɼ� : ����� �ܼ� ������� ����
		NULL, NULL,			// �޸� ��� ����, ���� ���μ��� ���丮
		&si,				// ���� ���μ��� �Ӽ� ����
		&pi					// �����ϴ� ���μ��� ���� �޾ƿ���
	);

	if (state != 0) {
		_fputts(_T("Creation OK!\n"), stdout);
	}
	else {
		_fputts(_T("Creation ERROR!\n"), stdout);
	}

	return 0;
}



