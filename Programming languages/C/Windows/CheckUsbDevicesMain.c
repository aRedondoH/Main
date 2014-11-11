/*
============================================================================
Name        : CheckUsbDevices.c
Author      : Alberto.R.
Version     :
Copyright   : Your copyright notice
Description : Hello World in C, Ansi-style
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>
#include <inttypes.h>
#include <string.h>

/* Constants */
#define MAXLENGHTLINE 200

/* Record to save the devices */
struct node_usb {
	uint8_t deviceClass;
	uint8_t deviceSubClass;
	uint16_t vendorID;
	uint16_t productID;
	struct node_usb *next;
}*usbs, *usbs_temp;

/* Global variables */
libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
libusb_context *ctx = NULL; //a libusb session
int r; //for return values
ssize_t cnt; //holding number of devices in list

/* Initialize the Usb environment */
void initializeUsb(){
	/* Initialize a library session */
	r = libusb_init(&ctx);
	/* check if the initialization was good */
	if (r < 0) {
		printf("Init Error\n");
		return 1;
	}
	/* set verbosity level to 3, as suggested in the documentation */
	libusb_set_debug(ctx, 3);
}

/* Usb initial checking */
int getListUsbDevices() {	
	/*get the list of devices */
	cnt = libusb_get_device_list(ctx, &devs);
	if (cnt < 0) {
		printf("Get Device error\n");
	}
	return 0;
}

/* List Operations */
/* Append */
void append(uint8_t deviceClassToInsert, uint8_t deviceSubClassToInsert,
	uint16_t vendorIDToInsert, uint16_t productIDToInsert, int flagInsert) {

	/* Allocate memory for the node */
	struct node_usb *right, *temp;
	right = NULL;
	/* Allocate memory for the node */
	temp = (struct node_usb *) malloc(sizeof(struct node_usb));

	/* Assign the specific information in fields */
	/* Assign device class*/
	temp->deviceClass = deviceClassToInsert;
	/* Assign device subclass */
	temp->deviceSubClass = deviceSubClassToInsert;
	/* Assign vendor ID */
	temp->vendorID = vendorIDToInsert;
	/* Assign product ID*/
	temp->productID = productIDToInsert;

	/* Append to main devices list */
	if (flagInsert == 1) {
		right = (struct node_usb *) usbs;
	}
	/* Append to temp devices list */
	if (flagInsert == 2) {
		right = (struct node_usb *) usbs_temp;
	}
	while (right->next != NULL)
		right = right->next;
	right->next = temp;
	right = temp;
	right->next = NULL;
}

/* Add */
void add(uint8_t deviceClassToInsert, uint8_t deviceSubClassToInsert,
	uint16_t vendorIDToInsert, uint16_t productIDToInsert, int flagInsert) {

	/* Create a node to fill it with the temporal information */
	struct node_usb *temp;
	/* Allocate memory for the node */
	temp = (struct node_usb *) malloc(sizeof(struct node_usb));

	/* Assign the specific information in fields */
	/* Assign device class*/
	temp->deviceClass = deviceClassToInsert;
	/* Assign device subclass */
	temp->deviceSubClass = deviceSubClassToInsert;
	/* Assign vendor ID */
	temp->vendorID = vendorIDToInsert;
	/* Assign product ID*/
	temp->productID = productIDToInsert;

	/* Add usb device to the main list */
	if (flagInsert == 1) {
		if (usbs == NULL) {
			usbs = temp;
			usbs->next = NULL;
		}
		else {
			temp->next = usbs;
			usbs = temp;
		}
	}

	/* Add usbs device to the temp list */
	if (flagInsert == 2) {
		if (usbs_temp == NULL) {
			usbs_temp = temp;
			usbs_temp->next = NULL;
		}
		else {
			temp->next = usbs_temp;
			usbs_temp = temp;
		}
	}
}
/* Add in a specific location */
void addafter(int loc, uint8_t deviceClassToInsert,
	uint8_t deviceSubClassToInsert, uint16_t vendorIDToInsert,
	uint16_t productIDToInsert, int flagInsert) {
	int i;
	struct node_usb *left, *right, *temp;
	left = NULL;
	right = NULL;
	/* Addafter usb device in main list */
	if (flagInsert == 1) {
		right = usbs;
	}
	/* Addafter usb device in temp list */
	if (flagInsert == 2) {
		right = usbs_temp;
	}
	for (i = 1; i < loc; i++) {
		left = right;
		right = right->next;
	}

	/* Allocate memory for the node */
	temp = (struct node_usb *) malloc(sizeof(struct node_usb));

	/* Assign the specific information in fields */
	/* Assign device class*/
	temp->deviceClass = deviceClassToInsert;
	/* Assign device subclass */
	temp->deviceSubClass = deviceSubClassToInsert;
	/* Assign vendor ID */
	temp->vendorID = vendorIDToInsert;
	/* Assign product ID*/
	temp->productID = productIDToInsert;

	/* add device to the list in a specific location */
	left->next = temp;
	left = temp;
	left->next = right;

}

