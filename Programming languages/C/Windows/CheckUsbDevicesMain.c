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

void printdev(libusb_device *dev); //prototype of the function

int main() {
	libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
	libusb_context *ctx = NULL; //a libusb session
	int r; //for return values
	ssize_t cnt; //holding number of devices in list
	r = libusb_init(&ctx); //initialize a library session
	if (r < 0) {
		printf("Init Error\n");
		return 1;
	}
	libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
	cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
	if (cnt < 0) {
		printf("Get Device error\n");
	}

	int i; //for iterating through the list
	for (i = 0; i < cnt; i++) {
		printf("Device: %d\n", i + 1);
		printdev(devs[i]); //print specs of this device
	}
	libusb_free_device_list(devs, 1); //free the list, unref the devices in it
	libusb_exit(ctx); //close the session
	return 0;
}

void printdev(libusb_device *dev) {
	struct libusb_device_descriptor desc;
	int r = libusb_get_device_descriptor(dev, &desc);
	if (r < 0) {
		printf("failded to get device descriptor\n");
		return;
	}

	//printf("Number of posible configurations: %d ", desc.bNumConfigurations);
	printf("Device Class: %d\n", desc.bDeviceClass);
	printf("Device Sub-class: %d\n", desc.bDeviceSubClass);
	printf("VendorID: %x\n", desc.idVendor);
	printf("ProductID: %x\n", desc.idProduct);
	//char paco[256];
	//libusb_get_string_descriptor(dev,desc.iManufacturer, paco, sizeof(paco));
	//printf("Manufacture: %s\n", paco);
	struct libusb_config_descriptor *config;
	libusb_get_config_descriptor(dev, 0, &config);

	//printf("Interfaces: %d ||| ", config->bNumInterfaces);
	//const struct libusb_interface *inter;
	//const struct libusb_interface_descriptor *interdesc;
	//const struct libusb_endpoint_descriptor *epdesc;

	//int i;
	//for (i = 0; i < (int)config->bNumInterfaces; i++) {
		//inter = &config->interface[i];

		//printf("Number of alternate settings: %d | ", inter->num_altsetting);
		//int j;
		//for (j = 0; j < inter->num_altsetting; j++) {
			//interdesc = &inter->altsetting[j];

			//printf("Interface Number: %d\n", interdesc->bInterfaceNumber);

			//printf("Number of endpoints: %d | ", interdesc->bNumEndpoints);
			//int k;
			//for (k = 0; k < (int)interdesc->bNumEndpoints; k++) {
				//epdesc = &interdesc->endpoint[k];

				//printf("Descriptor Type: %d\n", epdesc->bDescriptorType);

				//printf("EP Address: %d | ", epdesc->bEndpointAddress);
			//}
		//}
	//}
	//cout<<endl<<endl<<endl;
	printf("\n\n");
	//libusb_free_config_descriptor(config);
}