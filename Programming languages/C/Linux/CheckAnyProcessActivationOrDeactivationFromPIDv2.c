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
}*head;

/*Dynamic list of nodes*/
//typedef struct process_node dynamicListOfProcess;

struct node *n;


void append(int num)
{
    struct process_node *temp,*right;
    temp= (struct process_node *)malloc(sizeof(struct process_node));
    temp->processPID=num;
    right=(struct process_node *)head;
    while(right->next != NULL)
    right=right->next;
    right->next =temp;
    right=temp;
    right->next=NULL;
}


void add( int num )
{
    struct process_node *temp;
    temp=(struct process_node *)malloc(sizeof(struct process_node));
    temp->processPID=num;
    if (head== NULL){
    	head=temp;
    	head->next=NULL;
    }else{
    	temp->next=head;
    	head=temp;
    }
}
void addafter(int num, int loc)
{
    int i;
    struct process_node *temp,*left,*right;
    right=head;
    for(i=1;i<loc;i++)
    {
    left=right;
    right=right->next;
    }
    temp=(struct process_node *)malloc(sizeof(struct process_node));
    temp->processPID=num;
    left->next=temp;
    left=temp;
    left->next=right;
    return;
}



void insert(int num)
{
    int c=0;
    struct process_node *temp;
    temp=head;
    if(temp==NULL)
    {
    add(num);
    }
    else
    {
    while(temp!=NULL)
    {
        if(temp->processPID<num)
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

int delete(int num)
{
    struct process_node *temp, *prev;
    temp=head;
    while(temp!=NULL)
    {
    if(temp->processPID==num)
    {
        if(temp==head)
        {
        head=temp->next;
        free(temp);
        return 1;
        }
        else
        {
        prev->next=temp->next;
        free(temp);
        return 1;
        }
    }
    else
    {
        prev=temp;
        temp= temp->next;
    }
    }
    return 0;
}

void  display(struct process_node *r)
{
    r=head;
    if(r==NULL)
    {
    return;
    }
    while(r!=NULL)
    {
    printf("%d ",r->processPID);
    r=r->next;
    }
    printf("\n");
}

int count()
{
    struct process_node *n;
    int c=0;
    n=head;
    while(n!=NULL)
    {
    n=n->next;
    c++;
    }
    return c;
}

/* Get all process running without checking PID */
void makeListEveryProcessRunningWithoutPID() {

	//struct process_node *curr, *head;


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
		//curr = (dynamicListOfProcess *) malloc(sizeof(dynamicListOfProcess));
		//curr->processPID = atoi(line);
		//curr->next = head;
		//head = curr;
		insert(atoi(line));
	}
	//curr = head;


	//int p = 0;
	//FILE *fp2;
	//char sysCallStr[100];

	//Display information inside of list
	if(head==NULL){
		printf("List is Empty\n");
	}else{
		display(n);
	}

	//while (curr) {
		/* print the process id */
		//printf("Process pid: %d, pos: %d\n", curr->processPID, p);


		/* print the process name */
		//sprintf(sysCallStr, "ps -p %d -o command | tail -n +2 ", curr->processPID);
		//fp2 = popen(sysCallStr, "r");
		//while (fgets(line, sizeof line, fp2) != NULL ) {
			//printf("The process name is: %s", line);
		//}

		//p++;
		//curr = curr->next;
	//}
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
	head = NULL;
	makeListEveryProcessRunningWithoutPID();
	//makeListEveryProcessRunningCheckingPID(); // make a snapshot of the processes running at the beginning
	//for (;;) {
	//checkAnyActivationOrTerminationProcess();
	//sleep(3);
	//}

	return EXIT_SUCCESS;

}

