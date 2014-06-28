/*
 ============================================================================
 Name        : CheckAnyProcessActivateOrTermination.c
 Author      : Alberto.R.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

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

/* Constants */
#define MAXNUMBERPROCESSES 200
#define MAXLENGHTLINE 200

/* Global variables */
char *arrayOfCommonProcesses[MAXNUMBERPROCESSES];
int currentPosition = -1;
int numberOfProcesses = 0;

int p = 0;
char *arrayOfCommonProcessesTemp[MAXNUMBERPROCESSES];
int numberOfProcessesTemp = 0;

/* Remove blanks from strings */
char* deblank(char* input) {
	int i, j;
	char *output = input;
	for (i = 0, j = 0; i <= strlen(input); i++, j++) {
		if (input[i] != ' ')
			output[j] = input[i];
		else
			j--;
	}
	output[j] = 0;
	return output;
}
/* Print array of processes */
void printArray(char *arrayOfProcesses[MAXNUMBERPROCESSES]) {
	int z;
	/* print the list of processes */
	printf("List of processes: \n");
	for (z = 0; z <= numberOfProcesses; z++) {
		printf("%s pos: %d", arrayOfProcesses[z], z);
	}
	printf("\n");
	fflush(stdout);
}

/*Insert process in Array */
void insertProcessArray(char * proce) {

	int emptyHole = 0;
	int positionEmptyHole = 0;
	int p;

	// search if there is an empty hole to insert the process
	for (p = 0; p < numberOfProcesses; p++) {
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
			currentPosition++;
			// Memory allocation for each process
			arrayOfCommonProcesses[currentPosition] = malloc(strlen(proce) + 1);
			// copy the process into array
			strcpy(arrayOfCommonProcesses[currentPosition], proce);
			numberOfProcesses = currentPosition;
		}
	}
}

/* Get all process running without checking PID */
void makeListEveryProcessRunningWithoutPID() {
	char line[MAXLENGHTLINE];

	FILE *fp;
	fp =
			popen(
					"ps aux | awk '{printf $11 \" \\n \"}' | uniq -u | head -n -7 | tail -n +2",
					"r");

	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		//insertProcessArray(line);
		currentPosition++;
		// Memory allocation for each process
		arrayOfCommonProcesses[currentPosition] = malloc(strlen(line) + 1);
		// copy the process into array
		strcpy(arrayOfCommonProcesses[currentPosition], line);
		numberOfProcesses = currentPosition;
	}
}

/* Get all process running checking PID */
void makeListEveryProcessRunningCheckingPID() {
	char line[MAXLENGHTLINE];
	FILE *fp;

	fp = popen("ps aux | awk '{printf $11 \" \" $2 \"\\n\"}' ", "r");

	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {

		int processIgnored = 0; // processIgnored==0 when the process is not ignored and processIgnored==1 when the process will be ignored
		/* Ignore ps process */
		if ((line[0] == 'p') && (line[1] = 's')) {
			processIgnored = 1;
		}
		/* Ignore sh process */
		if ((line[0] == 's') && (line[1] == 'h')) {
			processIgnored = 1;
		}
		/* Ignore [sh] process */
		if ((line[0] == '[') && (line[1] == 's') && (line[2] == 'h')
				&& (line[3] == ']')) {
			processIgnored = 1;
		}
		if (processIgnored == 0) {
			// insert process into array
			currentPosition++;
			// Memory allocation for each process
			arrayOfCommonProcesses[currentPosition] = malloc(strlen(line) + 1);
			// copy the process into array
			strcpy(arrayOfCommonProcesses[currentPosition], line);
			numberOfProcesses = currentPosition;
		}
	}
}

/* Get all process running in temp list without checking PID*/
void makeListEveryProcessRunningTempWithoutPID() {
	char line[MAXLENGHTLINE];

	FILE *fp;
	fp =
			popen(
					"ps aux | awk '{printf $11 \" \\n \"}' | uniq -u | head -n -7 | tail -n +2",
					"r");

	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		// Memory allocation for each process
		arrayOfCommonProcessesTemp[p] = malloc(strlen(line) + 1);
		// copy the process into array
		strcpy(arrayOfCommonProcessesTemp[p], line);
		numberOfProcessesTemp = p;
		p++;
	}
}