/* Count element of the list */
int count(int flagToCount) {
	struct node_usb *n;
	int c = 0;
	n = NULL;
	/* Count elements from main list */
	if (flagToCount == 1) {
		n = usbs;
	}
	/* Count elements from temp list */
	if (flagToCount == 2) {
		n = usbs_temp;
	}
	while (n != NULL) {
		n = n->next;
		c++;
	}
	return c;
}

/* Insert usb device */
void insertUsbDevice(uint8_t deviceClassTemp, uint8_t deviceSubClassTemp,
	uint16_t vendorIDTemp, uint16_t productIDTemp) {

	int c = 0;
	struct node_usb *temp;

	/* Assign the devices list to temp */
	temp = usbs;

	if (temp == NULL) {
		add(deviceClassTemp, deviceSubClassTemp, vendorIDTemp, productIDTemp,
			1);
	}
	else {
		c = count(1);
		if (c == 0)
			add(deviceClassTemp, deviceSubClassTemp, vendorIDTemp,
			productIDTemp, 1);
		else if (c < count(1))
			addafter(++c, deviceClassTemp, deviceSubClassTemp, vendorIDTemp,
			productIDTemp, 1);
		else {
			append(deviceClassTemp, deviceSubClassTemp, vendorIDTemp,
				productIDTemp, 1);
		}
	}
}
/* Insert usb device in temp list */
void insertUsbDeviceTemp(uint8_t deviceClassTemp, uint8_t deviceSubClassTemp,
	uint16_t vendorIDTemp, uint16_t productIDTemp) {

	int c = 0;
	struct node_usb *temp;

	/* Assign the devices list to temp */
	temp = usbs_temp;

	if (temp == NULL) {
		add(deviceClassTemp, deviceSubClassTemp, vendorIDTemp, productIDTemp,
			2);
	}
	else {
		c = count(1);
		if (c == 0)
			add(deviceClassTemp, deviceSubClassTemp, vendorIDTemp,
			productIDTemp, 2);
		else if (c < count(1))
			addafter(++c, deviceClassTemp, deviceSubClassTemp, vendorIDTemp,
			productIDTemp, 2);
		else {
			append(deviceClassTemp, deviceSubClassTemp, vendorIDTemp,
				productIDTemp, 2);
		}
	}
}

/* Free the temp list */
void freeTempList() {
	/* Free pointers from main list */
	struct node_usb *tmp1;
	tmp1 = usbs_temp;
	while (usbs_temp != NULL) {
		tmp1 = usbs_temp;
		usbs_temp = usbs_temp->next;
		free(tmp1);
	}
	usbs_temp = NULL;
}

