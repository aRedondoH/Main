/* Hello World program */

#include <stdio.h>
#include <Windows.h>
#include <Pdh.h>

int oldLow;
int oldHigh;

void setTimeStandAtthebeginning(){

	// the files handle
	HANDLE hFile1;
	// FILETIME is another name for struct _FILETIME structure (a typedef)
	FILETIME ftWrite;
	// SYSTEMTIME is another name for struct _SYSTEMTIME structure (a typedef)
	SYSTEMTIME stUTC, stLocal;
	// low byte data
	DWORD low;
	// high byte data
	DWORD high;
	// filename, make sure the file is there
	LPCWSTR fname1 = L"c:\\TestingFile.txt";

	// Opening the existing file
	hFile1 = CreateFile(fname1, //file to open
		GENERIC_READ, //open for reading
		FILE_SHARE_READ, //share for reading
		NULL, //default security
		OPEN_EXISTING, //existing file only
		FILE_ATTRIBUTE_NORMAL, //normal file
		NULL); //no attribute template

	if (hFile1 == INVALID_HANDLE_VALUE)
	{
		printf("Could not open %S file, error %ul\n", fname1, GetLastError());
		// just exit...
		return 4;
	}
	//else
	//	printf("%S file opened successfully\n", fname1);

	// Retrieve the created file times
	if (!GetFileTime(hFile1, NULL, NULL, &ftWrite))
	{
		printf("Something wrong!\n");
		return FALSE;
	}

	// Viewing the unreadable...
	// Filing the 32 bit low part into variable low and another 32 bit high part into variable high
	// Accessing the FILETIME structures' members, assigning them to some variables...

	low = ftWrite.dwLowDateTime;
	oldLow = ftWrite.dwLowDateTime;
	high = ftWrite.dwHighDateTime;
	oldHigh = ftWrite.dwHighDateTime;

	// Trying to display the content in hex...
	//printf("Unreadable format...\n");
	//printf("32 bit: low byte is = %0X and high byte is = %0X\n", low, high);

	// Convert the file created time to local time.
	FileTimeToSystemTime(&ftWrite, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
	//printf("\nReadable format...\n");

	// Build a readable string showing the date and time. Accessing the SYSTEMTIME structure's member
	//printf("UTC System Time format:\n");
	//printf("Writen on: %02d/%02d/%d %02d:%02d\n", stUTC.wDay, stUTC.wMonth,
	//	stUTC.wYear, stUTC.wHour, stUTC.wMinute);

	// Accessing the SYSTEMTIME structures' members
	//printf("Local time format:\n");
	printf("Writen on: %02d/%02d/%d %02d:%02d\n", stLocal.wDay, stLocal.wMonth,
		stLocal.wYear, stLocal.wHour, stLocal.wMinute);

	// close the file's handle and itself
	if (CloseHandle(hFile1) == 0)
		printf("%S handle can't be closed! Error code: %d\n", fname1, GetLastError());
	//else
	//printf("%S handle closed successfully\n", fname1);

}

void checkPathFile(){


	// the files handle
	HANDLE hFile1;
	// FILETIME is another name for struct _FILETIME structure (a typedef)
	FILETIME ftWrite;
	// SYSTEMTIME is another name for struct _SYSTEMTIME structure (a typedef)
	SYSTEMTIME stUTC, stLocal;
	// low byte data
	DWORD low;
	// high byte data
	DWORD high;
	// filename, make sure the file is there
	LPCWSTR fname1 = L"c:\\TestingFile.txt";

	// Opening the existing file
	hFile1 = CreateFile(fname1, //file to open
		GENERIC_READ, //open for reading
		FILE_SHARE_READ, //share for reading
		NULL, //default security
		OPEN_EXISTING, //existing file only
		FILE_ATTRIBUTE_NORMAL, //normal file
		NULL); //no attribute template

	if (hFile1 == INVALID_HANDLE_VALUE)
	{
		printf("Could not open %S file, error %ul\n", fname1, GetLastError());
		// just exit...
		return 4;
	}
	//else
	//	printf("%S file opened successfully\n", fname1);

	// Retrieve the created file times
	if (!GetFileTime(hFile1, NULL, NULL, &ftWrite))
	{
		printf("Something wrong!\n");
		return FALSE;
	}

	// Viewing the unreadable...
	// Filing the 32 bit low part into variable low and another 32 bit high part into variable high
	// Accessing the FILETIME structures' members, assigning them to some variables...

	low = ftWrite.dwLowDateTime;
	
	high = ftWrite.dwHighDateTime;
	

	// Trying to display the content in hex...
	//printf("Unreadable format...\n");
	//printf("32 bit: low byte is = %0X and high byte is = %0X\n", low, high);

	// Convert the file created time to local time.
	FileTimeToSystemTime(&ftWrite, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
	//printf("\nReadable format...\n");

	// Build a readable string showing the date and time. Accessing the SYSTEMTIME structure's member
	//printf("UTC System Time format:\n");
	//printf("Created on: %02d/%02d/%d %02d:%02d\n", stUTC.wDay, stUTC.wMonth,
	//	stUTC.wYear, stUTC.wHour, stUTC.wMinute);

	// Accessing the SYSTEMTIME structures' members
	//printf("Local time format:\n");
	printf("Writen on: %02d/%02d/%d %02d:%02d\n", stLocal.wDay, stLocal.wMonth,
		stLocal.wYear, stLocal.wHour, stLocal.wMinute);

	// close the file's handle and itself
	if (CloseHandle(hFile1) == 0)
		printf("%S handle can't be closed! Error code: %d\n", fname1, GetLastError());
	//else
		//printf("%S handle closed successfully\n", fname1);

	int newLow = ftWrite.dwLowDateTime;
	int newHigh = ftWrite.dwHighDateTime;

	if ((oldLow != newLow) && (oldHigh != newHigh)){
	
		printf("The file timestamp has been changed\n");

		// Update timestamp values
		oldLow = newLow;
		newLow = newHigh;
	}

}


int main(void)

{
	setTimeStandAtthebeginning();
	for (;;){
		checkPathFile();
		Sleep(1000);
	}
	return 0;
}