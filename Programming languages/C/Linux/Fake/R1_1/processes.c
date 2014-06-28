/*
 * processes.c
 *
 *  Created on: May 27, 2014
 *      Author: secnok
 */

#include "processes.h"
#include "snok_agent.h"
#include "connection.h"

#include <dirent.h>



/* Common processes */
char *arrayOfCommonProcesses[MAXNUMBERPROCESSES];
int currentPositionMainList = -1;
int numberOfCommonProcesses = 0;

int currentPositionTempList = 0;
char *arrayOfCommonProcessesTemp[MAXNUMBERPROCESSES];
int numberOfCommonProcessesTemp = 0;


/* --------------------------------------------*/
/* ----------- PROCESSES FUNCTIONS ------------*/
/* --------------------------------------------*/

/* FUNCTIONS FOR CRITICAL PROCESSES*/
/* Return 1 if process state changes, 0 otherwise */
int is_process_state_change(char *process_name, int *previous_running_state) {

	char temp_string[100];
	int current_running_state;
	/* Return 1 if the process state changes from running to not running
	 * or vice versa, 0 otherwise */
	int is_process_state_change = 0;
	long pid;

	pid = (long) get_process_id_by_name(process_name);
	if (pid < 0) {
		/* The process does not run for now */
		current_running_state = 0;
		if (*previous_running_state != current_running_state) {
			/* State changes */
			is_process_state_change = 1;

			/* Event detail information */
			snprintf(temp_string, 100, "Process: %s is not running \n",
					process_name);
			transferEvent(my_id, CRITICAL_PROCESS_OFF, temp_string);

			printf("Process: %s is not running \n", process_name);
			fflush(stdout);

		} else {
			is_process_state_change = 0;
		}
	} else {
		/* The process runs for now */
		current_running_state = 1;
		if (*previous_running_state != current_running_state) {
			/* State changes */
			is_process_state_change = 1;

			/* Event detail information */
			snprintf(temp_string, 100, "Process: %s is running \n",
					process_name);
			transferEvent(my_id, CRITICAL_PROCESS_ON, temp_string);
			printf("Process: %s is running with PID: %ld\n", process_name, pid);
			fflush(stdout);

		} else {
			is_process_state_change = 0;
		}
	}

	/* Update the latest running state of the process */
	*previous_running_state = current_running_state;

	return is_process_state_change;
}

/* Return process id that matches with process name */
pid_t get_process_id_by_name(char *process_name) {

	DIR *dir;
	struct dirent *ent;
	char buf[1024];
	char pname[200] = { 0, };
	FILE *fp = NULL;

	/* Open /proc to read information */
	if (!(dir = opendir("/proc"))) {
		perror("can't open /proc");
		return -1;
	}

	while ((ent = readdir(dir)) != NULL ) {
		/* process id represents as directory name */
		long lpid = atol(ent->d_name);
		if (lpid < 0)
			continue;
		/* open stat file to read information */
		snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);
		fp = fopen(buf, "r");
		if (fp) {
			int nchars = fread(pname, 1, 200, fp);

			int start, end;
			for (end = 0; end < nchars && pname[end] != '\0'; end++) { /* empty on purpose */
			}
			for (start = end; start >= 0 && pname[start] != '/'; --start) { /* empty on purpose */
			}
			start++;

			if (nchars > 0) {
				/* the process is running */
				/* note that we only find the first instance of the process with smallest pid
				 * there may be more than one instances of the process that is running */
				if (!strcmp(&pname[start], process_name)) {
					fclose(fp);
					closedir(dir);
					return (pid_t) lpid;
				}
			}
			fclose(fp);
		}
	}

	closedir(dir);
	return -1;
}

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

/* Parsing the processes lines */
void parsingLine(char line[200]) {
	// Parsing processes thats begin with '['
	if (line[1] == '[') {
		line[1] = ' ';
		char * stringToCut = strtok(line, "]");
		stringToCut = deblank(stringToCut);
		printf("%s\n", stringToCut);
		transferEvent(my_id, PROCESS_RUNNING, stringToCut);
	} else if (line[1] == '/') { // Parsing processes thats begin with '/'
		char *processToPrint;
		char *stringToCut = strtok(line, "/");
		while (stringToCut != NULL ) {
			processToPrint = stringToCut;
			stringToCut = strtok(NULL, "/");
		}
		printf("%s", processToPrint);
		transferEvent(my_id, PROCESS_RUNNING, processToPrint);
	} else {
		// if the process does not need to parsing do nothing
		printf("%s", deblank(line));
		transferEvent(my_id, PROCESS_RUNNING, deblank(line));
	}

}
/* Get all process running */
void listEveryProcessRunning() {
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
		parsingLine(line);
	}
}

/* FUNCTION FOR COMMON PROCESSES */
/* Print array of processes */
void printArray(char *arrayOfProcesses[MAXNUMBERPROCESSES]) {
	int z;
	/* print the list of processes */
	printf("List of processes: \n");
	for (z = 0; z <= numberOfCommonProcesses; z++) {
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
			currentPositionMainList++;
			// Memory allocation for each process
			arrayOfCommonProcesses[currentPositionMainList] = malloc(strlen(proce) + 1);
			// copy the process into array
			strcpy(arrayOfCommonProcesses[currentPositionMainList], proce);
			numberOfCommonProcesses = currentPositionMainList;
		}
	}
}

