/*
 ============================================================================
 Name        : InsertCriticalProcessInTheList.c
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
#include <signal.h>

/* Constants for readArgumentsFromConfigFile */
#define MAX_BUFFER_READ_ARGUMENTS 50
#define MAX_BUFFER_READ_ARGUMENTS_OF_PROCESSES 2000
#define MAX_STRING 1000
#define MIN_ID 1
#define MAX_ID 100
#define MIN_THRESHOLD 0
#define MAX_THRESHOLD 100
#define MAXLENGHTLINE 200

/* Constants for checkIsAlive */
#define MAX_TEMP_STRING_CHECKIFALIVE 150

/* Global variables */
int my_id = 1;
char * detector_ip;
char * flagUsbDevices;
char * agentHASH;
long double threshold;
int memoryThreshold;
long double lengthCircularBuffer;
long double auditFunctionTime;
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
/* MEM state */
/* currentlyMEMState=1 if the MEM is on EXCESS state and
 * currentlyMEMState=0 if the MEM is on NORMAL state
 */
int currentlyMEMState=-1;
int lastMEMState=-1;
int flagCpuGratefulFallbackMode = 0; // flagCpuGratefullFallbackMode=0 is off and flagCpuGratefullFallbackMode=1 is on
int flagMemGratefulFallbackMode = 0;

/*Structures for dynamic memory*/
/*process node*/
struct process_node {
	int processPID;
	char processName[MAXLENGHTLINE];
	struct process_node *next;
}*criticalProcesses ,*tempInside;

/*List Operations */
/* Display the content list of nodes */
void display() {
	struct process_node *r;
	r = criticalProcesses;
	if (r == NULL ) {
		printf("the main list is empty\n");
		return;
	} else {
		printf("Critical processes list:\n");
		while (r != NULL ) {

			printf("%d %s\n", r->processPID, r->processName);
			r = r->next;
		}
	}
	printf("\n");
}

/* Count element of the list */
int countCriticalProcessesInMainList() {
	struct process_node *n;
	int c = 0;
	n = criticalProcesses;
	while (n != NULL ) {
		n = n->next;
		c++;
	}
	return c;
}

/* insert Critical process at the end of the list */
void appendCriticalProcess(int num, char pName[MAXLENGHTLINE],
		struct process_node **temp) {
	/* Allocate memory for the node */
	struct process_node *right;

	*temp = (struct process_node *) malloc(sizeof(struct process_node));
	/* Assign the specific information in fields */
	(*temp)->processPID = num;
	strcpy((*temp)->processName, pName);

	right = (struct process_node *) criticalProcesses;

	while (right->next != NULL )
		right = right->next;
	right->next = *temp;
	right = *temp;
	right->next = NULL;

}

/* add critical process */
void addCriticalProcess(int num, char pName[MAXLENGHTLINE],
		struct process_node **temp) {
	/* Allocate memory for the node */
	*temp = (struct process_node *) malloc(sizeof(struct process_node));
	/* Assign the specific information in fields */
	(*temp)->processPID = num;
	strcpy((*temp)->processName, pName);

	/* Add to critical process list */
		if (criticalProcesses == NULL ) {
			criticalProcesses = *temp;
			criticalProcesses->next = NULL;
		} else {
			(*temp)->next = criticalProcesses;
			criticalProcesses = *temp;
		}
}

/* add critical process in a specific location */
void addafterCriticalProcess(int num, int loc, char pName[MAXLENGHTLINE],
		struct process_node **temp) {
	int i;
	struct process_node *left, *right;

	/* Addafter in critical processes list */
	right = criticalProcesses;

	for (i = 1; i < loc; i++) {
		left = right;
		right = right->next;
	}
	/* Allocate memory for the node */
	*temp = (struct process_node *) malloc(sizeof(struct process_node));
	/* Assign the specific information in fields */
	(*temp)->processPID = num;
	strcpy((*temp)->processName, pName);

	left->next = *temp;
	left = *temp;
	left->next = right;
	return;
}

/* insert a node in the critical processes list */
void insertMainListCriticalProcess(int num, char pName[MAXLENGHTLINE]) {
	int c = 0;
	struct process_node *temp;
	temp = criticalProcesses;
	if (temp == NULL ) {
		addCriticalProcess(num, pName, &tempInside);
	} else {
		while (temp != NULL ) {
			if (temp->processPID < num)
				c++;
			temp = temp->next;
		}
		if (c == 0)
			addCriticalProcess(num, pName, &tempInside); // insert at the beginning
		else if (c < countCriticalProcessesInMainList())
			addafterCriticalProcess(num, ++c, pName, &tempInside); // insert after a number
		else {
			appendCriticalProcess(num, pName, &tempInside); // insert at the end
		}
	}
}

