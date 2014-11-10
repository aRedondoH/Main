/*
 ============================================================================
 Name        : GetPS2AndSerialDevices.c
 Author      : Alberto.R.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/* Constants */
#define MAXLENGHTLINE 200

/* Record to save the devices */
struct node_device {
	char deviceName[MAXLENGHTLINE];
	char phys[MAXLENGHTLINE];
	char sysfs[MAXLENGHTLINE];
	struct node_device *next;
}*devices, *devices_temp;

/* List Operations */
/* Append */
void append(char deviceNameToInsert[MAXLENGHTLINE],
		char physToInsert[MAXLENGHTLINE], char sysfsToInsert[MAXLENGHTLINE],
		int flagInsert) {
	/* Allocate memory for the node */
	struct node_device *right, *temp;
	/* Allocate memory for the node */
	temp = (struct node_device *) malloc(sizeof(struct node_device));
	/* Assign the specific information in fields */
	/* Assign name of the device */
	strcpy(temp->deviceName, deviceNameToInsert);
	/* Assig phys path */
	strcpy(temp->phys, physToInsert);
	/* Assign sysfs path */
	strcpy(temp->sysfs, sysfsToInsert);

	/* Append to main devices list */
	if (flagInsert == 1) {
		right = (struct node_device *) devices;
	}
	/* Append to temp devices list */
	if (flagInsert == 2) {
		right = (struct node_device *) devices_temp;
	}
	while (right->next != NULL )
		right = right->next;
	right->next = temp;
	right = temp;
	right->next = NULL;
}

/* Add */
void add(char deviceNameToInsert[MAXLENGHTLINE],
		char physToInsert[MAXLENGHTLINE], char sysfsToInsert[MAXLENGHTLINE],
		int flagInsert) {
	/* Create a node to fill it with the temporal information */
	struct node_device *temp;
	/* Allocate memory for the node */
	temp = (struct node_device *) malloc(sizeof(struct node_device));
	/* Assign the specific information in fields */
	/* Assign name of the device */
	strcpy(temp->deviceName, deviceNameToInsert);
	/* Assign phys path */
	strcpy(temp->phys, physToInsert);
	/* Assign sysfs path */
	strcpy(temp->sysfs, sysfsToInsert);

	/* Add device to the main list */
	if (flagInsert == 1) {
		if (devices == NULL ) {
			devices = temp;
			devices->next = NULL;
		} else {
			temp->next = devices;
			devices = temp;
		}
	}

	/* Add device to the temp list */
	if (flagInsert == 2) {
		if (devices_temp == NULL ) {
			devices_temp = temp;
			devices_temp->next = NULL;
		} else {
			temp->next = devices_temp;
			devices_temp = temp;
		}
	}
}

/* Add in a specific location */
void addafter(int loc, char deviceNameToInsert[MAXLENGHTLINE],
		char physToInsert[MAXLENGHTLINE], char sysfsToInsert[MAXLENGHTLINE],
		int insertFlag) {
	int i;
	struct node_device *left, *right, *temp;
	left = NULL;

	/* Addafter device in main list */
	if (insertFlag == 1) {
		right = devices;
	}
	/* Addafter device in temp list */
	if (insertFlag == 2) {
		right = devices_temp;
	}
	for (i = 1; i < loc; i++) {
		left = right;
		right = right->next;
	}

	/* Allocate memory for the node */
	temp = (struct node_device *) malloc(sizeof(struct node_device));

	/* Assign the specific information in fields */
	/* Assign name of the device */
	strcpy(temp->deviceName, deviceNameToInsert);
	/* Assign phys path */
	strcpy(temp->phys, physToInsert);
	/* Assign sysfs path */
	strcpy(temp->sysfs, sysfsToInsert);

	/* add device to the list in a specific location */
	left->next = temp;
	left = temp;
	left->next = right;

}

/* Count element of the list */
int count(int flagToCount) {
	struct node_device *n;
	int c = 0;
	/* Count elements from main list */
	if (flagToCount == 1) {
		n = devices;
	}
	/* Count elements from temp list */
	if (flagToCount == 2) {
		n = devices_temp;
	}
	while (n != NULL ) {
		n = n->next;
		c++;
	}
	return c;
}

/* Insert device */
void insertDevice(char deviceNameTemp[MAXLENGHTLINE],
		char physTemp[MAXLENGHTLINE], char sysfsTemp[MAXLENGHTLINE]) {

	int c = 0;
	struct node_device *temp;

	/* Assign the devices list to temp */
	temp = devices;

	if (temp == NULL ) {
		add(deviceNameTemp, physTemp, sysfsTemp, 1);
	} else {
		c = count(1);
		if (c == 0)
			add(deviceNameTemp, physTemp, sysfsTemp, 1);
		else if (c < count(1))
			addafter(++c, deviceNameTemp, physTemp, sysfsTemp, 1);
		else {
			append(deviceNameTemp, physTemp, sysfsTemp, 1);
		}
	}
}