/* Get all process running in temp list checking PID*/
void makeListEveryProcessRunningTempCheckingPID() {
	char line[MAXLENGHTLINE];

	FILE *fp;

	fp = popen("ps aux | awk '{printf $11 \" \" $2 \"\\n\"}' ", "r");

	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		int processIgnored = 0; // processIgnored==0 when the process is not ignored and processIgnored==1 when the process will be ignored
		/* Ignore ps process */
		if ((line[0] == 'p') && (line[1] = 's')) {
			processIgnored = 1;
		}
		/* Ignore sh process */
		if ((line[0] == 's') && (line[1] == 'h')) {
			processIgnored = 1;
		}
		/* Ignore [sh] process */
		if ((line[0] == '[') && (line[1] == 's') && (line[2] == 'h')
				&& (line[3] == ']')) {
			processIgnored = 1;
		}
		if (processIgnored == 0) {
			// Memory allocation for each process
			arrayOfCommonProcessesTemp[p] = malloc(strlen(line) + 1);
			// copy the process into array
			strcpy(arrayOfCommonProcessesTemp[p], line);
			numberOfProcessesTemp = p;
			p++;
		}
	}
}

/* Clean the array assign empty holes */
void cleanArray(char * arrayToClean[MAXNUMBERPROCESSES]) {
	int l;
	for (l = 0; l < MAXNUMBERPROCESSES; l++) {
		arrayToClean[l] = " ";
	}
	p = 0;
}
/* Check if the process exists inside of the list */
int checkIfTheProcessExistsOnArray(char * process) {
	int found = 0;
	int i;

	for (i = 0; i <= numberOfProcesses; i++) {
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

/* Remove a specific process */
void removeProcessOnArray(char * process) {
	int n;
	for (n = 0; n <= numberOfProcesses; n++) {
		/* if the process is found */
		if ((strcmp(arrayOfCommonProcesses[n], process) == 0)
				&& (strcmp(process, "") != 0)) {
			int f;
			/* assigning the next process to the current position to remove */
			for (f = n; f <= numberOfProcesses; f++) {
				if (f != numberOfProcesses) {
					arrayOfCommonProcesses[f] = arrayOfCommonProcesses[f + 1];
				} else {
					if (f == numberOfProcesses) {
						arrayOfCommonProcesses[f] = "";
					}
				}
			}
		}
	}
}
/* Check if there are new processes*/
void checkNewProcesses() {
	int s;
	int d;
	int found = -1;
	// check if there is a new process to include in the main list of processes
	for (s = 0; s < numberOfProcessesTemp; s++) {
		for (d = 0; d < numberOfProcesses; d++) {
			if (strcmp(arrayOfCommonProcessesTemp[s], arrayOfCommonProcesses[d])
					== 0) {
				found = 0;
			}
		}
		/* if found==-1 outside loop means there is a new process*/
		if (found == -1) {
			if (checkIfTheProcessExistsOnArray(arrayOfCommonProcessesTemp[s])
					== 0) {
				printf("New process activate: %s\n",
						arrayOfCommonProcessesTemp[s]);
				fflush(stdout);
				insertProcessArray(arrayOfCommonProcessesTemp[s]);
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

	// check if each process from main list is inside of temp list
	for (h = 0; h <= numberOfProcesses; h++) {
		for (k = 0; k <= numberOfProcessesTemp; k++) {
			if (strcmp(arrayOfCommonProcesses[h], arrayOfCommonProcessesTemp[k])
					== 0) {
				found = 0;
			}
		}
		/* if found==-1 outside loop means there is a deactivate process */
		if (strcmp(arrayOfCommonProcesses[h], "") != 0) {
			if (found == -1) {
				printf("Termination process: %s\n", arrayOfCommonProcesses[h]);
				fflush(stdout);
				removeProcessOnArray(arrayOfCommonProcesses[h]);
			}
		}
		found = -1;
	}
}
/* Check if there is any process activate or deactivate */
void checkAnyActivationOrTerminationProcess() {
	makeListEveryProcessRunningTempCheckingPID();
	checkNewProcesses();
	checkTerminationProcesses();
	cleanArray(arrayOfCommonProcessesTemp);
}

int main(void) {
	printf("we going to check any process activate or deactivate \n"); /* prints we going to check any process activation or termination */
	fflush(stdout);
	makeListEveryProcessRunningCheckingPID(); // make a snapshot of the processes running at the beginning
	for (;;) {
		checkAnyActivationOrTerminationProcess();
		sleep(3);
	}
	return EXIT_SUCCESS;

}
