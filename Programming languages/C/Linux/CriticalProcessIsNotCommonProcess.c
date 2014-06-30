/*
 * CriticalProcessIsNotCommonProcess.c
 *
 *  Created on: Jun 30, 2014
 *      Author: secnok
 */

#define MAXNUMBERPROCESSES 10000
#define MAXLENGHTLINE 200
#define MAX_LENGHT_TEMP_STRING 100

#include <unistd.h>
#include <sys/types.h>

/* Common libraries */
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/* Fake things */
int numberOfProcesses=2;
char *arrayOfProcesses[30];

/* Global variables of processes */
char *arrayOfCommonProcesses[MAXNUMBERPROCESSES];
int currentPositionMainList = 0;
int numberOfCommonProcesses = 0;

char *arrayOfCommonProcessesTemp[MAXNUMBERPROCESSES];
int currentPositionTempList = 0;
int numberOfCommonProcessesTemp = 0;

/* Headers */
/* FUNCTION HEADERS COMMON PROCESSES */

	/*Insert process in Array */
	void insertProcessArray(char * proce);
	/* Get all process running without checking PID */
	void makeListEveryProcessRunningWithoutPID();
	/* Get all process running in temp list without checking PID*/
	void makeListEveryProcessRunningTempWithoutPID();
	/* Clean the array assign empty holes */
	void cleanArray(char * arrayToClean[MAXNUMBERPROCESSES]);
	/* Check if the process exists inside of the list */
	int checkIfTheProcessExistsOnArray(char * process);
	/* Remove a specific process */
	void removeProcessOnArray(char * process);
	/* Check if one common process is a critical process*/
	int checkIfOneCommonProcessIsCriticalProcess(char * process);
	/* Check if there are new processes*/
	void checkNewProcesses();
	/* check if there are new termination processes */
	void checkTerminationProcesses();
	/* Check if there is any process activate or deactivate */
	void checkAnyActivationOrTerminationProcess();

/* FUNCTION FOR COMMON PROCESSES */
	/* Remove blanks from strings */
	char* deblank(char* input) {
		int i, j;
		char *output = input;

		for (i = 0, j = 0; i < strlen(input); i++, j++) {
			if (input[i] != ' ')
				output[j] = input[i];
			else
				j--;
		}
		output[j] = 0;
		return output;
	}

/* Print array of processes main*/
void printArray1() {
	int z;

	/* print the list of processes */
	printf("List of processes(main): \n");
	for (z = 0; z <= numberOfCommonProcesses; z++) {
		printf("%s pos: %d", arrayOfCommonProcesses[z], z);
	}
	printf("\n");
	fflush(stdout);
}

/* Print array of processes temp*/
void printArray2() {
	int z;

	/* print the list of processes */
	printf("List of processes(temp): \n");
	for (z = 0; z <= numberOfCommonProcessesTemp; z++) {
		printf("%s pos: %d", arrayOfCommonProcessesTemp[z], z);
	}
	printf("\n");
	fflush(stdout);
}



/* Get all process running without checking PID */
void makeListEveryProcessRunningWithoutPID() {
	char line[MAXLENGHTLINE];
	FILE *fpv6;

	/* Run command to obtend the list ob processes running */
	fpv6 =
			popen(
					"ps aux | awk '{printf $11 \" \\n \"}' | uniq -u | head -n -7 | tail -n +2",
					"r");

	/* Error open file */
	if (fpv6 == NULL ) {
		printf(
				"Failed to run command in makeListEveryProcessRunningWithoutPID\n");
		fflush(stdout);
	} else {

		/* Read the output a line at a time -output it. */
		while (fgets(line, sizeof (line), fpv6) != NULL ) {

			// Memory allocation for each process
			arrayOfCommonProcesses[currentPositionMainList] = malloc(
					strlen(line) + 1);
			// copy the process into array
			strcpy(arrayOfCommonProcesses[currentPositionMainList], line);
			numberOfCommonProcesses = currentPositionMainList;
			//insertProcessArray(line);
			currentPositionMainList++;
		}
	}
	fclose(fpv6);
}



/* Get all process running in temp list without checking PID*/
void makeListEveryProcessRunningTempWithoutPID() {
	char line[MAXLENGHTLINE];
	FILE *fpv7;

	/* Run command to obten the list of processes running */
	fpv7 =
			popen(
					"ps aux | awk '{printf $11 \" \\n \"}' | uniq -u | head -n -7 | tail -n +2",
					"r");

	/* Error open file */
	if (fpv7 == NULL ) {
		printf(
				"Failed to run command in makeListEveryProcessRunningTempWithoutPID\n");
		fflush(stdout);
	} else {

		/* Read the output a line at a time -output it. */
		while (fgets(line, sizeof (line), fpv7) != NULL ) {
			// Memory allocation for each process
			arrayOfCommonProcessesTemp[currentPositionTempList] = malloc(
					strlen(line) + 1);
			// copy the process into array
			strcpy(arrayOfCommonProcessesTemp[currentPositionTempList], line);
			numberOfCommonProcessesTemp = currentPositionTempList;
			currentPositionTempList++;
		}
	}
	fclose(fpv7);
}



