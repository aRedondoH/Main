#include<stdio.h>
#include<Windows.h>
#include<VersionHelpers.h>
#include<stdlib.h>

/* Processes includes */
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>
#include <clocale>
#include <cstdlib>
#include <comdef.h> //new
#include <wchar.h>

/* Get currently OS */
void getWindowsVersion(){
	if (IsWindowsXPOrGreater() && !IsWindowsXPSP1OrGreater()){
		printf("OS: Windows XP\n");
	}
	if (IsWindowsXPSP1OrGreater() && !IsWindowsXPSP2OrGreater()){
		printf("OS: Windows XP SP1\n");
	}
	if (IsWindowsXPSP2OrGreater() && !IsWindowsXPSP3OrGreater()){
		printf("OS: Windows XP SP2\n");
	}
	if (IsWindowsXPSP3OrGreater() && !IsWindowsVistaOrGreater()){
		printf("OS: Windows XP SP3\n");
	}
	if (IsWindowsVistaOrGreater() && !IsWindowsVistaSP1OrGreater()){
		printf("OS: Windows Vista\n");
	}
	if (IsWindowsVistaSP1OrGreater() && !IsWindowsVistaSP2OrGreater()){
		printf("OS: Windows Vista SP1\n");
	}
	if (IsWindowsVistaSP2OrGreater() && !IsWindows7OrGreater()){
		printf("OS: Windows Vista SP2\n");
	}
	if (IsWindows7OrGreater() && !IsWindows7SP1OrGreater()){
		printf("OS: Windows 7\n");
	}
	if (IsWindows7SP1OrGreater() && !IsWindows8OrGreater()){
		printf("OS: Windows 7 SP1\n");
	}
	if (IsWindows8OrGreater() && !IsWindows8Point1OrGreater()){
		printf("OS: Windows 8\n");
	}
	if (IsWindows8Point1OrGreater()){
		printf("OS: Windows 8.x\n");
	}
	printf("\n");
}

/* Get currently open ports */
void getOpenPorts(){
	FILE *fp;
	errno_t err;
	char portsOutput[300];
	char portsOutputCopy[300];
	int count = 0;
	char *token;
	char *next_token;
	char str1[30];
	char str2[30];
	char str3[30];
	char str4[30];
	int dontPrintAnyMore = 0;
	int noPortsOpen = 0;
	int portOpen = 0;

	/* Get open ports */
	system("netsh firewall show state > tempFirewallOutput.txt");
	err = fopen_s(&fp, "tempFirewallOutput.txt", "r");
	if (err != 0){
		printf("Error %d when open file", err);
	}
	strcpy(str2, "IMPORTANT:");
	strcpy(str3, "\n");
	strcpy(str4, "No");

	/* Read the output a line at a time - output it. */
	while (fgets(portsOutput, 300, fp) != NULL) {
		strcpy(portsOutputCopy, portsOutput); // copy of portsOutput
		token = strtok_s(portsOutputCopy, " ", &next_token);
		strcpy(str1, token);
		/* if it find the word "IMPORTANT:" or " " it doesn't print any more*/
		int ret = strcmp(str1, str2);
		if (ret == 0){
			dontPrintAnyMore = 1;
		}
		int ret2 = strcmp(str1, str3);
		if ((count > 13) && (ret2 == 0)){
			dontPrintAnyMore = 1;
		}
		// if it find the word "No" it means there aren't ports open
		int ret3 = strcmp(str1, str4);
		if (ret3 == 0){
			noPortsOpen = 1;
		}
		// Get port
		if ((count > 13) && (noPortsOpen != 1)){
			sscanf(portsOutput, "%d", &portOpen);
		}

		/* print output for our purpose */
		if ((count > 13) && (dontPrintAnyMore != 1) && (noPortsOpen != 1)){
			printf("Port open: %d\n", portOpen);
		}

		count++; // counting lines from the tempFirewallOutput
	}
	if (noPortsOpen == 1){
		printf("No ports are currently open\n");
	}
	fclose(fp);
	printf("\n");
}
/* Get all the process running */
void getAllProcessesRunning(){
	bool exists = false;
	PROCESSENTRY32 process;
	WCHAR wc[200];
	DWORD pid = 0;
	char cpid[10];


	process.dwSize = sizeof(PROCESSENTRY32);
	// Get snapshot of the current windows status 
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	printf("Processes running: \n");
	// Get processes running and their pid
	if (Process32First(snapshot, &process)){
		while (Process32Next(snapshot, &process)){
			pid = process.th32ProcessID;

			/* Making a wchar msg */
			ua_wcscpy_s(wc, 200, process.szExeFile);
			wcscat_s(wc, 200, L" with pid: ");
			/* Convert wchar msg to char* */
			_bstr_t b(wc);
			/* Convert dword to char* */
			sprintf(cpid, "%d", pid);
			/* Concatenate strings */
			char msgOutput[210];
			strcpy_s(msgOutput, 210, b);
			strcat_s(msgOutput, 210, cpid);

			printf("%s\n", msgOutput);
			
		}
	}
	CloseHandle(snapshot);
}

void audit(){
	printf("--------- Audit ---------------\n\n");
	/* Get Windows version */
	getWindowsVersion();
	/* Get Open ports*/
	getOpenPorts();
	/* Get all processes running */
	getAllProcessesRunning();
	printf("\n-------------------------------\n");
}

int __cdecl wmain(__in int argc, __in_ecount(argc) PCWSTR argv[])
{
	for (;;){
		audit();
		//Sleep(1000);
	}
	
}