
// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>


// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>





int _tmain(int argc, TCHAR* argv[]) {

	DWORD val1, val2;
	val1 = _ttoi(argv[1]);
	val2 = _ttoi(argv[2]);


	_tprintf(_T("%d + %d = %d \n"), val1, val2, val1 + val2);

	_gettchar();

	return 0;
}