/* Clean the array assign empty holes */
void cleanArray(char * arrayToClean[MAXNUMBERPROCESSES]) {
	int l;

	for (l = 0; l < MAXNUMBERPROCESSES; l++) {
		arrayToClean[l]="";
	}
	currentPositionTempList = 0;
}



/* Check if the process exists inside of the list */
int checkIfTheProcessExistsOnArray(char * process) {
	int found = 0;
	int i;

	for (i = 0; i <= numberOfCommonProcesses; i++) {
		//printf("Comparing ---%s--- and ---%s----\n", process, arrayOfCommonProcesses[i]);
		if (strcmp(process, arrayOfCommonProcesses[i]) == 0) {
			found = 1;
		}
	}
	/* The process exists within array */
	if (found == 1) {
		return 1;
	} else {
		if (found == 0) {
			return 0;
		}
	}
	return 0;
}

/*Insert process in Array */
void insertProcessArray(char * proce) {
	int emptyHole = 0;
	int positionEmptyHole = 0;
	int p;

	// search if there is an empty hole to insert the process
	for (p = 0; p < numberOfCommonProcesses; p++) {
		// if the array has an empty hole
		if (strcmp(arrayOfCommonProcesses[p], "") == 0) {
			emptyHole = 1;
			positionEmptyHole = p;
		}
	}
	// if there is an empty hole it inserts the process on it
	if (emptyHole == 1) {
		// Memory allocation for each process
		arrayOfCommonProcesses[positionEmptyHole] = malloc(strlen(proce) + 1);
		// copy the process into array
		strcpy(arrayOfCommonProcesses[positionEmptyHole], proce);
	} else {
		// if there is not an empty hole it insert the process in a new position
		if (emptyHole == 0) {
			// Memory allocation for each process
			arrayOfCommonProcesses[currentPositionMainList] = malloc(
					strlen(proce) + 1);
			// copy the process into array
			strcpy(arrayOfCommonProcesses[currentPositionMainList], proce);
			numberOfCommonProcesses = currentPositionMainList;
			currentPositionMainList++;
		}
	}
}


/* Remove a specific process */
void removeProcessOnArray(char * process) {
	int n;

	for (n = 0; n <= numberOfCommonProcesses; n++) {
		/* if the process is found */
		if ((strcmp(arrayOfCommonProcesses[n], process) == 0)
				&& (strcmp(process, "") != 0)) {
			int f;
			/* assigning the next process to the current position to remove */
			for (f = n; f <= numberOfCommonProcesses; f++) {
				if (f != numberOfCommonProcesses) {
					arrayOfCommonProcesses[f] = arrayOfCommonProcesses[f + 1];
				} else {
					if (f == numberOfCommonProcesses) {
						arrayOfCommonProcesses[f] = "";
					}
				}
			}
		}
	}
}

/* Remove \n from a string */
char* removeNewLine(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if(p) {
    	char *p2 = p;
    	while(*s != '\0') {
    		if(*s != '\t' && *s != '\n') {
    			*p2++ = *s++;
    		} else {
    			++s;
    		}
    	}
    	*p2 = '\0';
    }
    return p;
}

/* Remove \n from a string v2 */
char* removeNewLineV2(char *s){
	//char str[80];
	int len;
	//FILE *fp;

	//fgets(s,sizeof(s),fp);
	// remove newline
	len = strlen(s);
	if( s[len-1] == '\n' )
	    s[len-1] = 0;
	return s;
}


/* Check if one common process is a critical process*/
int checkIfOneCommonProcessIsCriticalProcess(char * process) {
	int foundOneProcess = 0; // found==0 the process is not found and found==1 the process is found
	int p;


	// Remove blancks of the process for comparing
	char *temp1 = deblank(process);

	// Remove \n of the process for comparing
	temp1 = removeNewLineV2(temp1);


	/* try to find the process inside of arrayOfProcesses */
	for (p = 0; p < numberOfProcesses; p++) { // care with numberOfProcesses
		//printf("Comparing p1=--%s-- with p2=--%s--\n", temp1, arrayOfProcesses[p]);
		if (strcmp(temp1, arrayOfProcesses[p]) == 0) {
			foundOneProcess = 1;

		}
	}

	if (foundOneProcess == 1) {
		return 1;
	} else {
		if (foundOneProcess == 0) {
			return 0;
		}
	}
	return 0;
}

