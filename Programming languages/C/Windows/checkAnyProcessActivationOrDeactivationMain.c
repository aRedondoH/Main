/* Common includes */
#include <windows.h>
#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>


/* Processes includes */
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>
#include <clocale>
#include <cstdlib>
#include <comdef.h>
#include <wchar.h>
#include <Windows.h>
#include <VersionHelpers.h>
#pragma comment( lib, "ole32.lib" )



#define MAX_NUMBER_OF_PROCESSES 300
#define MAX_LENGHT_LINE 200
#define MAX_LENGHT_PID 10
#define MAX_LENGHT_OUTPUT 210

/* Common processes */
char *arrayOfCommonProcesses[MAX_NUMBER_OF_PROCESSES];
int currentPositionMainList = 0;
int numberOfCommonProcesses = 0;

char *arrayOfCommonProcessesTemp[MAX_NUMBER_OF_PROCESSES];
int currentPositionTempList = 0;
int numberOfCommonProcessesTemp = 0;

void printArrayOfProcess(char * arrayOfProcesses[MAX_NUMBER_OF_PROCESSES]){
	int z;
	printf("List of processes into array: \n");
	for (z = 0; z <= numberOfCommonProcesses; z++){
		printf("Pos: %d process: %s\n", z, arrayOfProcesses[z]);
	}
	printf("\n");
}


void makeListEveryProcessRunning(){
	bool exists = false;
	PROCESSENTRY32 process;
	WCHAR wc[MAX_LENGHT_LINE];
	DWORD pid = 0;
	char cpid[MAX_LENGHT_PID];

	process.dwSize = sizeof(PROCESSENTRY32);
	// Get snapshot of the current windows status 
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);


	printf("Processes running: \n");
	// Get processes running and their pid
	if (Process32First(snapshot, &process)){
		while (Process32Next(snapshot, &process)){
			pid = process.th32ProcessID;

			/* Making a wchar msg */
			ua_wcscpy_s(wc, MAX_LENGHT_LINE, process.szExeFile);
			wcscat_s(wc, MAX_LENGHT_LINE, L" with pid: ");
			/* Convert wchar msg to char* */
			_bstr_t b(wc);
			/* Convert dword to char* */
			sprintf(cpid, "%d", pid);
			/* Concatenate strings */
			char msgOutput[MAX_LENGHT_OUTPUT];
			strcpy_s(msgOutput, MAX_LENGHT_OUTPUT, b);
			strcat_s(msgOutput, MAX_LENGHT_OUTPUT, cpid);
			//printf("%s\n", msgOutput);

			/* insert process into array */
			arrayOfCommonProcesses[currentPositionMainList] = (char *)malloc(strlen(msgOutput) + 1); // Memory allocation for each process
			strcpy(arrayOfCommonProcesses[currentPositionMainList], msgOutput); // copy the process into array
			numberOfCommonProcesses = currentPositionMainList;
			currentPositionMainList++;
		}
	}
	CloseHandle(snapshot);
}

void makeListEveryProcessRunningTemp(){

	bool exists = false;
	PROCESSENTRY32 process;
	WCHAR wc[MAX_LENGHT_LINE];
	DWORD pid = 0;
	char cpid[MAX_LENGHT_PID];

	process.dwSize = sizeof(PROCESSENTRY32);
	// Get snapshot of the current windows status 
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);



	// Get processes running and their pid
	if (Process32First(snapshot, &process)){
		while (Process32Next(snapshot, &process)){
			pid = process.th32ProcessID;

			/* Making a wchar msg */
			ua_wcscpy_s(wc, MAX_LENGHT_LINE, process.szExeFile);
			wcscat_s(wc, MAX_LENGHT_LINE, L" with pid: ");
			/* Convert wchar msg to char* */
			_bstr_t b(wc);
			/* Convert dword to char* */
			sprintf(cpid, "%d", pid);
			/* Concatenate strings */
			char msgOutput[MAX_LENGHT_OUTPUT];
			strcpy_s(msgOutput, MAX_LENGHT_OUTPUT, b);
			strcat_s(msgOutput, MAX_LENGHT_OUTPUT, cpid);
			//printf("%s\n", msgOutput);

			/* insert process into array */
			arrayOfCommonProcessesTemp[currentPositionTempList] = (char *)malloc(strlen(msgOutput) + 1); // Memory allocation for each process
			strcpy(arrayOfCommonProcessesTemp[currentPositionTempList], msgOutput); // copy the process inside of array
			numberOfCommonProcessesTemp = currentPositionTempList;
			currentPositionTempList++;
		}
	}
	CloseHandle(snapshot);

}
/* Check if the process exists inside of the list */
int checkIfTheProcessExistsOnArray(char * process){
	int found = 0;
	int i;

	for (i = 0; i <= numberOfCommonProcesses; i++){
		if (strcmp(process, arrayOfCommonProcesses[i]) == 0){
			found = 1;
		}
	}
	/* If the process exists within array*/
	if (found == 1){
		return 1;
	}
	else{
		if (found == 0){
			return 0;
		}
	}
	return 0;
}

