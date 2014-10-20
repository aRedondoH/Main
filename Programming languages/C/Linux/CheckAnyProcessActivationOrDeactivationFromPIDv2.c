/*
 * CheckMain.c
 *
 *  Created on: Oct 7, 2014
 *      Author: secnok
 */

/* Common libraries */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

/* Constants */
#define MAXLENGHTLINE 200

/*Structures for dynamic memory*/
/*process node*/
struct process_node {
	int processPID;
	char processName[MAXLENGHTLINE];
	struct process_node *next;
}*head, *headTemp, *headTemp_save, *tempInside;

struct process_node *n;
struct process_node *n2;

/* insert at the end
 if flagInsert==1 it will insert into main list,
 if flagInsert==2 it will insert into temp list*/
void append(int num, char pName[MAXLENGHTLINE], struct process_node **temp,
		int flagInsert) {
	/* Allocate memory for the node */
	struct process_node *right;

	*temp = (struct process_node *) malloc(sizeof(struct process_node));
	/* Assign the specific information in fields */
	(*temp)->processPID = num;
	strcpy((*temp)->processName, pName);

	if (flagInsert == 1) {
		right = (struct process_node *) head;
	}
	if (flagInsert == 2) {
		right = (struct process_node *) headTemp;
	}
	while (right->next != NULL )
		right = right->next;
	right->next = *temp;
	right = *temp;
	right->next = NULL;

}

/* add number inside of the node
 if flagInsert==1 it will insert into main list,
 if flagInsert==2 it will insert into temp list */
void add(int num, char pName[MAXLENGHTLINE], struct process_node **temp,
		int flagInsert) {
	/* Allocate memory for the node */
	*temp = (struct process_node *) malloc(sizeof(struct process_node));
	/* Assign the specific information in fields */
	(*temp)->processPID = num;
	strcpy((*temp)->processName, pName);
	/* Add to main list */
	if (flagInsert == 1) {
		if (head == NULL ) {
			head = *temp;
			head->next = NULL;
		} else {
			(*temp)->next = head;
			head = *temp;
		}
	}
	/* Add to the temp list */
	if (flagInsert == 2) {
		if (headTemp == NULL ) {
			headTemp = *temp;
			headTemp->next = NULL;
		} else {
			(*temp)->next = headTemp;
			headTemp = *temp;
		}
	}
}