/* Check if there are new processes*/
void checkNewProcesses() {
	int s;
	int d;
	int found = -1;
	char temp_string[MAX_LENGHT_TEMP_STRING];

	// check if there is a new process to include in the main list of processes
	for (s = 0; s <= numberOfCommonProcessesTemp; s++) {
		for (d = 0; d <= numberOfCommonProcesses; d++) {
			if (strcmp(arrayOfCommonProcessesTemp[s], arrayOfCommonProcesses[d])
					== 0) {
				found = 0;
			}
		}
		/* if found==-1 outside loop means there is a new process*/
		if (found == -1) {
			printf("THERE ARE A NEW PROCESS");
			printf("p: -----%s-----\n", arrayOfCommonProcessesTemp[s]);
			if ((checkIfTheProcessExistsOnArray(arrayOfCommonProcessesTemp[s])
					== 0)) {
				char * cpyToCompare=malloc(strlen(arrayOfCommonProcessesTemp[s]) + 1);
				strcpy(cpyToCompare, arrayOfCommonProcessesTemp[s]);
				if (checkIfOneCommonProcessIsCriticalProcess(
						cpyToCompare) == 0) {

					printf("Common process activate: %---s---\n",
							arrayOfCommonProcessesTemp[s]);

					/* Event detail information */
					snprintf(temp_string, MAX_LENGHT_TEMP_STRING, "%s\n",
							arrayOfCommonProcessesTemp[s]);
					//transferEvent(my_id, COMMON_PROCESS_ON, temp_string);
					printf("Number of processes in the list %d\n",
							numberOfCommonProcesses);

					insertProcessArray(arrayOfCommonProcessesTemp[s]);
					fflush(stdout);
					//printArray(arrayOfCommonProcesses);
					//printArray();
					free(cpyToCompare);

				}
			}
		}
		found = -1;
	}
}
/* check if there are new termination processes */
void checkTerminationProcesses() {
	int h;
	int k;
	int found = -1;
	char temp_string[MAX_LENGHT_TEMP_STRING];

	// check if each process from main list is inside of temp list
	for (h = 0; h <= numberOfCommonProcesses; h++) {
		for (k = 0; k <= numberOfCommonProcessesTemp; k++) {
			if (strcmp(arrayOfCommonProcesses[h], arrayOfCommonProcessesTemp[k])
					== 0) {
				found = 0;
			}
		}
		/* if found==-1 outside loop means there is a deactivate process */
		if (strcmp(arrayOfCommonProcesses[h], "") != 0) {
			if (found == -1) {
				char * cpyToCompare=malloc(strlen(arrayOfCommonProcesses[h]) + 1);
								strcpy(cpyToCompare, arrayOfCommonProcesses[h]);
				if (checkIfOneCommonProcessIsCriticalProcess(
						cpyToCompare) == 0) {
					printf("Common termination process: ---%s--\n",
							arrayOfCommonProcesses[h]);
					fflush(stdout);
					/* Event detail information */
					snprintf(temp_string, MAX_LENGHT_TEMP_STRING, "%s\n",
							arrayOfCommonProcesses[h]);
					//transferEvent(my_id, COMMON_PROCESS_OFF, temp_string);
					printf("Number of processes in the list %d\n",
							numberOfCommonProcesses);
					removeProcessOnArray(arrayOfCommonProcesses[h]);

				}
				free(cpyToCompare);
			}
		}
		found = -1;
	}
}

/* Check if there is any process activate or deactivate */
void checkAnyActivationOrTerminationProcess() {
	makeListEveryProcessRunningTempWithoutPID();
	//printArray1();
	//printArray2();
	printf("NumberProcessesMain: %d NumberProcessesTemp: %d\n", numberOfCommonProcesses, numberOfCommonProcessesTemp);
	checkNewProcesses();
	checkTerminationProcesses();
	cleanArray(arrayOfCommonProcessesTemp);
}

void initializeArrayOfProccesesOnlyTesting(){
	// Reserve memory for two processes
	arrayOfProcesses[0] = malloc(strlen("iceweasel") + 1);
	strcpy(arrayOfProcesses[0], "iceweasel");

	arrayOfProcesses[1] = malloc(strlen("gcalctool") + 1);
	strcpy(arrayOfProcesses[1], "gcalctool");

}

int main(int argc, char *argv[]) {
	printf("we going to improve critical process is not common process\n");
	initializeArrayOfProccesesOnlyTesting();
	makeListEveryProcessRunningWithoutPID();
	//printArray(arrayOfCommonProcesses);
	for (;;){
		checkAnyActivationOrTerminationProcess();
		//printArray1();
		sleep(3);
		//printf("NumberCommon: %d and numberTemp: %d\n", numberOfCommonProcesses, numberOfCommonProcessesTemp);

	}
	return 0;
}