/*Insert process in Array*/
void insertProcessArray(char * proce){
	int emptyHole = 0;
	int positionEmptyHole = 0;
	int p;

	// Search if there is a empty hole to insert the process
	for (p = 0; p < numberOfCommonProcesses; p++){
		// if the array has an empty hole
		if (strcmp(arrayOfCommonProcesses[p], "") == 0){
			emptyHole = 1;
			positionEmptyHole = p;
		}
	}
	// if there is an empty hole it inserts the process on it
	if (emptyHole == 1){
		// Memory allocation for each process
		arrayOfCommonProcesses[positionEmptyHole] = (char*)malloc(strlen(proce) + 1);
		// copy the process into array
		strcpy(arrayOfCommonProcesses[positionEmptyHole], proce);
	}
	else{
		// if there is not an empty hole it inserts the process in a new position
		if (emptyHole == 0){
			// Memory allocation for each process
			arrayOfCommonProcesses[currentPositionMainList] = (char *)malloc(strlen(proce) + 1);
			// copy the process into array
			strcpy(arrayOfCommonProcesses[currentPositionMainList], proce);
			numberOfCommonProcesses = currentPositionMainList;
			currentPositionMainList++;
		}
	}
}

/* Remove a specific process */
void removeProcessOnArray(char * process){
	int n;
	for (n = 0; n <= numberOfCommonProcesses; n++){
		/* if the process is found */
		if ((strcmp(arrayOfCommonProcesses[n], process) == 0) && (strcmp(process, "") != 0)){
			int f;
			/* assigning the next process to the current position to remove */
			for (f = n; f <= numberOfCommonProcesses; f++){
				if (f != numberOfCommonProcesses){
					arrayOfCommonProcesses[f] = arrayOfCommonProcesses[f + 1];
				}
				else{
					/* if it is on the last position, it assigns an empty hole */
					if (f == numberOfCommonProcesses){
						arrayOfCommonProcesses[f] = "";
					}
				}
			}
		}
	}
}

/* check if there is a new process activated */
void checkNewProcesses(){
	int s;
	int d;
	int found = -1;

	// Check if there is a new process to include in the main list of processes
	for (s = 0; s <= numberOfCommonProcessesTemp; s++){
		for (d = 0; d <= numberOfCommonProcesses; d++){
			if (strcmp(arrayOfCommonProcessesTemp[s], arrayOfCommonProcesses[d]) == 0){
				found = 0;
			}
		}
		/* if found==-1 outside loop means there is a new process */
		if (found == -1){
			if (checkIfTheProcessExistsOnArray(arrayOfCommonProcessesTemp[s]) == 0){
				printf("New process activated: %s\n", arrayOfCommonProcessesTemp[s]);
				insertProcessArray(arrayOfCommonProcessesTemp[s]);
			}
		}
		found = -1;
	}
}

/* Check if there are new termination process */
void checkTerminationProcesses(){
	int h;
	int k;
	int found = -1;
	// check if each process from main list is inside of temp list
	for (h = 0; h <= numberOfCommonProcesses; h++){
		for (k = 0; k <= numberOfCommonProcessesTemp; k++){
			if (strcmp(arrayOfCommonProcesses[h], arrayOfCommonProcessesTemp[k]) == 0){
				found = 0;
			}
		}
		/* if found==-1 outside loop means there is a deactivate process */
		if (strcmp(arrayOfCommonProcesses[h], "") != 0){
			if (found == -1){
				printf("Termination process: %s\n", arrayOfCommonProcesses[h]);
				removeProcessOnArray(arrayOfCommonProcesses[h]);
			}
		}
		found = -1;
	}
}

/* Clean the array to assign empty holes */
void cleanArray(char * arrayToClean[MAX_NUMBER_OF_PROCESSES]){
	currentPositionTempList = 0;
}

/* Check if there is any process activated or deactivated */
void checkAnyActivationOrTerminationProcess(){
	makeListEveryProcessRunningTemp();
	checkNewProcesses();
	checkTerminationProcesses();
	cleanArray(arrayOfCommonProcessesTemp);
}

int main(int argc, char *argv[]){

	printf("We are going to check any process activate or deactivate\n ");
	// make the list of processes running
	makeListEveryProcessRunning();
	printf("\n");

	for (;;){
		checkAnyActivationOrTerminationProcess();
		Sleep(3000);
	}
}