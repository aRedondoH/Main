/*
 * snok_agent.h
 *
 *  Created on: May 27, 2014
 *      Author: secnok
 */

#ifndef SNOK_AGENT_H_
#define SNOK_AGENT_H_



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


/* Say to compiler that the global variables are declared */
extern int my_id;
extern char * detector_ip;
extern long double threshold;
extern char * arrayOfProcesses[30];
extern int numberOfProcesses;
extern int currentlyFirewallStatus;
extern int lastFirewallStatus;
extern int currentlyCPUstate;
extern int lastCPUstate;
extern time_t lastTime;


/* Constants */
#define MAXNUMBERPROCESSES 200
#define MAXLENGHTLINE 200

extern char *arrayOfCommonProcesses[MAXNUMBERPROCESSES];
extern int currentPositionMainList;
extern int numberOfCommonProcesses;
extern int currentPositionTempList;
extern char *arrayOfCommonProcessesTemp[MAXNUMBERPROCESSES];
extern int numberOfCommonProcessesTemp;

/* Event type
 * Can be extended once we define more events */
enum detection_type {
	USB_INSERTION = 1,
	USB_REMOVAL = 2,
	CPU_EXCESS = 3,
	CPU_NORMAL = 4,
	CRITICAL_PROCESS_ON = 5,
	CRITICAL_PROCESS_OFF = 6,
	AGENT_START = 7,
	FIREWALL_ON = 8,
	FIREWALL_OFF = 9,
	IS_ALIVE = 10,
	OS_IDENTITY = 11,
	PORT_OPEN = 12,
	PROCESS_RUNNING = 18,
	COMMON_PROCESS_ON = 19,
	COMMON_PROCESS_OFF = 20
} event_type;

/* Functions */
/* SNOK Agent need to run with root privileges */
/* GENERAL FUNCTION HEADERS */
/* Agent prepares a start message to send server */
int send_start_message(int id);
/* Check the CPU_threshold, processes, firewall initial state*/
void checkInitialState(long double previous_load, int previous_running_state[]);
/* Get arguments from the config file */
int readArgumentsFromConfigFile();
/* Check each 5 minutes is alive */
void checkIsAlive();

#endif /* SNOK_AGENT_H_ */
