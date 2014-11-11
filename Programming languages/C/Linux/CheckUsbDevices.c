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
	char deviceClass[MAXLENGHTLINE];
	char deviceSubClass[MAXLENGHTLINE];
	char vendorID[MAXLENGHTLINE];
	char productID[MAXLENGHTLINE];
	struct node_usb *next;
}*usbs, *usbs_temp;

/* Global variables */
libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
libusb_context *ctx = NULL; //a libusb session
int r; //for return values
ssize_t cnt; //holding number of devices in list

/* List Operations */
/* Append */
void append(char deviceClassToInsert[MAXLENGHTLINE],
		char deviceSubClassToInsert[MAXLENGHTLINE],
		char vendorIDToInsert[MAXLENGHTLINE],
		char productIDToInsert[MAXLENGHTLINE], int flagInsert) {

	/* Allocate memory for the node */
	struct node_usb *right, *temp;
	/* Allocate memory for the node */
	temp = (struct node_usb *) malloc(sizeof(struct node_usb));

	/* Assign the specific information in fields */
	/* Assign device class*/
	strcpy(temp->deviceClass, deviceClassToInsert);
	/* Assign device subclass */
	strcpy(temp->deviceSubClass, deviceSubClassToInsert);
	/* Assign vendor ID */
	strcpy(temp->vendorID, vendorIDToInsert);
	/* Assign product ID*/
	strcpy(temp->productID, productIDToInsert);

	/* Append to main devices list */
	if (flagInsert == 1) {
		right = (struct node_usb *) usbs;
	}
	/* Append to temp devices list */
	if (flagInsert == 2) {
		right = (struct node_usb *) usbs_temp;
	}
	while (right->next != NULL )
		right = right->next;
	right->next = temp;
	right = temp;
	right->next = NULL;
}

