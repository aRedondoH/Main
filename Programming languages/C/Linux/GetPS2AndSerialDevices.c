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
void append(char deviceNameToInsert[MAXLENGHTLINE],char sysfsToInsert[MAXLENGHTLINE]) {

	/* Allocate memory for the node */
	struct node_device *right, *temp;
	temp = (struct node_device *) malloc(sizeof(struct node_devide));
	/* Assign the specific information in fields */
	/* Assign name of the device */
	strcpy(temp->deviceName, deviceNameToInsert);
	/* Assign fisical location */
	strcpy(temp->Sysfs, sysfsToInsert);

	right = (struct node_rule *) devices;
	while (right->next != NULL )
		right = right->next;
	right->next = temp;
	right = temp;
	right->next = NULL;
}

/* Add */
void add(char deviceNameToInsert[MAXLENGHTLINE], char sysfsToInsert[MAXLENGHTLINE]) {
	/* Create a node to fill it with the temporal information */
	struct node_device *temp;
	/* Assign the specific information in fields */
	/* Assign name of the device */
	strcpy(temp->deviceName, deviceNameToInsert);
	/* Assign fisical location */
	strcpy(temp->Sysfs, sysfsToInsert);
	/* Add to rule list */
	if (devices == NULL ) {
		devices = temp;
		devices->next = NULL;
	} else {
		temp->next = devices;
		devices = temp;
	}
}

/* Add in a specific location */
void addafter (int loc, char deviceNameToInsert[MAXLENGHTLINE], sysfsToInsert[MAXLENGHTLINE]) {
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
		temp = (struct node_device *) malloc(sizeof(struct node_rule));
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
	char freeTextName[MAXLENGHTLINE];

	/* Read output from the command running */
	while (fgets(line, sizeof line, fp) != NULL ) {
		token1 = strtok(line, " ");

		if (strcmp("N:", token1) == 0) {
			strcpy(freeTextName, "");
			token1 = strtok(NULL, " ");
			/* Go to the device name */
			while (token1 != NULL ) {
				strcat(freeTextName, token1);
				token1 = strtok(NULL, " ");
			}
			printf("%s", freeTextName);
		}
		if (token1 != NULL ) {
			if (strcmp("S:", token1) == 0) {
				/* Go to Sysfs */
				token1 = strtok(NULL, " ");
				printf("%s", token1);
			}
		}
	}
}

int main(void) {
	puts("we going to detect PS2 and serial devices");
	makeListOfPs2AndSerialDevicesConected();

	return EXIT_SUCCESS;
}
