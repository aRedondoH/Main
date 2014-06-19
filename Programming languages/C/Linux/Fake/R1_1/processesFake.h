/*
 * processes.h
 *
 *  Created on: May 27, 2014
 *      Author: secnok
 */

#ifndef PROCESSES_H_
#define PROCESSES_H_

#include <unistd.h>
#include <sys/types.h>

#define MAXNUMBERPROCESSES 500
#define MAXLENGHTLINE 200


/* PROCESSES FUNCTIONS HEADERS */
/* FUNCTION HEADERS CRITICAL PROCESSES */
	/* Return 1 if process state changes, 0 otherwise */
	int is_process_state_changeFake(char *process_name, int *previous_running_state);
	/* Return process id that matches with process name */
	pid_t get_process_id_by_nameFake(char *process_name);
	/* Remove blanks from strings */
	char* deblankFake(char* input);
	/* Parsing the processes lines */
	void parsingLineFake(char line[MAXLENGHTLINE]);
	/* Get all process running */
	void listEveryProcessRunningFake();

/* FUNCTION HEADERS COMMON PROCESSES */
	/* Print array of processes */
	void printArrayFake(char *arrayOfProcesses[MAXNUMBERPROCESSES]);
	/*Insert process in Array */
	void insertProcessArrayFake(char * proce);
	/* Get all process running without checking PID */
	void makeListEveryProcessRunningWithoutPIDFake();
	/* Get all process running checking PID */
	void makeListEveryProcessRunningCheckingPIDFake();
	/* Get all process running in temp list without checking PID*/
	void makeListEveryProcessRunningTempWithoutPIDFake();
	/* Get all process running in temp list checking PID*/
	void makeListEveryProcessRunningTempCheckingPIDFake();
	/* Clean the array assign empty holes */
	void cleanArrayFake(char * arrayToClean[MAXNUMBERPROCESSES]);
	/* Check if the process exists inside of the list */
	int checkIfTheProcessExistsOnArrayFake(char * process);
	/* Remove a specific process */
	void removeProcessOnArrayFake(char * process);
	/* Check if there are new processes*/
	void checkNewProcessesFake();
	/* check if there are new termination processes */
	void checkTerminationProcessesFake();
	/* Check if there is any process activate or deactivate */
	void checkAnyActivationOrTerminationProcessFake();

#endif /* PROCESSES_H_ */
