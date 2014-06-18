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
	int is_process_state_change(char *process_name, int *previous_running_state);
	/* Return process id that matches with process name */
	pid_t get_process_id_by_name(char *process_name);
	/* Remove blanks from strings */
	char* deblank(char* input);
	/* Parsing the processes lines */
	void parsingLine(char line[MAXLENGHTLINE]);
	/* Get all process running */
	void listEveryProcessRunning();

/* FUNCTION HEADERS COMMON PROCESSES */
	/* Print array of processes */
	void printArray(char *arrayOfProcesses[MAXNUMBERPROCESSES]);
	/*Insert process in Array */
	void insertProcessArray(char * proce);
	/* Get all process running without checking PID */
	void makeListEveryProcessRunningWithoutPID();
	/* Get all process running checking PID */
	void makeListEveryProcessRunningCheckingPID();
	/* Get all process running in temp list without checking PID*/
	void makeListEveryProcessRunningTempWithoutPID();
	/* Get all process running in temp list checking PID*/
	void makeListEveryProcessRunningTempCheckingPID();
	/* Clean the array assign empty holes */
	void cleanArray(char * arrayToClean[MAXNUMBERPROCESSES]);
	/* Check if the process exists inside of the list */
	int checkIfTheProcessExistsOnArray(char * process);
	/* Remove a specific process */
	void removeProcessOnArray(char * process);
	/* Check if there are new processes*/
	void checkNewProcesses();
	/* check if there are new termination processes */
	void checkTerminationProcesses();
	/* Check if there is any process activate or deactivate */
	void checkAnyActivationOrTerminationProcess();

#endif /* PROCESSES_H_ */
