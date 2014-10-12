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


/*Structures for dynamic memory*/
/*process node*/
struct process_node {
	char *name;
	int processPID;
	struct process_node *next;
};

/*Dynamic list of nodes*/
typedef struct process_node dynamicListOfProcess;

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


void makeListOfEveryProcessRunningCheckkingPIDDynamicMemory() {

	dynamicListOfProcess *curr, *head;
	head = NULL;

	char line[MAXLENGHTLINE];
	FILE *fp;
	fp = popen("ps aux | awk '{printf $11 \" \" $2 \"\\n\"}' | tail -n +2 ",
			"r");

	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	char *token1;
	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		token1 = NULL;
		//printf("line: %s\n", line);
		token1 = strtok(line, " ");
		curr = (dynamicListOfProcess *) malloc(sizeof(dynamicListOfProcess));
		curr->name = malloc(strlen(line) + 1);
		strcpy(curr->name, token1);

		if (token1 != NULL ) {
			// Incrementing pointer to the next token
			token1 = strtok(NULL, " ");
			// Insert PID into struct
			curr->processPID = atoi(token1);
		}
		curr->next = head;
		head = curr;
	}
	curr = head;

	printf("I am here\n");
	int p = 0;
	while (curr) {
		printf("Process: %s, pid: %d, pos: %d\n", curr->name, curr->processPID,
				p);
		p++;
		curr = curr->next;
	}

}



/* Check if there is any process activate or deactivate */
/*void checkAnyActivationOrTerminationProcess() {
	makeListEveryProcessRunningTempCheckingPID();
	checkNewProcesses();
	checkTerminationProcesses();
	cleanArray(arrayOfCommonProcessesTemp);
}*/

int main(void) {
	printf("we going to check any process activate or deactivate \n"); /* prints we going to check any process activation or termination */
	fflush(stdout);
	//makeListEveryProcessRunningCheckingPID(); // make a snapshot of the processes running at the beginning
	//for (;;) {
	//checkAnyActivationOrTerminationProcess();
	//sleep(3);
	//}
	//makeAndPrintListOfEveryProcessRunningInListOfRegister();
	makeListOfEveryProcessRunningCheckkingPIDDynamicMemory();
	printf("Hola\n");
	return EXIT_SUCCESS;

}
