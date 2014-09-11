#include <errno.h>
#include <stdio.h>
#include <windows.h>
#include <tchar.h> 



void test2(){
	//LPTSTR lpszFilePath = _T("C:\\Windows\\system32\\cmd.exe");
	LPTSTR lpszFilePath = _T("VBoxTray.exe"); //process path
	DWORD dwDummy;

	DWORD dwFVISize = GetFileVersionInfoSize(lpszFilePath, &dwDummy);
	LPBYTE lpVersionInfo = new BYTE[dwFVISize];
	GetFileVersionInfo(lpszFilePath, 0, dwFVISize, lpVersionInfo);
	UINT uLen;
	VS_FIXEDFILEINFO *lpFfi;
	VerQueryValue(lpVersionInfo, _T("\\"), (LPVOID *)&lpFfi, &uLen);
	DWORD dwFileVersionMS = lpFfi->dwFileVersionMS;
	DWORD dwFileVersionLS = lpFfi->dwFileVersionLS;
	delete[] lpVersionInfo;

	// Print high and lower part of version
	//printf("Higher: %x\n", dwFileVersionMS);
	//printf("Lower: %x\n", dwFileVersionLS);
	DWORD dwLeftMost = HIWORD(dwFileVersionMS);
	DWORD dwSecondLeft = LOWORD(dwFileVersionMS);
	DWORD dwSecondRight = HIWORD(dwFileVersionLS);
	DWORD dwRightMost = LOWORD(dwFileVersionLS);

	// Print version of the program
	_tprintf(TEXT("App: %s "),lpszFilePath);
	printf("version: %d.%d.%d.%d\n",dwLeftMost, dwSecondLeft,
		dwSecondRight, dwRightMost);
}



int main(int argc, char **argv)
{
	test2();
	return 0;
}