#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

typedef BOOL(WINAPI *P_GDFSE)(LPCTSTR, PULARGE_INTEGER,
	PULARGE_INTEGER, PULARGE_INTEGER);

void method1(int argc,char *argv[]){

	BOOL  fResult;

	char  *pszDrive = NULL,
		szDrive[4];

	DWORD dwSectPerClust,
		dwBytesPerSect,
		dwFreeClusters,
		dwTotalClusters;

	P_GDFSE pGetDiskFreeSpaceEx = NULL;

	unsigned __int64 i64FreeBytesToCaller,
		i64TotalBytes,
		i64FreeBytes;
	unsigned __int64 i64UsageMBytes;
	unsigned __int64 i64TotalMBytes;


	/*
	Use GetDiskFreeSpaceEx if available; otherwise, use
	GetDiskFreeSpace.

	Note: Since GetDiskFreeSpaceEx is not in Windows 95 Retail, we
	dynamically link to it and only call it if it is present.  We
	don't need to call LoadLibrary on KERNEL32.DLL because it is
	already loaded into every Win32 process's address space.
	*/
	pGetDiskFreeSpaceEx = (P_GDFSE)GetProcAddress(
		GetModuleHandle("kernel32.dll"),
		"GetDiskFreeSpaceExA");
	if (pGetDiskFreeSpaceEx)
	{
		fResult = pGetDiskFreeSpaceEx(L"C:",
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);
		if (fResult)
		{
			/* Get Total space in disk */
			i64TotalMBytes = i64TotalBytes / (1000 * 1000);
			/* Get total MB used */
			i64UsageMBytes = (i64TotalBytes / (1000 * 1000)) - (i64FreeBytes / (1000 * 1000));
			/* Printf percentaje MB used */
			printf("Total percentage disk usage: %I64u%% \n", (i64UsageMBytes * 100) / i64TotalMBytes);
		}
	}
	else
	{
		fResult = GetDiskFreeSpace(L"C:",
			&dwSectPerClust,
			&dwBytesPerSect,
			&dwFreeClusters,
			&dwTotalClusters);
	
		if (fResult)
		{
			/* force 64-bit math */
			i64TotalBytes = (__int64)dwTotalClusters * dwSectPerClust *
				dwBytesPerSect;
			i64FreeBytes = (__int64)dwFreeClusters * dwSectPerClust *
				dwBytesPerSect;

			/* Get Total space in disk */
			i64TotalMBytes = i64TotalBytes / (1000 * 1000);
			/* Get total MB used */
			i64UsageMBytes = (i64TotalBytes / (1000 * 1000)) - (i64FreeBytes / (1000 * 1000));
			/* Printf percentaje MB used */
			printf("Total percentage disk usage: %I64u%% \n", (i64UsageMBytes * 100) / i64TotalMBytes);
		}
	}

	if (!fResult)
		printf("error: %lu:  could not get free space for \"%s\"\n",
		GetLastError(), argv[1]);

}


int main(int argc, char *argv[]) {

	method1(argc, argv);	

	return 0;

}