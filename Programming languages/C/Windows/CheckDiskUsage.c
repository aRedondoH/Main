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
	Command line parsing.

	If the drive is a drive letter and not a UNC path, append a
	trailing backslash to the drive letter and colon.  This is
	required on Windows 95 and 98.
	*/
	/*if (argc != 2)
	{
		printf("usage:  %s <drive|UNC path>\n", argv[0]);
		printf("\texample:  %s C:\\\n", argv[0]);
		return;
	}*/

	/*pszDrive = argv[1];*/

	/*if (pszDrive[1] == ':')
	{
		szDrive[0] = pszDrive[0];
		szDrive[1] = ':';
		szDrive[2] = '\\';
		szDrive[3] = '\0';

		pszDrive = szDrive;
	}*/

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
			/*printf("\n\nGetDiskFreeSpaceEx reports\n\n");
			printf("Available space to caller = %I64u MB\n",
				i64FreeBytesToCaller / (1000 * 1000));
			printf("Total space               = %I64u MB\n",
				i64TotalBytes / (1000 * 1000));
			printf("Free space on drive       = %I64u MB\n",
				i64FreeBytes / (1000 * 1000));*/

			i64TotalMBytes = i64TotalBytes / (1000 * 1000);

			i64UsageMBytes = (i64TotalBytes / (1000 * 1000)) - (i64FreeBytes / (1000 * 1000));

			/*printf("Usage space = %I64u MB\n", i64UsageMBytes");*/

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

			/*printf("GetDiskFreeSpace reports\n\n");
			printf("Free space  = %I64u MB\n",
				i64FreeBytes / (1000 * 1000));
			printf("Total space = %I64u MB\n",
				i64TotalBytes / (1000 * 1000));*/

			
			i64TotalMBytes = i64TotalBytes / (1000 * 1000);

			i64UsageMBytes = (i64TotalBytes / (1000 * 1000)) - (i64FreeBytes / (1000 * 1000));

			/*printf("Usage space = %I64u MB\n", i64UsageMBytes");*/

			printf("Total percentage disk usage: %I64u%% \n", (i64UsageMBytes * 100) / i64TotalMBytes);
		}
	}

	if (!fResult)
		printf("error: %lu:  could not get free space for \"%s\"\n",
		GetLastError(), argv[1]);

}

static unsigned __int64 getFreeSpace(const char* dir)
{
	ULARGE_INTEGER freeBytesUser;
	ULARGE_INTEGER bytes;
	ULARGE_INTEGER freeBytesTotal;
	div_t divresult;


	int i = GetDiskFreeSpaceEx(L"C:", &freeBytesUser, &bytes, &freeBytesTotal);
	//cout << i << endl;
	printf("%d\n", i);
	
	printf("%llu %llu %llu\n", freeBytesUser, bytes, freeBytesTotal);
	return freeBytesUser.QuadPart;
}

void method2(){

	getFreeSpace(" C:\ ");

}

void method3PercentageDiskUsage(){

	//wmic logicaldisk get size,freespace,caption | find "C:"

	FILE *fp;
	char line[100];
	char command[100];
	long diskFullSpace;
	long long diskFreeSpace;

	// Command to get percentage disk usage
	sprintf(command, "wmic logicaldisk get size,freespace,caption | find \"C:\" ");

	fp = _popen(command, "r");
	/* Error run command */
	if (fp == NULL) {
		printf("Failed to run command to get disk usage \n");
	}
	else {
		char *token1;
		char strToConvert[100];
		/* Read output from command running*/
		while (fgets(line, sizeof line, fp) != NULL) {
			token1 = strtok(line, " ");
			token1 = strtok(NULL, " ");
			printf("--%s--\n", token1);
			//diskFreeSpace = atoll(token1);
			
			diskFreeSpace = strtol(strToConvert,NULL, 11);
			

			//diskUsage = atoi(line);
			printf("%ld\n", diskFreeSpace);
			printf("Hi\n");
		}
	}
	/* close file */
	fclose(fp);

}

int main(int argc, char *argv[]) {

	method1(argc, argv);	
	//method2();
	//method3PercentageDiskUsage();

	return 0;

}