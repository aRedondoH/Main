/* Processes libraries */
#include <tchar.h>
#include <clocale>
#include <cstdlib>
#include <comdef.h>
#include <wchar.h>
#include <TlHelp32.h>

/* Constants */
#define MAXLENGHTLINE 260

/* Structures for dynamic memory */
/* Process node */
struct process_node {
	int processPID;
	char processName[MAXLENGHTLINE];
	struct process_node *next;
}*head, *headTemp, *headTemp_save, *tempInside;

struct process_node *n;
struct process_node *n2;

/* ----------------------------------------------------- */
/* --------------- PROCESSES FUNCTIONS ----------------- */
/* ----------------------------------------------------- */

/* Display the content list of nodes */
void display(struct process_node *r) {
	r = head;
	if (r == NULL) {
		printf("the main list is empty\n");
		return;
	}
	else {
		printf("Main list\n");
		while (r != NULL) {

			printf("%d %s\n", r->processPID, r->processName);
			r = r->next;
		}
	}
	printf("\n");
}

/* Display the content of temp list */
void displayTemp(struct process_node *r) {
	r = headTemp;
	if (r == NULL) {
		printf("the temp list is empty\n");
		return;
	}
	else {
		printf("Temp list\n");
		while (r != NULL) {
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
	while (n != NULL) {
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
	while (n != NULL) {
		n = n->next;
		c++;
	}
	return c;
}

/* Free the temp list */
void freeTempList() {
	/* Free pointers from main list */
	struct process_node *tmp1;
	tmp1 = headTemp;
	while (headTemp != NULL) {
		tmp1 = headTemp;
		headTemp = headTemp->next;
		free(tmp1);
	}
	headTemp = NULL;
}

/* insert at the end
if flagInsert==1 it will insert into main list,
if flagInsert==2 it will insert into temp list*/
void append(int num, char pName[MAXLENGHTLINE], struct process_node **temp,
	int flagInsert) {
	/* Allocate memory for the node */
	struct process_node *right;

	/* Initialize pointer */
	right = NULL;

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
	while (right->next != NULL)
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
		if (head == NULL) {
			head = *temp;
			head->next = NULL;
		}
		else {
			(*temp)->next = head;
			head = *temp;
		}
	}
	/* Add to the temp list */
	if (flagInsert == 2) {
		if (headTemp == NULL) {
			headTemp = *temp;
			headTemp->next = NULL;
		}
		else {
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
	/* Initialize pointer */
	left = NULL;
	right = NULL;

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
	if (temp == NULL) {
		add(num, pName, &tempInside, 1);
	}
	else {
		while (temp != NULL) {
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
	if (temp == NULL) {
		add(num, pName, &tempInside, 2);
	}
	else {
		while (temp != NULL) {
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

/* Delete a node of the main list */
int deleteFromTempList(int num) {
	struct process_node *temp, *prev;
	temp = head;
	/* Initialite pointer */
	prev = NULL;
	while (temp != NULL) {
		if (temp->processPID == num) {
			if (temp == head) {
				head = temp->next;
				free(temp);
				return 1;
			}
			else {
				prev->next = temp->next;
				free(temp);
				return 1;
			}
		}
		else {
			prev = temp;
			temp = temp->next;
		}
	}
	return 0;
}




/* Get all process running checking PID main list */
void makeListEveryProcessRunningTakingPID(){
	char processNameTemp[MAXLENGHTLINE];
	int tempPID;


	PROCESSENTRY32 process;
	WCHAR wc[MAXLENGHTLINE];
	DWORD pid = 0;

	process.dwSize = sizeof(PROCESSENTRY32);
	// Get snapshot of the current windows status 
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	// Get processes running and their pid
	if (Process32First(snapshot, &process)){
		while (Process32Next(snapshot, &process)){
			/* Get pid*/
			pid = process.th32ProcessID;
			/* pid DWORD to int*/
			tempPID = static_cast<int>(pid);

			/* Convert tchar to wchar FIXME */
			ua_wcscpy_s(wc, MAXLENGHTLINE, process.szExeFile);
			/* Convert wchar msg to char* */
			_bstr_t b(wc);
			/* Convert char* to char array */
			strcpy_s(processNameTemp, MAXLENGHTLINE, b);

			//printf("Process: %s pid: %d\n", processNameTemp, tempPID);

			/* insert process into the list */
			insertMainList(tempPID, processNameTemp);

		}
	}
	CloseHandle(snapshot);
}

/* Get all process running checking PID temp list*/
void makeTempListEveryProcessRunningTakingPID(){

	char processNameTemp[MAXLENGHTLINE];
	int tempPID;


	PROCESSENTRY32 process;
	WCHAR wc[MAXLENGHTLINE];
	DWORD pid = 0;

	process.dwSize = sizeof(PROCESSENTRY32);
	// Get snapshot of the current windows status 
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	// Get processes running and their pid
	if (Process32First(snapshot, &process)){
		while (Process32Next(snapshot, &process)){
			/* Get pid*/
			pid = process.th32ProcessID;
			/* pid DWORD to int*/
			tempPID = static_cast<int>(pid);

			/* Convert tchar to wchar FIXME */
			ua_wcscpy_s(wc, MAXLENGHTLINE, process.szExeFile);
			/* Convert wchar msg to char* */
			_bstr_t b(wc);
			/* Convert char* to char array */
			strcpy_s(processNameTemp, MAXLENGHTLINE, b);

			//printf("Process: %s pid: %d\n", processNameTemp, tempPID);

			/* insert process into the list */
			insertIntoTempList(tempPID, processNameTemp);

		}
	}
	CloseHandle(snapshot);

}

/* Check if the process is already inside the list */
int checkIfTheProcessExistsInList(int PIDprocess) {
	int found = 0;
	struct process_node *runner;

	/* Pointer to the first node */
	runner = head;
	if (runner == NULL) {
		printf("something is wrong in checkIfTheProcessExistsInList\n");
		return -1;
	}
	while (runner != NULL) {
		if (runner->processPID == PIDprocess) {
			found = 0;
		}
		runner = runner->next;
	}
	if (found == 1) {
		return 1;
	}
	else {
		if (found == 0) {
			return 0;
		}
	}
	return 0;
}

/* Check if there is a new process */
void checkNewProcesses() {
	int found = -1;
	struct process_node *r;
	struct process_node *m;

	r = headTemp;
	m = head;
	if (r == NULL || m == NULL) {
		printf("something is wrong\n");
		return;
	}
	while (r != NULL) {
		while (m != NULL) {
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
	if (r == NULL || m == NULL) {
		printf("One of the two list is empty \n");
		return;
	}
	/* Check if in the main list there is a termination process */
	while (r != NULL) {
		while (m != NULL) {

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
			deleteFromTempList(r->processPID);
			deleted = 1;
			/* Recheck if there is more termination process */
			r = head;

		}
		if (deleted != 1){
			r = r->next;
		}
		deleted = 0;
		found = -1;
	}
}

/* Check if there is any process activate or deactivate */
void checkAnyActivationOrTerminationProcess() {
	/* Make temp list of processes */
	makeTempListEveryProcessRunningTakingPID();
	/* Check if there are new processes */
	checkNewProcesses();
	/* Check if there are termination processes */
	checkTerminationProcesses();
	/* Freeing temp list memory */
	freeTempList();
}

int main(int argc, char *argv[])
{
	printf("We are going to check the current processes running\n");
	/*Initializing pinters */
	head = NULL;
	headTemp = NULL;

	/* Make the main processes list */
	makeListEveryProcessRunningTakingPID();
	for (;;){
		checkAnyActivationOrTerminationProcess();
		Sleep(2000);
	}
}