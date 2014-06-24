/*
 * snok_agent.c
 *
 *  Created on: May 27, 2014
 *      Author: A.Redondo
 */

#include "snok_agent.h"
/* Common includes */
#include "connection.h"
#include "usb.h"
#include "cpu.h"
#include "processes.h"
#include "audit.h"
#include "firewall.h"

/* Fake includes */
#include "connectionFake.h"
#include "cpuFake.h"
#include "processesFake.h"
#include "auditFake.h"
#include "firewallFake.h"
#include "face.h"

/* Global variables */
int my_id = 1;
char * detector_ip;
long double threshold;
char *arrayOfProcesses[30];
int numberOfProcesses;
/* Firewall status */
/* firewallCurrentlyStatus=1 if the firewall is running and
 firewallCurrentlyStatus=0 if the firewall is not running*/
int currentlyFirewallStatus = -1;
int lastFirewallStatus = -1;
/* CPU state */
/* currentlyCPUstate=1 if the CPU is on EXCESS state and
 currentlyCPUstate=0 if the CPU is on NORMAL state */
int currentlyCPUstate = -1;
int lastCPUstate = -1;



/* time */
time_t lastTime;

/* --------------------------------------------*/
/* ----------- GENERAL FUNCTIONS --------------*/
/* --------------------------------------------*/
/* Agent prepares a start message to send server */
int send_start_message(int id) {
	/* Event detail information */
	int ret = transferEvent(my_id, AGENT_START, "Agent starts\n");

	if (ret == -10496) { // problem with Agent or Detector certificates
		printf(
				"Problem with SSL connection, please check certificates or contact with SecureNok \n");
		return 1;
	}
	if (ret == -11776) { // problem with Agent key
		printf(
				"Problem with SSL connection, please check Agent key or contact with SecureNok \n");
		return 1;
	}
	printf("\n");
	printf("********************************************\n");
	printf("----- SNOK-Agent is running with id %d -----\n", id);
	printf("********************************************\n");
	printf("\n");
	fflush(stdout);
	return 0;
}

/* Check the CPU_threshold, processes, firewall initial state*/
void checkInitialState(long double previous_load, int previous_running_state[]) {

	printf("-------- Initial Status --------\n");

	/* Check CPU status */
	checkCpuUsage(0);

	/* Check the currently processes status */
	int i;
	for (i = 0; i < numberOfProcesses; i++) {
		is_process_state_change(arrayOfProcesses[i],
				&previous_running_state[i]);
	}

	/* Check Firewall status */
	is_firewall_enabled(1);

	/* Make snapshot of the common processes running */
	makeListEveryProcessRunningWithoutPID();

	printf("---------------------------------\n\n");
	fflush(stdout);

}

/* Get arguments from the config file */
int readArgumentsFromConfigFile() {
	FILE * cF;
	char bufr[50];
	char bufrProcesses[2000];
	char processes[1000];

	/* open the file */
	cF = fopen("config.txt", "r");
	if (cF != NULL ) {
		/* get my_id */
		fgets(bufr, 1000, cF);
		sscanf(bufr + 8, "%d", &my_id);
		printf("Agent id is %d\n", my_id);

		/* get ip_detector */
		detector_ip = (char *) malloc(15);
		fgets(bufr, 1000, cF);
		sscanf(bufr + 11, "%s", detector_ip);
		printf("Ip detector is %s\n", detector_ip);

		/* get cpuThresold */
		fgets(bufr, 1000, cF);
		double cpuT; // receive double
		sscanf(bufr + 12, "%lf", &cpuT);
		threshold = cpuT; // double to long double
		printf("Cpu thresold is %2.Lf\n", threshold);
		fflush(stdout);

		/* get processes */
		fgets(bufrProcesses, 2000, cF);
		strcpy(processes, bufrProcesses + 15);

		// Remove '\n' from processes
		char *newline = strchr(processes, '\n');
		if (newline) {
			*newline = 0;
		}

		char *token1 = NULL;

		token1 = strtok(processes, " ");
		int i = 0;

		/* obtain the processes from the string and assign to array of strings */
		while (token1 != NULL ) {

			// Memory allocation for each process
			arrayOfProcesses[i] = malloc(strlen(token1) + 1);

			strcpy(arrayOfProcesses[i], token1);
			if (token1 != NULL ) {
				token1 = strtok(NULL, " ");
				i++;
			}

		}
		numberOfProcesses = i;
		printf("The number of processes is %d\n", numberOfProcesses);
		/* print the list of processes */
		printf("List of processes: ");
		for (i = 0; i < numberOfProcesses; i++) {
			printf("%s ", arrayOfProcesses[i]);
		}
		printf("\n");

	} else {
		printf("Error open config file\n ");
	}
	/* if my_id or threshold is incorrect the program will stop */
	if ((my_id < 1 || my_id > 100) || (threshold < 0 || threshold > 100)) {
		printf("Any argument is incorrect, please insert the correct values\n");
		return 1;
	}
	return 0;

}