/* Insert device temp */
void insertDeviceTemp(char deviceNameTemp[MAXLENGHTLINE],
		char physTemp[MAXLENGHTLINE], char sysfsTemp[MAXLENGHTLINE]) {

	int c = 0;
	struct node_device *temp;

	/* Assign the devices list to temp */
	temp = devices_temp;

	if (temp == NULL ) {
		add(deviceNameTemp, physTemp, sysfsTemp, 2);
	} else {
		c = count(2);
		if (c == 0)
			add(deviceNameTemp, physTemp, sysfsTemp, 2);
		else if (c < count(2))
			addafter(++c, deviceNameTemp, physTemp, sysfsTemp, 2);
		else {
			append(deviceNameTemp, physTemp, sysfsTemp, 2);
		}
	}
}

/* Free the temp list */
void freeTempList() {
	/* Free pointers from main list */
	struct node_device *tmp1;
	tmp1 = devices_temp;
	while (devices_temp != NULL ) {
		tmp1 = devices_temp;
		devices_temp = devices_temp->next;
		free(tmp1);
	}
	devices_temp = NULL;
}

/* Delete a device from the main list */
int delete(char nameToDelete[MAXLENGHTLINE]) {
	struct node_device *temp, *prev;
	temp = devices;
	while (temp != NULL ) {
		if (strcmp(temp->deviceName, nameToDelete) == 0) {
			if (temp == devices) {
				devices = temp->next;
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

/* Display list of devices */
void displayListOfDevices(int flagToShow) {
	struct node_device *r;
	/* Display main list */
	if (flagToShow == 1) {
		r = devices;
	}
	/* Display temp list */
	if (flagToShow == 2) {
		r = devices_temp;
	}
	if (r == NULL ) {
		printf("The list of devices is empty\n");
	} else {
		if (flagToShow == 1) {
			printf("Devices in main list\n");
		}
		if (flagToShow == 2) {
			printf("Devices in temp list\n");
		}
		while (r != NULL ) {
			printf("-----------------------\n");
			printf("Device Name: --%s--", r->deviceName);
			printf("Phys path: %s", r->phys);
			printf("Sysfs path: %s", r->sysfs);
			//printf("-----------------------\n");
			/* Pointing to the next device in th list */
			r = r->next;
			fflush(stdout);
		}
	}
}

/* Make list of the devices*/
void makeListOfPs2AndSerialDevicesConected() {

	char line[MAXLENGHTLINE];
	FILE *fp;

	/* Command to obtain all the devices connected */
	fp = popen("cat /proc/bus/input/devices", "r");
	/* Error run command */
	if (fp == NULL ) {
		printf("Failed to run command\n");
	}
	char * token1;
	char deviceNameTemp[MAXLENGHTLINE];
	char physTemp[MAXLENGHTLINE];
	char sysfsTemp[MAXLENGHTLINE];

	/* Read output from the command running */
	while (fgets(line, sizeof line, fp) != NULL ) {
		token1 = strtok(line, " ");

		/* Get device name*/
		if (token1 != NULL ) {
			if (strcmp("N:", token1) == 0) {
				strcpy(deviceNameTemp, "");
				token1 = strtok(NULL, " ");
				token1 = strtok(NULL, "=");
				/* Go to the device name */
				while (token1 != NULL ) {
					strcat(deviceNameTemp, token1);
					token1 = strtok(NULL, " ");
				}
				//printf("%s", deviceNameTemp);
			}
		}
		/* Get phys path */
		if (token1 != NULL ) {
			if (strcmp("P:", token1) == 0) {
				/* Go to phys */
				token1 = strtok(NULL, " ");
				if (token1!=NULL){
					strcpy(physTemp, token1);
				}
			}
		}

		/* Get sysfs path */
		if (token1 != NULL ) {
			if (strcmp("S:", token1) == 0) {
				/* Go to Sysfs */
				token1 = strtok(NULL, " ");
				if(token1!=NULL){
					strcpy(sysfsTemp, token1);
				}
				//printf("%s", token1);
				/* Insert device into the list */
				insertDevice(deviceNameTemp, physTemp, sysfsTemp);
			}
		}
	}
	fclose(fp);
}

/* Make temp list of the devices*/
void makeTempListOfPs2AndSerialDevicesConected() {

	char line[MAXLENGHTLINE];
	FILE *fp;

	/* Command to obtain all the devices connected */
	fp = popen("cat /proc/bus/input/devices", "r");
	/* Error run command */
	if (fp == NULL ) {
		printf("Failed to run command\n");
	}
	char * token1;
	char deviceNameTemp[MAXLENGHTLINE];
	char physTemp[MAXLENGHTLINE];
	char sysfsTemp[MAXLENGHTLINE];

	/* Read output from the command running */
	while (fgets(line, sizeof line, fp) != NULL ) {
		token1 = strtok(line, " ");

		/* Get device name*/
		if (token1 != NULL ) {
			if (strcmp("N:", token1) == 0) {
				strcpy(deviceNameTemp, "");
				token1 = strtok(NULL, " ");
				/* Go to the device name */
				while (token1 != NULL ) {
					strcat(deviceNameTemp, token1);
					token1 = strtok(NULL, " ");
				}
				//printf("%s", freeTextName);
			}
		}
		/* Get phys path */
		if (token1 != NULL ) {
			if (strcmp("P:", token1) == 0) {
				/* Go to phys */
				token1 = strtok(NULL, " ");
				strcpy(physTemp, token1);
			}
		}

		/* Get sysfs path */
		if (token1 != NULL ) {
			if (strcmp("S:", token1) == 0) {
				/* Go to Sysfs */
				token1 = strtok(NULL, " ");
				strcpy(sysfsTemp, token1);
				//printf("%s", token1);
				/* Insert device into the list */
				insertDeviceTemp(deviceNameTemp, physTemp, sysfsTemp);
			}
		}
	}
	fclose(fp);
}

/* check if the device exists in the list */
int checkIfTheDeviceExistsInList(char deviceNameToCheck[MAXLENGHTLINE]) {
	int found = 0;
	struct node_device *runner;

	/* Pointer to the first node */
	runner = devices;
	if (runner == NULL ) {
		printf("something is wrong in checkIfTheProcessExistsInList\n");
		return -1;
	}
	while (runner != NULL ) {
		if (strcmp(runner->deviceName, deviceNameToCheck) == 0) {
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

/* Check if there is new devices connected*/
void checkNewDevicesConnected() {
	int found = -1;
	struct node_device *r;
	struct node_device *m;

	r = devices_temp;
	m = devices;
	if (r == NULL || m == NULL ) {
		printf("something is wrong\n");
		return;
	}
	/*check if there are different number of elements in main and temp list*/
		while (r != NULL ) {
			while (m != NULL ) {
				if (strcmp(r->deviceName,m->deviceName)==0) {
					found = 0;
				}
				m = m->next;
			}
			m = devices;
			/* if found==-1 outsite loop means there is new device */
			if (found == -1) {
				if (checkIfTheDeviceExistsInList(r->deviceName) == 0) {
					/* Print process name */
					printf("New device found %s ", r->deviceName);
					/* Insert new process in the Main list */
					insertDevice(r->deviceName, r->phys, r->sysfs);
				}
			}
			r = r->next;
			found = -1;
		}
}

/* check if there is a desconection device */
void checkDisconnectionDevices() {
	int found = -1;
	int deleted = 0;
	struct node_device *r;
	struct node_device *m;

	/* Point to the main list */
	r = devices;
	/* Point to the temp list */
	m = devices_temp; //temp list
	if (r == NULL || m == NULL ) {
		printf("One of the two list is empty \n");
		return;
	}
	/* Check if in the main list there is a desconection device */
		while (r != NULL ) {
			while (m != NULL ) {
				if ((strcmp(r->deviceName, m->deviceName) == 0)
						&& (found != 0)) {
					//printf("Comparing %d with %d\n", r->processPID, m->processPID);
					found = 0;
				}
				m = m->next;
			}
			m = devices_temp;
			/* if found==-1 outsite loop means there is desconection device */
			if (found == -1) {
				printf("Desconection device found %s", r->deviceName);

				/* Delete process name from the main list */
				delete(r->deviceName);
				deleted = 1;
				/* Recheck if there is more termination process */
				r = devices;

			}
			if (deleted != 1) {
				r = r->next;
			}
			deleted = 0;
			found = -1;
		}
}

/* Check if there is any device insertion or removal */
void checkAnyInsertionOrRemoval() {
	makeTempListOfPs2AndSerialDevicesConected();
	checkNewDevicesConnected();
	checkDisconnectionDevices();

	freeTempList();
}

int main(void) {
	puts("we going to detect PS2 and serial devices");

	devices = NULL;
	devices_temp = NULL;

	/* Catch child signal to avoid zomby process */
	signal(SIGCHLD, SIG_IGN );

	/* make the main list with the devices inserted */
	makeListOfPs2AndSerialDevicesConected();
	//displayListOfDevices(1);

	for (;;) {
		checkAnyInsertionOrRemoval();
		sleep(1);
	}

	fflush(stdout);
	return 0;
}
