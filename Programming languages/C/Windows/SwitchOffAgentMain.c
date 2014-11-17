#define WIN32_LEAN_AND_MEAN 1
#include <stdio.h>
#include <stdlib.h>

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

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

#pragma comment(lib, "pdh.lib")


HANDLE  hConsoleOut;                 // Handle to the console 
HANDLE  hRunMutex;                   // "Keep Running" mutex 
HANDLE  hScreenMutex;                // "Screen update" mutex
int     ThreadNr;                    // Number of threads started 
CONSOLE_SCREEN_BUFFER_INFO csbiInfo; // Console information 

HANDLE switchOffMutex;


DWORD WINAPI threadOverLoad(void *vamosPrimo){
	int * i = 0;
	float * p = 0;

	while (p == p){
		(*p++) + 1.144564542315345;
		(*i++) + 1;
	}
	return 0;
}

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
		PdhAddCounter(query, szCounterName, 0, &counter); // this line works

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

/* if Agent needs to switch off return 1
* if Agent does not need to switch off return 0 */
int determineIfAgentNeedToSwitchOff(int currentCpuUsage, int maxCpuUsage) {
	int switchOff = 0;
	/* if the currentCpuUsage is higher than maxCpuUsage allow for the Agent */
	if (currentCpuUsage >= maxCpuUsage) {
		printf("Something is wrong with the Agent, switching off\n");
		switchOff = 1;
	}
	return switchOff;
}

DWORD WINAPI switchOffAgentIfNecessary(void *vamosPrimo){

	int cpuLoadAgent = 0;
	printf("Hellooo\n");
	for (;;){
		// Wait for display to be available, then lock it.
		//WaitForSingleObject(switchOffMutex, INFINITE);

		// Check cpu load of the Agent
		char text[] = "SwitchOfAgent";
		wchar_t wtext[20];
		mbstowcs(wtext, text, strlen(text) + 1);//Plus null
		LPWSTR ptr = wtext;
		cpuLoadAgent = getcpuload(ptr);
		// Determine if the Agent needs to switch off
		if (determineIfAgentNeedToSwitchOff(cpuLoadAgent, 80) == 1){
			exit(1);
		}

		// Wait 1 second 
		Sleep(1000);
	}

	return 0;
}

void WriteTitle(int ThreadNumLaLa)
{
	enum {
		sizeOfNThreadMsg = 80
	};
	char NThreadMsg[sizeOfNThreadMsg];

	//sprintf_s(NThreadMsg, sizeOfNThreadMsg,
	//	"Threads running: %02d.  Press 'A' "
	//	"to start a thread,'Q' to quit.", ThreadNum);
	printf("Thread: %d\n", ThreadNumLaLa);
	//SetConsoleTitle(NThreadMsg);
}

int main(void){

	printf("we are going to switch off Agent if it is necessary\n");

	ThreadNr = 2;

	///switchOffAgentIfNecessary();
	//ThreadNr++;



	//switchOffMutex = CreateMutex(NULL, FALSE, NULL);

	//_beginthread(switchOffAgentIfNecessary, 0, &ThreadNr);
	//WaitForSingleObject(switchOffMutex, INFINITE);
	//WriteTitle(ThreadNr);

	//ThreadNr++;
	//_beginthread(threadOverLoad, 0, &ThreadNr);
	//WriteTitle(2);
	HANDLE thread1 = CreateThread(NULL, 0, switchOffAgentIfNecessary, NULL, 0, NULL);
	//WaitForSingleObject(thread1, INFINITE);

	HANDLE thread2 = CreateThread(NULL, 0, threadOverLoad, NULL, 0, NULL);
	//WaitForSingleObject(thread2, INFINITE);

	// Aray to store thread handles 
	HANDLE Array_Of_Thread_Handles[2];
	Array_Of_Thread_Handles[0] = thread1;
	Array_Of_Thread_Handles[1] = thread2;

	// Wait until all threads have terminated.
	WaitForMultipleObjects(2,
		Array_Of_Thread_Handles, TRUE, INFINITE);

	// Close all thread handles upon completion.
	CloseHandle(thread1);
	CloseHandle(thread2);
	


	return 0;
}