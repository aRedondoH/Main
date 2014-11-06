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

/* Constants */
#define MAXLENGHTLINE 200

/* Record to save the devices */
struct node_device {
	char deviceName[MAXLENGHTLINE];
	char Sysfs[MAXLENGHTLINE];
	struct node_device *next;
}*devices;

/* List Operations */
/* Append */
void append(char deviceNameToInsert[MAXLENGHTLINE],
		char sysfsToInsert[MAXLENGHTLINE]) {
	/* Allocate memory for the node */
	struct node_device *right, *temp;
	/* Allocate memory for the node */
	temp = (struct node_device *) malloc(sizeof(struct node_device));
	/* Assign the specific information in fields */
	/* Assign name of the device */
	strcpy(temp->deviceName, deviceNameToInsert);
	/* Assign fisical location */
	strcpy(temp->Sysfs, sysfsToInsert);

	right = (struct node_device *) devices;
	while (right->next != NULL )
		right = right->next;
	right->next = temp;
	right = temp;
	right->next = NULL;
}

/* Add */
void add(char deviceNameToInsert[MAXLENGHTLINE],
		char sysfsToInsert[MAXLENGHTLINE]) {
	/* Create a node to fill it with the temporal information */
	struct node_device *temp;
	/* Allocate memory for the node */
	temp = (struct node_device *) malloc (sizeof(struct node_device));
	/* Assign the specific information in fields */
	/* Assign name of the device */
	strcpy(temp->deviceName, deviceNameToInsert);
	/* Assign physical location */
	strcpy(temp->Sysfs, sysfsToInsert);
	/* Add device to the list */
	if (devices == NULL ) {
		devices = temp;
		devices->next = NULL;
	} else {
		temp->next = devices;
		devices = temp;
	}
}

/* Add in a specific location */
void addafter(int loc, char deviceNameToInsert[MAXLENGHTLINE],
		char sysfsToInsert[MAXLENGHTLINE]) {
	int i;
	struct node_device *left, *right, *temp;
	left = NULL;

	/* Addafter in main list */
	right = devices;

	for (i = 1; i < loc; i++) {
		left = right;
		right = right->next;
	}

	/* Allocate memory for the node */
	temp = (struct node_device *) malloc(sizeof(struct node_device));

	/* Assign the specific information in fields */
	/* Assign name of the device */
	strcpy(temp->deviceName, deviceNameToInsert);
	/* Assign fisical location */
	strcpy(temp->Sysfs, sysfsToInsert);

	/* add device to the list in a specific location */
	left->next = temp;
	left = temp;
	left->next = right;

}

/* Count element of the list */
int count() {
	struct node_device *n;
	int c = 0;
	n = devices;
	while (n != NULL ) {
		n = n->next;
		c++;
	}
	return c;
}

/* Insert device */
void insertDevice(char deviceNameTemp[MAXLENGHTLINE],
		char sysfsTemp[MAXLENGHTLINE]) {

	int c = 0;
	struct node_device *temp;

	/* Assign the devices list to temp */
	temp = devices;

	if (temp == NULL ) {
		add(deviceNameTemp, sysfsTemp);
	} else {
		c = count();
		if (c == 0)
			add(deviceNameTemp, sysfsTemp);
		else if (c < count())
			addafter(++c, deviceNameTemp, sysfsTemp);
		else {
			append(deviceNameTemp, sysfsTemp);
		}
	}
}

/* Display list of devices */
void displayListOfDevices() {
	struct node_device *r;
	r = devices;
	if (r == NULL ) {
		printf("The list of devices is empty\n");
	} else {
		printf("List of Devices\n");
		while (r != NULL ) {
			printf("-----------------------\n");
			printf("Device Name: %s", r->deviceName);
			printf("Physical path: %s", r->Sysfs);
			//printf("-----------------------\n");
			/* Pointing to the next device in th list */
			r = r->next;
			fflush(stdout);
		}
	}
}

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
	char physicalNameTemp[MAXLENGHTLINE];

	/* Read output from the command running */
	while (fgets(line, sizeof line, fp) != NULL ) {
		token1 = strtok(line, " ");

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

		if (token1 != NULL ) {
			if (strcmp("S:", token1) == 0) {
				/* Go to Sysfs */
				token1 = strtok(NULL, " ");
				strcpy(physicalNameTemp, token1);
				//printf("%s", token1);
				/* Insert device into the list */
				insertDevice(deviceNameTemp, physicalNameTemp);
			}
		}
	}
	fclose(fp);
}

int main(void) {
	puts("we going to detect PS2 and serial devices");
	//for(;;){
		makeListOfPs2AndSerialDevicesConected();
		displayListOfDevices();
	//}
	fflush(stdout);
	return 0;
}