/* add number in a specific locatin */
void addafter(int num, int loc, char pName[MAXLENGHTLINE],
		struct process_node **temp, int insertFlag) {
	int i;
	struct process_node *left, *right;

	/* Addafter in main list */
	if (insertFlag == 1) {
		right = head;
	}
	/* Addafter in temp list */
	if (insertFlag == 2) {
		right = headTemp;
	}
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

/* insert a node in the list */
void insertMainList(int num, char pName[MAXLENGHTLINE]) {
	int c = 0;
	struct process_node *temp;
	temp = head;
	if (temp == NULL ) {
		add(num, pName, &tempInside, 1);
	} else {
		while (temp != NULL ) {
			if (temp->processPID < num)
				c++;
			temp = temp->next;
		}
		if (c == 0)
			add(num, pName, &tempInside, 1); // insert at the beginning
		else if (c < count())
			addafter(num, ++c, pName, &tempInside, 1); // insert after a number
		else {
			append(num, pName, &tempInside, 1); // insert at the end
		}
	}
}

/* insert a node in the temp list */
void insertIntoTempList(int num, char pName[MAXLENGHTLINE]) {
	int c = 0;
	struct process_node *temp, *tempInside;
	temp = headTemp;
	/*Save to free*/
	headTemp_save = temp;
	if (temp == NULL ) {
		add(num, pName, &tempInside, 2);
	} else {
		while (temp != NULL ) {
			if (temp->processPID < num)
				c++;
			temp = temp->next;
		}
		if (c == 0)
			add(num, pName, &tempInside, 2);
		else if (c < countTemp())
			addafter(num, ++c, pName, &tempInside, 2);
		else
			append(num, pName, &tempInside, 2);
	}
}

/*  Free the main list */
void freeMainList() {
	/* Free pointers from main list */
	struct process_node *tmp1;
	tmp1 = head;
	while (head != NULL ) {
		tmp1 = head;
		head = head->next;
		free(tmp1);
	}
	head = NULL;
}
/* Free the temp list */
void freeTempList() {
	/* Free pointers from main list */
	struct process_node *tmp1;
	tmp1 = headTemp;
	while (headTemp != NULL ) {
		tmp1 = headTemp;
		headTemp = headTemp->next;
		free(tmp1);
	}
	headTemp = NULL;
}
/* Free main and temp list */
void freeAllMemory() {
	/* Free Main list */
	freeMainList();
	/* Free Temp list */
	freeTempList();
}

/* Delete a node of the main list */
int delete(int num) {
	struct process_node *temp, *prev;
	temp = head;
	while (temp != NULL ) {
		if (temp->processPID == num) {
			if (temp == head) {
				head = temp->next;
				free(temp);
				return 1;
			} else {
				prev->next = temp->next;
				free(temp);
				return 1;
			}
		} else {
			prev = temp;
			temp = temp->next;
		}
	}
	return 0;
}

/* Display the content list of nodes */
void display(struct process_node *r) {
	r = head;
	if (r == NULL ) {
		printf("the main list is empty\n");
		return;
	} else {
		printf("Main list\n");
		while (r != NULL ) {

			printf("%d %s\n", r->processPID, r->processName);
			r = r->next;
		}
	}
	printf("\n");
}

/* Display the content of temp list */
void displayTemp(struct process_node *r) {
	r = headTemp;
	if (r == NULL ) {
		printf("the temp list is empty\n");
		return;
	} else {
		printf("Temp list\n");
		while (r != NULL ) {
			printf("%d %s\n", r->processPID, r->processName);
			r = r->next;
		}
	}
	printf("\n");
}

/* Count element of the list */
int count() {
	struct process_node *n;
	int c = 0;
	n = head;
	while (n != NULL ) {
		n = n->next;
		c++;
	}
	return c;
}

/* Count element of the list temp list*/
int countTemp() {
	struct process_node *n;
	int c = 0;
	n = headTemp;
	while (n != NULL ) {
		n = n->next;
		c++;
	}
	return c;
}

/* Get all process running without checking PID */
void makeListEveryProcessRunningTakingPID() {

	char line[MAXLENGHTLINE];
	FILE *fp;
	//fp = popen("ps aux | awk '{printf $2 \" \\n \"}'  | grep -v 'ps' | grep -v awk | grep -v grep | tail -n +2 | grep -v tail", "r");
	//fp = popen("ps aux | awk '{printf $11 \" \" $2 \"\\n\"}' | tail -n +2 ",
	//		"r");
	fp = popen("ps aux | awk '{printf $11 \" \" $2 \"\\n\"}' | tail -n 5", "r");
	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	char *token1;
	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		int tempPid;
		char tempPName[MAXLENGHTLINE];
		/* Get process name */
		token1 = strtok(line, " ");

		strcpy(tempPName, token1);

		/* Get PID */
		if (token1 != NULL ) {
			// Increasing pointer to the next token
			token1 = strtok(NULL, " ");
			// Assign PID to the temp variable
			tempPid = atoi(token1);
		}
		/* Insert into the list */
		insertMainList(tempPid, tempPName);
	}
	//Display information inside of list
	if (head == NULL ) {
		printf("List is Empty\n");
	} else {
		display(n);

	}
}

/* Get all process running without checking PID */
void makeListTempEveryProcessRunningTakingPID() {

	char line[MAXLENGHTLINE];
	FILE *fp;
	//fp = popen("ps aux | awk '{printf $2 \" \\n \"}'  | grep -v 'ps' | grep -v awk | grep -v grep | tail -n +2 | grep -v tail", "r");
	//fp = popen("ps aux | awk '{printf $11 \" \" $2 \"\\n\"}' | tail -n +2 ",
	//		"r");
	fp = popen("ps aux | awk '{printf $11 \" \" $2 \"\\n\"}' | tail -n 5", "r");
	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	char *token1;
	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		int tempPid;
		char tempPName[MAXLENGHTLINE];
		/* Get process name */
		token1 = strtok(line, " ");

		strcpy(tempPName, token1);

		/* Get PID */
		if (token1 != NULL ) {
			// Increasing pointer to the next token
			token1 = strtok(NULL, " ");
			// Assign PID to the temp variable
			tempPid = atoi(token1);
		}
		/* Insert into the list */
		insertIntoTempList(tempPid, tempPName);
	}

	//Display information inside of list
	if (headTemp == NULL ) {
		printf("List is Empty\n");
	} else {
		//displayTemp(n2);
	}
}