/* Delete a device from the main list */
int delete(uint16_t productIDToDelete) {
	struct node_usb *temp, *prev;
	temp = usbs;
	prev = NULL;
	while (temp != NULL) {
		if (temp->productID == productIDToDelete) {
			if (temp == usbs) {
				usbs = temp->next;
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

/* Display list of devices */
void displayListOfDevices(int flagToShow) {
	struct node_usb *r;
	r = NULL;
	/* Display main list */
	if (flagToShow == 1) {
		r = usbs;
	}
	/* Display temp list */
	if (flagToShow == 2) {
		r = usbs_temp;
	}
	if (r == NULL) {
		printf("The list of devices is empty\n");
	}
	else {
		if (flagToShow == 1) {
			printf("Usb devices in main list\n");
		}
		if (flagToShow == 2) {
			printf("Usb devices in temp list\n");
		}
		while (r != NULL) {
			printf("-----------------------\n");
			printf("Usb device class: %x\n", r->deviceClass);
			printf("Usb device subclass: %x\n", r->deviceSubClass);
			printf("Vendor id: %x\n", r->vendorID);
			printf("Product id: %x\n", r->productID);
			/* Pointing to the next device in th list */
			r = r->next;
			fflush(stdout);
		}
	}
	printf("\n");
}

/* Make list of usb devices inserted */
void makeListUsbDevices() {
	struct libusb_device_descriptor desc;
	int i;
	uint8_t deviceClassTemp;
	uint8_t deviceSubClassTemp;
	uint16_t vendorIDTemp;
	uint16_t productIDTemp;

	getListUsbDevices();

	/* Iterating through the list of usb devices*/
	for (i = 0; i < cnt; i++) {
		int r = libusb_get_device_descriptor(devs[i], &desc);

		if (r < 0) {
			printf("failded to get device descriptor\n");
			return;
		}

		/* Assign the specific values to temp variables */
		deviceClassTemp = desc.bDeviceClass;
		deviceSubClassTemp = desc.bDeviceSubClass;
		vendorIDTemp = desc.idVendor;
		productIDTemp = desc.idProduct;
		/* Insert usb values into main list */
		insertUsbDevice(deviceClassTemp, deviceSubClassTemp, vendorIDTemp,
			productIDTemp);
	}
}

/* Make temp list of usb devices inserted */
void makeTempListUsbDevices() {
	struct libusb_device_descriptor desc;
	int i;
	uint8_t deviceClassTemp;
	uint8_t deviceSubClassTemp;
	uint16_t vendorIDTemp;
	uint16_t productIDTemp;

	getListUsbDevices();

	/* Iterating through the list of usb devices*/
	for (i = 0; i < cnt; i++) {
		int r = libusb_get_device_descriptor(devs[i], &desc);

		if (r < 0) {
			printf("failed to get device descriptor\n");
			return;
		}
		/* Assign the specific values to temp variables */
		deviceClassTemp = desc.bDeviceClass;
		deviceSubClassTemp = desc.bDeviceSubClass;
		vendorIDTemp = desc.idVendor;
		productIDTemp = desc.idProduct;
		/* Insert values into temp list */
		insertUsbDeviceTemp(deviceClassTemp, deviceSubClassTemp, vendorIDTemp,
			productIDTemp);
	}
}

/* Check if the device exists in the list */
int checkIfTheDeviceExistsInList(uint16_t idProductToCheck) {
	int found = 0;
	struct node_usb *runner;

	/* Pointer to the first node */
	runner = usbs;
	if (runner == NULL) {
		printf("something is wrong in checkIfTheProcessExistsInList\n");
		return -1;
	}
	while (runner != NULL) {
		if (runner->productID == idProductToCheck) {
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

/* Check if there are new devices connected */
void checkNewDevicesConnected() {
	int found = -1;
	struct node_usb *r;
	struct node_usb *m;

	r = usbs_temp;
	m = usbs;
	if (r == NULL || m == NULL) {
		printf("something is wrong\n");
		return;
	}
	/*check if there are different number of elements in main and temp list*/
	while (r != NULL) {
		while (m != NULL) {
			if (r->productID == m->productID) {
				found = 0;
			}
			m = m->next;
		}
		m = usbs;
		/* if found==-1 outsite loop means there is new device */
		if (found == -1) {
			if (checkIfTheDeviceExistsInList(r->productID) == 0) {
				/* Print process name */
				printf("New device found productID %x\n", r->productID);
				fflush(stdout);
				/* Insert new process in the Main list */
				insertUsbDevice(r->deviceClass, r->deviceSubClass, r->vendorID,
					r->productID);
			}
		}
		r = r->next;
		found = -1;
	}
}

/* Check if there is a disconnection device */
void checkDisconnectionDevices() {
	int found = -1;
	int deleted = 0;
	struct node_usb *r;
	struct node_usb *m;

	/* Point to the main list */
	r = usbs;
	/* Point to the temp list */
	m = usbs_temp; //temp list
	if (r == NULL || m == NULL) {
		printf("One of the two list is empty \n");
		return;
	}
	/* Check if in the main list there is a desconection device */
	while (r != NULL) {
		while (m != NULL) {
			if ((r->productID == m->productID) && (found != 0)) {
				//printf("Comparing %d with %d\n", r->processPID, m->processPID);
				found = 0;
			}
			m = m->next;
		}
		m = usbs_temp;
		/* if found==-1 outsite loop means there is desconection device */
		if (found == -1) {
			printf("Disconnection device found productID %x\n", r->productID);
			fflush(stdout);
			/* Delete process name from the main list */
			delete(r->productID);
			deleted = 1;
			/* Recheck if there is more termination process */
			r = usbs;

		}
		if (deleted != 1) {
			r = r->next;
		}
		deleted = 0;
		found = -1;
	}
}

/* Check if there is any usb device insertion or removal */
void checkAnyInsertionOrRemoval() {
	makeTempListUsbDevices();
	checkNewDevicesConnected();
	checkDisconnectionDevices();

	freeTempList();
}


int main() {
	/* Initialize lists */
	usbs = NULL;
	usbs_temp = NULL;
	 
	initializeUsb();
	getListUsbDevices();
	makeListUsbDevices();
	for (;;) {
		checkAnyInsertionOrRemoval();
		Sleep(1000);
	}

	//libusb_free_device_list(devs, 1); //free the list, unref the devices in it
	//libusb_exit(ctx); //close the session

	return 0;
}