/* Check each 10 minutes is alive */
void checkIsAlive() {
	/* give the currently seconds */
	time_t sec = time(NULL );
	/* obtain the seconds spent */
	time_t countDownSeconds = sec - lastTime;
	long int intCountDownSeconds = (long int) countDownSeconds;
	long int stopCountDown = 60 * 10; // how much seconds we need to check (600sec)

	char tempMsg[150];
	snprintf(tempMsg, 150, "Agent is alive with id %d", my_id);
	/* send the event if each 5 minutes */
	if (intCountDownSeconds >= stopCountDown) {
		printf("%s\n", tempMsg);
		lastTime = time(NULL );
		transferEvent(my_id, IS_ALIVE, tempMsg);

		// Check audit function
		/* Array empty for our purpose */
		int emptyArray[numberOfProcesses];
		int ret = audit(emptyArray);
		if (ret != 0) {
			printf("Error %d in Audit function\n", ret);
		}
	}

}

void runAgentWithNormalBehaviour(){

	/* check the currently time at the beginning */
		lastTime = time(NULL );

		/* Declarations */
		/* Initial CPU load, used to decide if CPU events happen
		 * if new load and initial load are in two sides of the threshold
		 * then CPU usage state changes */
		long double initial_load = 0;
		/* Parameter for libusb_handle_events_timeout_completed() function */
		/* Set = 0 so that the function acts right after finishing the previous events */
		struct timeval usb_event_timeout = (struct timeval ) { 0 };
		/* Array to keep former state of each process */
		int processInitialRunningState[numberOfProcesses];

		/* Obtain arguments */
		int correctValues = readArgumentsFromConfigFile();
		if (correctValues == 0) {

			/* Agent starts and send a start message to server */
			int checkRet = send_start_message(my_id);

			if (checkRet == 0) { // Check if there is problem connection
				/* Initialization of USB detection */
				/* check if Usb device is installed */
				int usbInstalledState = checkUsbInstallation();

				if (usbInstalledState == 0) {
					/* check if the usb is compatible */
					checkUsbCompatibility();
				}

				if (usbInstalledState == 0) {
					/* Event happens if a USB is inserted */
					is_USB_insertion();
					/* Event happens if a USB is removed */
					is_USB_removal();
				}

				/* Check initial state of CPU, processes and firewall*/
				checkInitialState(initial_load, processInitialRunningState);

				/* Main loop */
				do {
					if (usbInstalledState == 0) {
						/* USB detection*/
						/* Return 0 if success */
						libusb_handle_events_timeout_completed(NULL,
								&usb_event_timeout, NULL );
					}
					// Check if CPU state changes
					checkCpuUsage(1);

					// Check if critical processes are running
					int i;
					for (i = 0; i < numberOfProcesses; i++) {
						is_process_state_change(arrayOfProcesses[i],
								&processInitialRunningState[i]);
					}
					// Check if firewall is running
					is_firewall_enabled(1);

					// Check common process activation or deactivation
					checkAnyActivationOrTerminationProcess();

					// Check keep alive
					checkIsAlive();

				} while (1);

				if (usbInstalledState == 0) {
					/* For the current code, we will never each here */
					libusb_exit(NULL );
				}
				exit(0);
			}
		}


}

int printAgentMenu (){
	printf("\n");
	printf("**************************************************************************************\n");
	printf("***************************  Welcome to Fake Agent ***********************************\n");
	printf("**************************************************************************************\n");
	printf("** Please one of the following options:                                             **\n");
	printf("**                                                                                  **\n");
	printf("** 1-Run an Agent with Malformed event data                                         **\n");
	printf("** 2-Run an Agent with correct event data but contains invalid or out-of-range data **\n");
	printf("** 3-Run an Agent with invalid cert                                                 **\n");
	printf("** 4-Run an Agent with invalid key                                                  **\n");
	printf("** 5-Run an Agent with invalid detector cert                                        **\n");
	printf("** 6-Run an Agent with predefined event sequences (behaviour analysis)              **\n");
	printf("** 7-Run an Agent with normal behavior                                              **\n");
	printf("** 8-Run an Agent with Malformed event data (only one event)                        **\n");
	printf("** 10-Quit                                                                          **\n");
	printf("**************************************************************************************\n");
	printf("option-->");
	fflush(stdout);
	int option;
	scanf("%d", &option);
	return option;
}

void menu(){
	int op;
	do{
		op=printAgentMenu();
		if (op==1){
			readArgumentsFromConfigFile();
			RunAgentWithMalformedEventData();
		}
		if (op==2){
			readArgumentsFromConfigFile();
			RunAgentContainsInvalidOrOutOfRangeData();
		}
		if (op==3){
			readArgumentsFromConfigFile();
			RunAgentWithInvalidCert();
		}
		if (op==4){
			readArgumentsFromConfigFile();
			RunAgentWithInvalidKey();
		}
		if (op==5){
			readArgumentsFromConfigFile();
			RunAgentWithInvalidDetectorCert();
		}
		if (op==6){
			readArgumentsFromConfigFile();
			RunAgentWithPredefinedEventSequences();
		}
		if (op==7){
			runAgentWithNormalBehaviour();
		}
		if (op==8){
			readArgumentsFromConfigFile();
			RunAgentWithMalformedEventDataSendOneEvent();
		}
		if (((op>8) || (op<1))&& (op!=10)){
			printf("Wrong option, please insert one of the Menu options above \n");
		}
	}while(op!=10);

}

int main(int argc, char *argv[]) {
	menu();
	return 0;
}