/* Return process id that matches with process name */
pid_t get_process_id_by_name(char *process_name) {

	DIR *dir;
	struct dirent *ent;
	char buf[1024];
	char pname[MAXLENGHTLINE] = { 0, };
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
			int nchars = fread(pname, 1, MAXLENGHTLINE, fp);

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

/* Get arguments from the config file */
int readArgumentsFromConfigFile() {
	FILE * cF;
	char bufr[MAX_BUFFER_READ_ARGUMENTS];
	char bufrProcesses[MAX_BUFFER_READ_ARGUMENTS_OF_PROCESSES];
	char processes[MAX_STRING];

	printf("-------------------------------------\n");
	printf("-------SNOK Agent Configuration------\n");
	printf("-------------------------------------\n");
	/* open the file */
	cF = fopen("config.txt", "r");
	if (cF != NULL ) {
		/* get my_id */
		fgets(bufr, MAX_STRING, cF);
		sscanf(bufr + 8, "%d", &my_id);
		printf("Agent id is %d\n", my_id);

		/* get ip_detector */
		detector_ip = (char *) malloc(15);
		fgets(bufr, MAX_STRING, cF);
		sscanf(bufr + 11, "%s", detector_ip);
		printf("Ip detector is %s\n", detector_ip);

		/* get cpuThresold */
		fgets(bufr, MAX_STRING, cF);
		double cpuT; // receive double
		sscanf(bufr + 13, "%lf", &cpuT);
		threshold = cpuT; // double to long double
		printf("Cpu thresold is %2.Lf\n", threshold);

		/* get memoryThresold */
		fgets(bufr, MAX_STRING, cF);
		int memoryT; // receive double
		sscanf(bufr + 16, "%d", &memoryT);
		memoryThreshold = memoryT;
		printf("Memory threshold is %d\n", memoryThreshold);

		/* get flag usb devices */
		flagUsbDevices = (char *) malloc(3);
		fgets(bufr, MAX_STRING, cF);
		sscanf(bufr + 11, "%s", flagUsbDevices);
		printf("Detection usb devices: %s\n", flagUsbDevices);

		/* get length circular buffer */
		fgets(bufr, MAX_STRING, cF);
		double circularL; // receive double
		sscanf(bufr + 21, "%lf", &circularL);
		lengthCircularBuffer = circularL;
		printf("Length circular buffer is %2.Lf\n", lengthCircularBuffer);

		/* get time audit function */
		fgets(bufr, MAX_STRING, cF);
		double auditFunctionT; // receive double
		sscanf(bufr + 18, "%lf", &auditFunctionT);
		auditFunctionTime = auditFunctionT;
		printf("Audit function time is %2.Lf\n", auditFunctionTime);

		/* get Agent HASH */
		agentHASH = (char *) malloc(40);
		fgets(bufr, MAX_STRING, cF);
		sscanf(bufr + 10, "%s", agentHASH);
		printf("The Agent HASH is %s\n", agentHASH);
		fflush(stdout);

		/* get processes */
		fgets(bufrProcesses, MAX_BUFFER_READ_ARGUMENTS_OF_PROCESSES, cF);
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
		printf("List of processes: \n");
		for (i = 0; i < numberOfProcesses; i++) {
			printf("%s pid: %d \n", arrayOfProcesses[i], get_process_id_by_name(arrayOfProcesses[i]));
			insertMainListCriticalProcess(get_process_id_by_name(arrayOfProcesses[i]),arrayOfProcesses[i]);

		}
		printf("\n");

	} else {
		printf("Error open config file\n ");
	}
	/* if my_id or threshold is incorrect the program will stop */
	if ((my_id < MIN_ID || my_id > MAX_ID)
			|| (threshold < MIN_THRESHOLD || threshold > MAX_THRESHOLD)) {
		printf("Any argument is incorrect, please insert the correct values\n");
		return 1;
	}
	return 0;

}

int main(void) {
	printf("we are going to insert the critical processes in the list\n");
	readArgumentsFromConfigFile();
	display();

	return EXIT_SUCCESS;
}
