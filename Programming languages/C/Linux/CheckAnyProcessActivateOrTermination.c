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

/* Global variables */
char *arrayOfProcesses[200];
int i = -1;
int numberOfProcesses = 0;

int p = 0;
char *arrayOfProcessesTemp[200];
int numberOfProcessesTemp = 0;

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

/*Insert process in array */
void insertProcessArray(char * proce) {

	i++;
	// Memory allocation for each process
	arrayOfProcesses[i] = malloc(strlen(proce) + 1);
	// copy the process into array
	strcpy(arrayOfProcesses[i], proce);
	numberOfProcesses = i;

}

/*Insert process in temp array */
void insertProcessArrayTemp(char * proce) {

	// Memory allocation for each process
	arrayOfProcessesTemp[p] = malloc(strlen(proce) + 1);
	// copy the process into array
	strcpy(arrayOfProcessesTemp[p],proce);
	numberOfProcessesTemp = p;
	p++;

}

/* Print array of processes */
void printArray(char *arrayOfProcesses[200]) {
	int z;
	/* print the list of processes */
	printf("List of processes: \n");
	for (z = 0; z < numberOfProcesses; z++) {
		printf("%s pos: %d", arrayOfProcesses[z],z);
	}
	printf("\n");
}

/* Get all process running */
void makeListEveryProcessRunning() {
	char line[200];

	FILE *fp;
	fp =
			popen(
					"ps aux | awk '{printf $11 \" \\n \"}' | uniq -u | head -n -7 | tail -n +2",
					"r");

	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		insertProcessArray(line);
	}
}

/* Get all process running */
void makeListEveryProcessRunningTemp() {
	char line[200];

	FILE *fp;
	fp =
			popen(
					"ps aux | awk '{printf $11 \" \\n \"}' | uniq -u | head -n -7 | tail -n +2",
					"r");

	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		insertProcessArrayTemp(line);
	}
}

void cleanArray(char * arrayToClean[200]) {
	int l;
	for (l = 0; l < 200; l++) {
		arrayToClean[l] = " ";
	}
	p = 0;
}

void checkNewProcesses() {
	int s;
	int d;
	int found = -1;
	for (s = 0; s < numberOfProcessesTemp; s++) {
		for (d = 0; d < numberOfProcesses; d++) {
			if (strcmp(arrayOfProcessesTemp[s], arrayOfProcesses[d]) == 0) {
				found = 0;
			}
		}
		/* if found==-1 outside loop means there is a new process*/
		if (found == -1) {
			printf("New process activate: %s\n", arrayOfProcessesTemp[s]);
			insertProcessArray(arrayOfProcessesTemp[s]);
		}
		found = -1;
	}
}

void removeProcessOnArray(char * process) {
	int n;
	for (n = 0; n < numberOfProcesses; n++) {
		/* if the process is found */
		if (strcmp(arrayOfProcesses[n], process) == 0) {
			int f;
			/* assigning the next process to the current position to remove */
			for (f = n; f < numberOfProcesses; f++) {
				arrayOfProcesses[f] = arrayOfProcesses[f + 1];
			}
		}
	}
}

void checkTerminationProcesses() {
	int h;
	int k;
	int found = -1;
	for (h = 0; h < numberOfProcesses; h++) {
		for (k = 0; k < numberOfProcessesTemp; k++) {
			if (strcmp(arrayOfProcesses[h], arrayOfProcessesTemp[k]) == 0) {
				found = 0;
			}
		}
		/* if found==-1 outside loop means there is a termination process */
		if (found == -1) {
			printf("Termination process: %s\n", arrayOfProcesses[h]);
			removeProcessOnArray(arrayOfProcesses[h]);

		}
		found = -1;
	}
}

int main(void) {
	puts("we going to check any process activation or termination \n"); /* prints we going to check any process activation or termination */
	makeListEveryProcessRunning();
	for (;;) {
		makeListEveryProcessRunningTemp();
		checkNewProcesses();
		//checkTerminationProcesses();
		printArray(arrayOfProcesses);
		sleep(3);
		cleanArray(arrayOfProcessesTemp);
	}
	return EXIT_SUCCESS;

}
