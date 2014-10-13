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

/*Structures for dynamic memory*/
/*process node*/
struct process_node2 {
	int processPID;
	struct process_node2 *next;
}*headTemp;

struct node *n;

/* insert at the end */
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

/* insert at the end temp list*/
void appendtempList(int num)
{
    struct process_node2 *temp,*right;
    temp= (struct process_node2 *)malloc(sizeof(struct process_node2));
    temp->processPID=num;
    right=(struct process_node2 *)headTemp;
    while(right->next != NULL)
    right=right->next;
    right->next =temp;
    right=temp;
    right->next=NULL;
}

/* add number inside of the node*/
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

/* add number inside of the node temp list */
void addTempList( int num )
{
    struct process_node2 *temp;
    temp=(struct process_node2 *)malloc(sizeof(struct process_node2));
    temp->processPID=num;
    if (headTemp== NULL){
    	headTemp=temp;
    	headTemp->next=NULL;
    }else{
    	temp->next=headTemp;
    	headTemp=temp;
    }
}

/* add number in a specific locatin */
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

/* add number in a specific locatin temp list*/
void addafterTempList(int num, int loc)
{
    int i;
    struct process_node2 *temp,*left,*right;
    right=headTemp;
    for(i=1;i<loc;i++)
    {
    left=right;
    right=right->next;
    }
    temp=(struct process_node2 *)malloc(sizeof(struct process_node2));
    temp->processPID=num;
    left->next=temp;
    left=temp;
    left->next=right;
    return;
}


/* insert a node in the list */
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
/* insert a node in the temp list */
void insertIntoTempList(int num){
	 int c=0;
	    struct process_node2 *temp;
	    temp=headTemp;
	    if(temp==NULL)
	    {
	    addTempList(num);
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
	        addTempList(num);
	    else if(c<countTemp())
	        addafterTempList(num,++c);
	    else
	        appendtempList(num);
	    }
}

/* Delete a node of the list */
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

/* Display the content list of nodes */
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

/* Display the content of temp list */
void  displayTemp(struct process_node2 *r)
{
    r=headTemp;
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


/* Count element of the list */
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

/* Count element of the list temp list*/
int countTemp()
{
    struct process_node2 *n;
    int c=0;
    n=headTemp;
    while(n!=NULL)
    {
    n=n->next;
    c++;
    }
    return c;
}

/* Get all process running without checking PID */
void makeListEveryProcessRunningTakingPID() {

	char line[MAXLENGHTLINE];

	FILE *fp;
	fp = popen("ps aux | awk '{printf $2 \" \\n \"}'| grep -v 'ps aux' | grep -v awk | tail -n +2", "r");
	//fp = popen("ps aux | awk '{printf $2 \" \\n \"}'  | grep -v 'ps' | grep -v awk | grep -v grep | tail -n +2 | grep -v tail", "r");

	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		insert(atoi(line));
	}

	//Display information inside of list
	if(head==NULL){
		printf("List is Empty\n");
	}else{
		//display(n);

	}
}
/* Get all process running without checking PID */
void makeListTempEveryProcessRunningTakingPID() {

	char line[MAXLENGHTLINE];

	FILE *fp;
	fp = popen("ps aux | awk '{printf $2 \" \\n \"}'  | grep -v 'ps aux' | grep -v awk | tail -n +2 ", "r");
	//fp = popen("ps aux | awk '{printf $2 \" \\n \"}'  | grep -v 'ps' | grep -v awk | grep -v grep | tail -n +2 | grep -v tail", "r");

	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
		fflush(stdout);
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {

		insertIntoTempList(atoi(line));
	}

	//Display information inside of list
	if(headTemp==NULL){
		printf("List is Empty\n");
	}else{
		//displayTemp(n);
	}
}
/* Check if there is a new process */
void checkNewProcesses(){
	int found=-1;
	struct process_node *r,*m;
	FILE *fp;
	char sysCallStr[100];
	char line[200];
	r=headTemp;
	m=head;
	    if(r==NULL || m==NULL)
	    {
	    	printf("something is wrong\n");
	    return;
	    }
	    while(r!=NULL)
	    {
	    	while(m!=NULL){
	    		if (r->processPID==m->processPID){
	    			//printf("Comparing %d with %d\n", r->processPID, m->processPID);
	    			found=0;
	    		}
	    		//printf("%d ",r->processPID);
	    		m=m->next;
	    	}
	    	m=head;
	    	/* if found==-1 outsite loop means there is new process */
	    	if (found==-1){

	    		printf("New process activated pid: %d\n", r->processPID);
	    		sprintf(sysCallStr, "ps -p %d -o command | tail -n +2", r->processPID);
	    		fp = popen(sysCallStr, "r");
	    		while(fgets(line,sizeof line, fp)!=NULL){
	    			printf(" name: %s", line);
	    		}

	    		insert(r->processPID);

	    	}
	    	r=r->next;
	    	found=-1;
	    }
	    printf("\n");

}

void checkTerminationProcesses(){
	int found=-1;
	struct process_node *r,*m;
		FILE *fp;
		char sysCallStr[100];
		char line[200];
		r=head; //mainlist
		m=headTemp; //temp list

		 if(r==NULL || m==NULL)
			    {
			    	printf("something is wrong\n");
			    return;
			    }
			    while(r!=NULL)
			    {
			    	while(m!=NULL){
			    		if (r->processPID==m->processPID){
			    			//printf("Comparing %d with %d\n", r->processPID, m->processPID);
			    			found=0;
			    		}
			    		//printf("%d ",r->processPID);
			    		m=m->next;
			    	}
			    	m=head;
			    	/* if found==-1 outsite loop means there is new process */
			    	if (found==-1){

			    		printf("Termination process pid: %d\n", r->processPID);
			    		sprintf(sysCallStr, "ps -p %d -o command | tail -n +2", r->processPID);
			    		fp = popen(sysCallStr, "r");
			    		while(fgets(line,sizeof line, fp)!=NULL){
			    			printf(" name: %s", line);
			    		}

			    		delete(r->processPID);

			    	}
			    	r=r->next;
			    	found=-1;
			    }
			    printf("\n");

}

/* Free the memory of the temp list */
void freeList()
{
   struct process_node* tmp;

   while (headTemp != NULL)
    {
       tmp = headTemp;
       headTemp = headTemp->next;
       free(tmp);
    }

}

/* Check if there is any process activate or deactivate */
void checkAnyActivationOrTerminationProcess() {
 makeListTempEveryProcessRunningTakingPID();
 checkNewProcesses();
 checkTerminationProcesses();
 printf("Main List\n");
 display(n);
 printf("Temp list\n");
 		displayTemp(n);
 freeList();
 }

int main(void) {
	printf("we going to check any process activate or deactivate  from PID \n"); /* prints we going to check any process activation or termination */
	fflush(stdout);
	head = NULL;
	headTemp = NULL;
	makeListEveryProcessRunningTakingPID();

	for (;;) {
		checkAnyActivationOrTerminationProcess();
		printf("Main list\n");
		sleep(1);
	}

	return EXIT_SUCCESS;

}