/* Check if the process is already inside the list */
int checkIfTheProcessExistsInList(int PIDprocess) {
	int found = 0;
	struct process_node *runner;

	/* Pointer to the first node */
	runner = head;
	if (runner == NULL ) {
		printf("something is wrong in checkIfTheProcessExistsInList\n");
		return -1;
	}
	while (runner != NULL ) {
		if (runner->processPID == PIDprocess) {
			found = 0;
		}
		runner = runner->next;
	}
	if (found == 1) {
		return 1;
	} else {
		if (found == 0) {
			return 0;
		}
	}
	return 0;
}

/* Print the process name from PID */
void PrintProcessName(int PIDprocess) {

	FILE *fp;
	char sysCallStr[MAXLENGHTLINE];
	char line[MAXLENGHTLINE];

	sprintf(sysCallStr, "ps -p %d -o command | tail -n +2", PIDprocess);
	fp = popen(sysCallStr, "r");
	while (fgets(line, sizeof line, fp) != NULL ) {
		printf("Process name: %s", line);
	}
	pclose(fp);
}

/* Check if there is a new process */
void checkNewProcesses() {
	int found = -1;
	struct process_node *r;
	struct process_node *m;

	r = headTemp;
	m = head;
	if (r == NULL || m == NULL ) {
		printf("something is wrong\n");
		return;
	}
	while (r != NULL ) {
		while (m != NULL ) {
			if (r->processPID == m->processPID) {
				found = 0;
			}
			m = m->next;
		}
		m = head;
		/* if found==-1 outsite loop means there is new process */
		if (found == -1) {
			if (checkIfTheProcessExistsInList(r->processPID) == 0) {
				/* Print process name */
				printf("New process activated pid: %d name: %s\n",
						r->processPID, r->processName);
				/* Insert new process in the Main list */
				insertMainList(r->processPID, r->processName);
			}
		}
		r = r->next;
		found = -1;
	}
	printf("\n");
}

/* Check if there is a termination processes */
void checkTerminationProcesses() {
	int found = -1;
	int deleted = 0;
	struct process_node *r;
	struct process_node *m;

	/* Point to the main list */
	r = head;
	/* Point to the temp list */
	m = headTemp; //temp list
	if (r == NULL || m == NULL ) {
		printf("One of the two list is empty \n");
		return;
	}
	/* Check if in the main list there is a termination process */
	while (r != NULL ) {
		while (m != NULL ) {

				if (((r->processPID) == (m->processPID)) && (found != 0)) {
					//printf("Comparing %d with %d\n", r->processPID, m->processPID);
					found = 0;
				}

			m = m->next;
		}
		m = headTemp;
		/* if found==-1 outsite loop means there is termination process */
		if (found == -1) {
			printf("Termination process pid: %d name: %s\n", r->processPID,
					r->processName);

			/* Delete process name from the main list */
			delete(r->processPID);
			deleted=1;
			/* Recheck if there is more termination process */
			r=head;

		}
		if (deleted!=1){
			r = r->next;
		}
		deleted=0;
		found = -1;
	}
}

/* Check if there is any process activate or deactivate */
void checkAnyActivationOrTerminationProcess() {
	makeListTempEveryProcessRunningTakingPID();
	checkNewProcesses();
	checkTerminationProcesses();
	/* Print temp list */
	//printf("Priting temp list\n");
	//displayTemp(n2);
	freeTempList();

}

/* Catch Ctrl+c to free memory*/
void INThandler(int sig) {
	char c;
	signal(sig, SIG_IGN );
	printf("Do you want to quit? [y/n]");
	c = getchar();
	if (c == 'y' || c == 'Y') {
		freeAllMemory();
		exit(0);
	}
}

int main(void) {
	printf("we going to check any process activate or deactivate  from PID \n"); /* prints we going to check any process activation or termination */
	fflush(stdout);

	head = NULL;
	headTemp = NULL;

	/* Catch child signal to avoid zomby process */
	signal(SIGCHLD, SIG_IGN );

	/* Catch child signal to free memory */
	signal(SIGINT, INThandler);

	/*Make the main list of processes */
	makeListEveryProcessRunningTakingPID();

	for (;;) {
		checkAnyActivationOrTerminationProcess();
		sleep(2);
	}

	return EXIT_SUCCESS;

}

