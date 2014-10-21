/*
 ============================================================================
 Name        : MethodToSwithOffAgentItself.c
 Author      : Alberto.R.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/*Overload cpu*/
#include <time.h>
#include <omp.h>


/* Constants */
#define MAXLENGHTLINE 200

struct Agent_info {
	int processPID;
	char agentName[MAXLENGHTLINE];
	int cpuUsage;
};

struct Agent_info aInfo;
int p=3;

void *switchOffAgentIfNecessary( void *ptr);


/* if Agent needs to switch off return 1
 * if Agent does not need to switch off return 0 */
int determineIfAgentNeedToSwitchOff(int currentCpuUsage, int maxCpuUsage) {
	int switchOff = 0;
	/* if the currentCpuUsage is higher than maxCpuUsage allow for the Agent */
	if (currentCpuUsage >= maxCpuUsage) {
		switchOff = 1;
	}
	return switchOff;
}

/*Get CPU from PID*/
int getCpuUsageFromPid(){

	char line[MAXLENGHTLINE];
		FILE *fp;
		char commandString[MAXLENGHTLINE];
		/* put the command into string*/
		sprintf(commandString, "ps aux | grep %d | head -| awk '{printf $3}'", aInfo.processPID);
		/* get the pid from process name */
		fp = popen(commandString, "r");
		/* Error open file */
		if (fp == NULL ) {
			printf("Failed to run command\n");
			fflush(stdout);
		}

		/* Read command output */
		while (fgets(line, sizeof line, fp) != NULL ) {
			aInfo.cpuUsage = atoi(line);

		}
	return aInfo.cpuUsage;
}

/* Get Agent PID and his specific CPU usage */
void getPidAndCpuFromAgentName(char agentName[MAXLENGHTLINE]) {
	char line[MAXLENGHTLINE];
	FILE *fp;
	char commandString[MAXLENGHTLINE];
	/* put the command into string*/
	sprintf(commandString, "pidof -s ./MethodToSwithOffAgentItself");
	/* get the pid from process name */
	fp = popen(commandString, "r");
	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	/* Read command output */
	while (fgets(line, sizeof line, fp) != NULL ) {
		aInfo.processPID = atoi(line);

	}
	getCpuUsageFromPid();
	printf("PID: %d, CPU: %d\n", aInfo.processPID, aInfo.cpuUsage);
	fflush(stdout);


}


void *threadOverLoad(void *arg){
	int * i;
	float * p;

	while (p == p){
	(*p++)+1.144564542315345;
	(*i++)+1;}

	return NULL;
}

void *switchOffAgentIfNecessary( void *ptr){
	for (;;) {
			getPidAndCpuFromAgentName(aInfo.agentName);

			if (determineIfAgentNeedToSwitchOff(aInfo.cpuUsage,80)==1){
				printf("The Agent has anomalous behaviour it will switch off itself \n");
				exit(1);
			}
			sleep(2);
		}
	return NULL;
}

int main(void) {
	puts("we going to switch off the Agent "); /* prints we going to switch off the Agent  */
	const char * message1="Thread 1";
	const char * message2="Thread 2";
	/* Copy the name of the process to be monitored */
	strcpy(aInfo.agentName, "./MethodToSwithOffAgentItself");

	/* Run functions in two threads at the same time */
	pthread_t thread1,thread2;
	   int rc,rc2;
	   long t;
	printf("Running multithreading...\n");
	rc = pthread_create(&thread1,NULL, switchOffAgentIfNecessary,(void*)message1);
	if (rc){
		printf("Error - pthread_create() pthread1 return code: %d\n", rc);
		exit(EXIT_FAILURE);
	}
	rc2 = pthread_create(&thread2,NULL,threadOverLoad, (void*)message2);
	if(rc2){
		printf("Error - pthread_create() pthread2 return code: %d\n", rc2);
	}

	printf("pthread_create() for thread 1 returns: %d\n", rc);
	printf("pthread_create() for thread 2 returns: %d\n", rc2);
	/* Run threads */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	return EXIT_SUCCESS;
}
