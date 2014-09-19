// This program needs only the essential Windows header files.
#define WIN32_LEAN_AND_MEAN 1

#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#include <pdh.h>
#include <pdhmsg.h>

#include <tchar.h>
#include <clocale>
#include <cstdlib>
#include <comdef.h>
#include <wchar.h>

#pragma comment(lib, "pdh.lib")

CONST PWSTR COUNTER_OBJECT = L"Process";

#define MAX_NUMBER_OF_PROCESSES 300
char *arrayOfCommonProcesses[MAX_NUMBER_OF_PROCESSES];

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

void SomeFunction(LPWSTR aString);

INT getcpuload(LPWSTR pTemp)
{
	static PDH_STATUS            status;
	static PDH_FMT_COUNTERVALUE  value;
	static HQUERY                query;
	static HCOUNTER              counter;
	static DWORD                 ret;
	static char                  runonce = 1;
	char                         cput = 0;

	if (runonce)
	{
		status = PdhOpenQuery(NULL, 0, &query);
		if (status != ERROR_SUCCESS)
		{
			printf("PdhOpenQuery() ***Error: 0x%X\n", status);
			return 0;
		}

		//PdhAddCounter(query, TEXT("\\Processor(_Total)\\% Processor Time"), 0, &counter); // A total of ALL CPU's in the system
		//PdhAddCounter(query, TEXT("\\Process(OUTLOOK)\\% Processor Time"), 0, &counter);
		//PdhAddCounter(query, TEXT("\\Process(calc)\\% Processor Time"), 0, &counter); // this line works
		

		
		TCHAR * szCounterName;
		szCounterName = new TCHAR[MAX_PATH];
		_stprintf(szCounterName, TEXT("\\Process(%s)\\%% Processor Time"), pTemp);
		PdhAddCounter(query,szCounterName, 0, &counter); // this line works
		
		//PdhAddCounter(query, TEXT("\\Process(pTemp)\\% Processor Time"), 0, &counter);
		//PdhAddCounter(query, TEXT("\\Processor(0)\\% Processor Time"),0,&counter);    // For systems with more than one CPU (Cpu0)
		//PdhAddCounter(query, TEXT("\\Processor(1)\\% Processor Time"),0,&counter);    // For systems with more than one CPU (Cpu1)
		runonce = 0;
		PdhCollectQueryData(query); // No error checking here
		return 0;
	}

	status = PdhCollectQueryData(query);
	if (status != ERROR_SUCCESS)
	{
		printf("PhdCollectQueryData() ***Error: 0x%X\n", status);
		if (status == PDH_INVALID_HANDLE)
			printf("PDH_INVALID_HANDLE\n");
		else if (status == PDH_NO_DATA)
			printf("PDH_NO_DATA\n");
		else
			printf("Unknown error\n");
		return 0;
	}

	status = PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE | PDH_FMT_NOCAP100, &ret, &value);
	if (status != ERROR_SUCCESS)
	{
		printf("PdhGetFormattedCounterValue() ***Error: 0x%X\n", status);
		return 0;
	}
	cput = value.doubleValue;
	
		wprintf(L" Process: %s ", pTemp);
		printf("CPU usage: %3d%%\n", cput);
	
	return cput;
}


void getCpuLoadForEachProcess(){
	PDH_STATUS status = ERROR_SUCCESS;
	LPWSTR pwsCounterListBuffer = NULL;
	DWORD dwCounterListSize = 0;
	LPWSTR pwsInstanceListBuffer = NULL;
	DWORD dwInstanceListSize = 0;
	LPWSTR pTemp = NULL;

	// Determine the required buffer size for the data. 
	status = PdhEnumObjectItems(
		NULL,                   // real-time source
		NULL,                   // local machine
		COUNTER_OBJECT,         // object to enumerate
		pwsCounterListBuffer,   // pass NULL and 0
		&dwCounterListSize,     // to get required buffer size
		pwsInstanceListBuffer,
		&dwInstanceListSize,
		PERF_DETAIL_WIZARD,     // counter detail level
		0);

	if (status == PDH_MORE_DATA)
	{
		// Allocate the buffers and try the call again.
		pwsCounterListBuffer = (LPWSTR)malloc(dwCounterListSize * sizeof(WCHAR));
		pwsInstanceListBuffer = (LPWSTR)malloc(dwInstanceListSize * sizeof(WCHAR));

		if (NULL != pwsCounterListBuffer && NULL != pwsInstanceListBuffer)
		{
			status = PdhEnumObjectItems(
				NULL,                   // real-time source
				NULL,                   // local machine
				COUNTER_OBJECT,         // object to enumerate
				pwsCounterListBuffer,
				&dwCounterListSize,
				pwsInstanceListBuffer,
				&dwInstanceListSize,
				PERF_DETAIL_WIZARD,     // counter detail level
				0);

			if (status == ERROR_SUCCESS)
			{
				wprintf(L"Counters that the Process objects defines:\n\n");

				// Walk the counters list. The list can contain one
				// or more null-terminated strings. The list is terminated
				// using two null-terminator characters.
				for (pTemp = pwsCounterListBuffer; *pTemp != 0; pTemp += wcslen(pTemp) + 1)
				{
					//wprintf(L"%s\n", pTemp);
				}

				//wprintf(L"\nInstances of the Process object:\n\n");

				// Walk the instance list. The list can contain one
				// or more null-terminated strings. The list is terminated
				// using two null-terminator characters.
				for (pTemp = pwsInstanceListBuffer; *pTemp != 0; pTemp += wcslen(pTemp) + 1)
				{
					
					//wprintf(L"%s\n", pTemp);
				
					int ccccppuu=getcpuload(pTemp);
					printf("CPU: %d", ccccppuu);
				}
			}
			else
			{
				wprintf(L"Second PdhEnumObjectItems failed with %0x%x.\n", status);
			}
		}
		else
		{
			wprintf(L"Unable to allocate buffers.\n");
			status = ERROR_OUTOFMEMORY;
		}
	}
	else
	{
		wprintf(L"\nPdhEnumObjectItems failed with 0x%x.\n", status);
	}

	if (pwsCounterListBuffer != NULL)
		free(pwsCounterListBuffer);

	if (pwsInstanceListBuffer != NULL)
		free(pwsInstanceListBuffer);

}


void main(void)
{
	char text[] = "firefox";
	wchar_t wtext[20];
	mbstowcs(wtext, text, strlen(text) + 1);//Plus null
	LPWSTR ptr = wtext;

	char text2[] = "iexplorer";
	wchar_t wtext2[20];
	mbstowcs(wtext2, text2, strlen(text2) + 1);//Plus null
	LPWSTR ptr2 = wtext2;
	for (;;){
		//getcpuload(L"firefox");
		//getcpuload(L"iexplore");
		
		
		
		getcpuload(ptr);
		getcpuload(ptr2);
		//getCpuLoadForEachProcess();
		Sleep(1000);
	}
}