/* Get all process running without checking PID */
void makeListEveryProcessRunningWithoutPID() {
	char line[MAXLENGHTLINE];

	FILE *fpv6;
	fpv6 =
			popen(
					"ps aux | awk '{printf $11 \" \\n \"}' | uniq -u | head -n -7 | tail -n +2",
					"r");

	/* Error open file */
	if (fpv6 == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fpv6) != NULL ) {
		//insertProcessArray(line);
		currentPositionMainList++;
		// Memory allocation for each process
		arrayOfCommonProcesses[currentPositionMainList] = malloc(strlen(line) + 1);
		// copy the process into array
		strcpy(arrayOfCommonProcesses[currentPositionMainList], line);
		numberOfCommonProcesses = currentPositionMainList;
	}
}

/* Get all process running checking PID */
void makeListEveryProcessRunningCheckingPID() {
	char line[MAXLENGHTLINE];
	FILE *fpv10;

	fpv10 = popen("ps aux | awk '{printf $11 \" \" $2 \"\\n\"}' ", "r");

	/* Error open file */
	if (fpv10 == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fpv10) != NULL ) {

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
			currentPositionMainList++;
			// Memory allocation for each process
			arrayOfCommonProcesses[currentPositionMainList] = malloc(strlen(line) + 1);
			// copy the process into array
			strcpy(arrayOfCommonProcesses[currentPositionMainList], line);
			numberOfCommonProcesses = currentPositionMainList;
		}
	}
}

/* Get all process running in temp list without checking PID*/
void makeListEveryProcessRunningTempWithoutPID() {
	char line[MAXLENGHTLINE];

	FILE *fpv7;
	fpv7 =
			popen(
					"ps aux | awk '{printf $11 \" \\n \"}' | uniq -u | head -n -7 | tail -n +2",
					"r");

	/* Error open file */
	if (fpv7 == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fpv7) != NULL ) {
		// Memory allocation for each process
		arrayOfCommonProcessesTemp[currentPositionTempList] = malloc(strlen(line) + 1);
		// copy the process into array
		strcpy(arrayOfCommonProcessesTemp[currentPositionTempList], line);
		numberOfCommonProcessesTemp = currentPositionTempList;
		currentPositionTempList++;
	}
}

/* Get all process running in temp list checking PID*/
void makeListEveryProcessRunningTempCheckingPID() {
	char line[MAXLENGHTLINE];

	FILE *fpv20;

	fpv20 = popen("ps aux | awk '{printf $11 \" \" $2 \"\\n\"}' ", "r");

	/* Error open file */
	if (fpv20 == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fpv20) != NULL ) {
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
			arrayOfCommonProcessesTemp[currentPositionTempList] = malloc(strlen(line) + 1);
			// copy the process into array
			strcpy(arrayOfCommonProcessesTemp[currentPositionTempList], line);
			numberOfCommonProcessesTemp = currentPositionTempList;
			currentPositionTempList++;
		}
	}
}

/* Clean the array assign empty holes */
void cleanArray(char * arrayToClean[MAXNUMBERPROCESSES]) {
	int l;
	for (l = 0; l < MAXNUMBERPROCESSES; l++) {
		arrayToClean[l] = " ";
	}
	currentPositionTempList = 0;
}
/* Check if the process exists inside of the list */
int checkIfTheProcessExistsOnArray(char * process) {
	int found = 0;
	int i;

	for (i = 0; i <= numberOfCommonProcesses; i++) {
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
/* Check if there are new processes*/
void checkNewProcesses() {
	int s;
	int d;
	int found = -1;
	char temp_string[100];

	// check if there is a new process to include in the main list of processes
	for (s = 0; s < numberOfCommonProcessesTemp; s++) {
		for (d = 0; d < numberOfCommonProcesses; d++) {
			if (strcmp(arrayOfCommonProcessesTemp[s], arrayOfCommonProcesses[d])
					== 0) {
				found = 0;
			}
		}
		/* if found==-1 outside loop means there is a new process*/
		if (found == -1) {
			if (checkIfTheProcessExistsOnArray(arrayOfCommonProcessesTemp[s])
					== 0) {
				printf("Common process activate: %s\n",
						arrayOfCommonProcessesTemp[s]);
				fflush(stdout);
				/* Event detail information */
				snprintf(temp_string, 100, "Common process: %s has been activated \n",
						arrayOfCommonProcessesTemp[s]);
				transferEvent(my_id, COMMON_PROCESS_ON, temp_string);

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
	char temp_string[100];

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
				printf("Common termination process: %s\n", arrayOfCommonProcesses[h]);
				fflush(stdout);
				/* Event detail information */
				snprintf(temp_string, 100,
						"Common process: %s has been deactivated \n",
						arrayOfCommonProcesses[h]);
				transferEvent(my_id, COMMON_PROCESS_OFF, temp_string);
				removeProcessOnArray(arrayOfCommonProcesses[h]);
			}
		}
		found = -1;
	}
}
/* Check if there is any process activate or deactivate */
void checkAnyActivationOrTerminationProcess() {
	makeListEveryProcessRunningTempWithoutPID();
	checkNewProcesses();
	checkTerminationProcesses();
	cleanArray(arrayOfCommonProcessesTemp);
}
