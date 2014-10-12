/*
 * CheckMain.c
 *
 *  Created on: Oct 7, 2014
 *      Author: secnok
 */

/* Common libraries */
#include <stdlib.h>
#include <stdio.h>

/* Constants */
#define MAXLENGHTLINE 200

/*Structures for dynamic memory*/
/*process node*/
struct process_node {
	int processPID;
	struct process_node *next;
};

/*Dynamic list of nodes*/
typedef struct process_node dynamicListOfProcess;


void add( int num )
{
    struct process_node *temp;
    temp=(struct node *)malloc(sizeof(struct process_node));
    temp->processPID=num;
    if (head== NULL)
    {
    head=temp;
    head->next=NULL;
    }
    else
    {
    temp->next=head;
    head=temp;
    }
}
void addafter(int num, int loc)
{
    int i;
    struct node *temp,*left,*right;
    right=head;
    for(i=1;i<loc;i++)
    {
    left=right;
    right=right->next;
    }
    temp=(struct node *)malloc(sizeof(struct node));
    temp->data=num;
    left->next=temp;
    left=temp;
    left->next=right;
    return;
}



void insert(int num)
{
    int c=0;
    struct node *temp;
    temp=;
    if(temp==NULL)
    {
    add(num);
    }
    else
    {
    while(temp!=NULL)
    {
        if(temp->data<num)
        c++;
        temp=temp->next;
    }
    if(c==0)
        add(num);
    else if(c<count())
        addafter(num,++c);
    else
        append(num);
    }
}

/* Get all process running without checking PID */
void makeListEveryProcessRunningWithoutPID() {

	dynamicListOfProcess *curr, *head;
	head = NULL;

	char line[MAXLENGHTLINE];

	FILE *fp;
	fp = popen("ps aux | awk '{printf $2 \" \\n \"}' | tail -n +2", "r");

	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}


	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		curr = (dynamicListOfProcess *) malloc(sizeof(dynamicListOfProcess));
		curr->processPID = atoi(line);
		curr->next = head;
		head = curr;
	}
	curr = head;


	int p = 0;
	FILE *fp2;
	char sysCallStr[100];

	while (curr) {
		/* print the process id */
		printf("Process pid: %d, pos: %d\n", curr->processPID, p);


		/* print the process name */
		//sprintf(sysCallStr, "ps -p %d -o command | tail -n +2 ", curr->processPID);
		//fp2 = popen(sysCallStr, "r");
		//while (fgets(line, sizeof line, fp2) != NULL ) {
			//printf("The process name is: %s", line);
		//}

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
	printf("we going to check any process activate or deactivate  from PID \n"); /* prints we going to check any process activation or termination */
	fflush(stdout);
	makeListEveryProcessRunningWithoutPID();
	//makeListEveryProcessRunningCheckingPID(); // make a snapshot of the processes running at the beginning
	//for (;;) {
	//checkAnyActivationOrTerminationProcess();
	//sleep(3);
	//}

	return EXIT_SUCCESS;

}