/* Add */
void add(char deviceClassToInsert[MAXLENGHTLINE],
		char deviceSubClassToInsert[MAXLENGHTLINE],
		char vendorIDToInsert[MAXLENGHTLINE],
		char productIDToInsert[MAXLENGHTLINE], int flagInsert) {

	/* Create a node to fill it with the temporal information */
	struct node_usb *temp;
	/* Allocate memory for the node */
	temp = (struct node_usb *) malloc(sizeof(struct node_usb));

	/* Assign the specific information in fields */
	/* Assign device class*/
	strcpy(temp->deviceClass, deviceClassToInsert);
	/* Assign device subclass */
	strcpy(temp->deviceSubClass, deviceSubClassToInsert);
	/* Assign vendor ID */
	strcpy(temp->vendorID, vendorIDToInsert);
	/* Assign product ID*/
	strcpy(temp->productID, productIDToInsert);

	/* Add usb device to the main list */
	if (flagInsert == 1) {
		if (usbs == NULL ) {
			usbs = temp;
			usbs->next = NULL;
		} else {
			temp->next = usbs;
			usbs = temp;
		}
	}

	/* Add usbs device to the temp list */
	if (flagInsert == 2) {
		if (usbs_temp == NULL ) {
			usbs_temp = temp;
			usbs_temp->next = NULL;
		} else {
			temp->next = usbs_temp;
			usbs_temp = temp;
		}
	}
}
/* Add in a specific location */
void addafter(int loc, char deviceClassToInsert[MAXLENGHTLINE],
		char deviceSubClassToInsert[MAXLENGHTLINE],
		char vendorIDToInsert[MAXLENGHTLINE],
		char productIDToInsert[MAXLENGHTLINE], int insertFlag) {
	int i;
	struct node_usb *left, *right, *temp;
	left = NULL;

	/* Addafter usb device in main list */
	if (insertFlag == 1) {
		right = usbs;
	}
	/* Addafter usb device in temp list */
	if (insertFlag == 2) {
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
	strcpy(temp->deviceClass, deviceClassToInsert);
	/* Assign device subclass */
	strcpy(temp->deviceSubClass, deviceSubClassToInsert);
	/* Assign vendor ID */
	strcpy(temp->vendorID, vendorIDToInsert);
	/* Assign product ID*/
	strcpy(temp->productID, productIDToInsert);

	/* add device to the list in a specific location */
	left->next = temp;
	left = temp;
	left->next = right;

}

/* Count element of the list */
int count(int flagToCount) {
	struct node_usb *n;
	int c = 0;
	/* Count elements from main list */
	if (flagToCount == 1) {
		n = usbs;
	}
	/* Count elements from temp list */
	if (flagToCount == 2) {
		n = usbs_temp;
	}
	while (n != NULL ) {
		n = n->next;
		c++;
	}
	return c;
}

/* Insert usb device */
void insertUsbDevice(char deviceClassTemp[MAXLENGHTLINE],
		char deviceSubClassTemp[MAXLENGHTLINE],
		char vendorIDTemp[MAXLENGHTLINE],
		char productIDTemp[MAXLENGHTLINE]) {

	int c = 0;
	struct node_usb *temp;

	/* Assign the devices list to temp */
	temp = usbs;

	if (temp == NULL ) {
		add(deviceClassTemp,deviceSubClassTemp,vendorIDTemp,productIDTemp, 1);
	} else {
		c = count(1);
		if (c == 0)
			add(deviceClassTemp,deviceSubClassTemp,vendorIDTemp,productIDTemp, 1);
		else if (c < count(1))
			addafter(++c, deviceClassTemp,deviceSubClassTemp,vendorIDTemp,productIDTemp, 1);
		else {
			append(deviceClassTemp,deviceSubClassTemp,vendorIDTemp,productIDTemp, 1);
		}
	}
}
/* Insert usb device in temp list */
void insertUsbDeviceTemp(char deviceClassTemp[MAXLENGHTLINE],
		char deviceSubClassTemp[MAXLENGHTLINE],
		char vendorIDTemp[MAXLENGHTLINE],
		char productIDTemp[MAXLENGHTLINE]) {

	int c = 0;
	struct node_usb *temp;

	/* Assign the devices list to temp */
	temp = usbs;

	if (temp == NULL ) {
		add(deviceClassTemp,deviceSubClassTemp,vendorIDTemp,productIDTemp, 2);
	} else {
		c = count(1);
		if (c == 0)
			add(deviceClassTemp,deviceSubClassTemp,vendorIDTemp,productIDTemp, 2);
		else if (c < count(1))
			addafter(++c, deviceClassTemp,deviceSubClassTemp,vendorIDTemp,productIDTemp, 2);
		else {
			append(deviceClassTemp,deviceSubClassTemp,vendorIDTemp,productIDTemp, 2);
		}
	}
}

/* Free the temp list */
void freeTempList() {
	/* Free pointers from main list */
	struct node_usb *tmp1;
	tmp1 = usbs_temp;
	while (usbs_temp != NULL ) {
		tmp1 = usbs_temp;
		usbs_temp = usbs_temp->next;
		free(tmp1);
	}
	usbs_temp = NULL;
}

/* Delete a device from the main list */
int delete(char productIDToDelete[MAXLENGHTLINE]) {
	struct node_usb *temp, *prev;
	temp = usbs;
	while (temp != NULL ) {
		if (strcmp(temp->productID, productIDToDelete) == 0) {
			if (temp == usbs) {
				usbs = temp->next;
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
	struct node_usb *r;
	/* Display main list */
	if (flagToShow == 1) {
		r = usbs;
	}
	/* Display temp list */
	if (flagToShow == 2) {
		r = usbs_temp;
	}
	if (r == NULL ) {
		printf("The list of devices is empty\n");
	} else {
		if (flagToShow == 1) {
			printf("Usb devices in main list\n");
		}
		if (flagToShow == 2) {
			printf("Usb devices in temp list\n");
		}
		while (r != NULL ) {
			printf("-----------------------\n");
			printf("Usb device class: --%s--", r->deviceClass);
			printf("Usb device subclass: %s", r->deviceSubClass);
			printf("Vendor id: %s", r->vendorID);
			printf("Product id: %s",r->productID);
			/* Pointing to the next device in th list */
			r = r->next;
			fflush(stdout);
		}
	}
}


/* Make list of usb devices inserted */
void makeListUsbDevices() {
	struct libusb_device_descriptor desc;
	int i;
	/* Iterating through the list of usb devices*/
	for (i = 0; i < cnt; i++) {
		int r = libusb_get_device_descriptor(devs[i], &desc);

		if (r < 0) {
			printf("failded to get device descriptor\n");
			return;
		}
		uint8_t deviceClassTemp;
		uint8_t deviceSubClassTemp;
		uint16_t vendorIDTemp;
		uint16_t productIDTemp;



		deviceClassTemp = desc.bDeviceClass;
		deviceSubClassTemp = desc.bDeviceSubClass;
		vendorIDTemp= desc.idVendor;
		productIDTemp = desc.idProduct;

		printf("Device Class: %x\n", deviceClassTemp);
		printf("Device Sub-class: %x\n", deviceSubClassTemp);
		printf("VendorID: %x\n", vendorIDTemp);
		printf("ProductID: %x\n", productIDTemp);

		//insertUsbDevice(deviceClassTemp,deviceClassTemp,vendorIDTemp,productIDTemp);
	}
}

/* Make temp list of usb devices inserted */
void makeTempListUsbDevices() {
	struct libusb_device_descriptor desc;
	int i;
	/* Iterating through the list of usb devices*/
	for (i = 0; i < cnt; i++) {
		int r = libusb_get_device_descriptor(devs[i], &desc);

		if (r < 0) {
			printf("failded to get device descriptor\n");
			return;
		}
		//printf("Device Class: %d\n", desc.bDeviceClass);
		//printf("Device Sub-class: %d\n", desc.bDeviceSubClass);
		//printf("VendorID: %x\n", desc.idVendor);
		//printf("ProductID: %x\n", desc.idProduct);
		insertUsbDeviceTemp((char*)desc.bDeviceClass,(char*)desc.bDeviceSubClass,(char*)desc.idVendor,(char*)desc.idProduct);
	}
}


/* Usb initial checking */
int usbInitialChecking() {
	/* initialize a library session */
	r = libusb_init(&ctx);
	/* check if the initialization was good */
	if (r < 0) {
		printf("Init Error\n");
		return 1;
	}
	/* set verbosity level to 3, as suggested in the documentation */
	libusb_set_debug(ctx, 3);
	/*get the list of devices */
	cnt = libusb_get_device_list(ctx, &devs);
	if (cnt < 0) {
		printf("Get Device error\n");
	}
	return 0;
}

int main() {
	usbInitialChecking();
	makeListUsbDevices();
	libusb_free_device_list(devs, 1); //free the list, unref the devices in it
	libusb_exit(ctx); //close the session
	return 0;
}

