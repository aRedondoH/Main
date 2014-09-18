// This program needs only the essential Windows header files.
#define WIN32_LEAN_AND_MEAN 1

#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#include <pdh.h>
#include <pdhmsg.h>

#pragma comment(lib, "pdh.lib")

CONST PWSTR COUNTER_OBJECT = L"Process";


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
		wprintf(L"%s ", pTemp);
		PdhAddCounter(query, TEXT("\\Process(firefox)\\% Processor Time"), 0, &counter); // this line works
		
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

	printf("\n\n"
		"CPU Total usage: %3d%%\n", cput);

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
					wprintf(L"%s\n", pTemp);
				}

				wprintf(L"\nInstances of the Process object:\n\n");

				// Walk the instance list. The list can contain one
				// or more null-terminated strings. The list is terminated
				// using two null-terminator characters.
				for (pTemp = pwsInstanceListBuffer; *pTemp != 0; pTemp += wcslen(pTemp) + 1)
				{
					
					wprintf(L"%s\n", pTemp);
				
					getcpuload(pTemp);
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
	//for (;;){
		//getcpuload();
		getCpuLoadForEachProcess();
	//	Sleep(1000);
	//}
}

