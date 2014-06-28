/*
 * usb.c
 *
 *  Created on: May 27, 2014
 *      Author: secnok
 */

#include "usb.h"
#include "snok_agent.h"


/* --------------------------------------------*/
/* ------------ USB FUCTIONS ------------------*/
/* --------------------------------------------*/
/* check if the usb device is installed in the machine */
int checkUsbInstallation() {
	char temp_string[100];
	/* Return 0 if USB is installed
	 Return other value with error associated */
	int usb_installed_state = libusb_init(NULL );

	/* Check Usb installation status */
	if (usb_installed_state != 0) {
		printf("USB error %d\n", usb_installed_state);
		snprintf(temp_string, 100, "USB init_error %d\n", usb_installed_state);
		transferEvent(my_id, USB_REMOVAL, temp_string);
	}
	return usb_installed_state;
}

/* Check if the usb is compatible with the currently Linux version */
int checkUsbCompatibility() {
	/* Check if USB hotplug is supported in the current platform */
	if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG)) {
		printf("Hotplug not supported by this build of libusb\n");
		libusb_exit(NULL );
		return EXIT_FAILURE;
	}
	return 0;
}

/* Called when a USB device is inserted */
static int hotplug_callback(libusb_context *ctx, libusb_device *dev,
		libusb_hotplug_event event, void *user_data) {

	struct libusb_device_descriptor desc;
	struct libusb_config_descriptor *conf_desc;
	int m, n;		// loop counters
	int nb_ifaces;
	char temp_string[100];

	int r = libusb_get_config_descriptor(dev, 0, &conf_desc);
	nb_ifaces = conf_desc->bNumInterfaces;
	for (m = 0; m < nb_ifaces; m++)
		for (n = 0; n < conf_desc->usb_interface[m].num_altsetting; n++)
			/* We only detect USB mass storage devices */
			if (conf_desc->usb_interface[m].altsetting[n].bInterfaceClass
					== LIBUSB_CLASS_MASS_STORAGE) {

				r = libusb_get_device_descriptor(dev, &desc);
				if (r < 0) {
					fprintf(stderr, "failed to get device descriptor%d\n", r);
					return 1;
				}

				/* Event detail information */
				// desc.idVendor has the vendor id
				// desc.idProduct has the product id
				snprintf(temp_string, 100, "USB inserted \n");
				transferEvent(my_id, USB_INSERTION, temp_string);
				printf("USB inserted \n");
			}
	return 0;
}

/* Called when a USB device is removal */
static int hotplug_callback_detach(libusb_context *ctx, libusb_device *dev,
		libusb_hotplug_event event, void *user_data) {

	struct libusb_device_descriptor desc;
	struct libusb_config_descriptor *conf_desc;
	int m, n;		// loop counters
	int nb_ifaces;
	char temp_string[100];

	int r = libusb_get_config_descriptor(dev, 0, &conf_desc);
	nb_ifaces = conf_desc->bNumInterfaces;
	for (m = 0; m < nb_ifaces; m++)
		for (n = 0; n < conf_desc->usb_interface[m].num_altsetting; n++)
			/* We only report USB mass storage devices */
			if (conf_desc->usb_interface[m].altsetting[n].bInterfaceClass
					== LIBUSB_CLASS_MASS_STORAGE) {

				r = libusb_get_device_descriptor(dev, &desc);
				if (LIBUSB_SUCCESS != r) {
					fprintf(stderr, "Error getting device descriptor\n");
				}

				/* Event detail information */
				// desc.idVendor has the vendor id
				// desc.idProduct has the product id
				snprintf(temp_string, 100, "USB removed \n");
				transferEvent(my_id, USB_REMOVAL, temp_string);
				printf("USB removed \n");
			}
	/* Under LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT event
	 * the only safe function is libusb_get_device_descriptor()
	 * this function should not be called within hotplug_callback_detach */
	libusb_close(handle);

	return 0;
}

/* Return 1 if a new USB is inserted, 0 otherwise */
int is_USB_insertion() {

	libusb_hotplug_callback_handle hp0;
	int result;
	result = libusb_hotplug_register_callback(NULL,
			LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED, 0, LIBUSB_HOTPLUG_MATCH_ANY,
			LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY,
			hotplug_callback, NULL, &hp0);
	if (LIBUSB_SUCCESS != result) {
		fprintf(stderr, "Error registering callback 0 %d\n", result);
		libusb_exit(NULL );
		return EXIT_FAILURE;
	}
	return result;
}

/* Return 1 if a USB is removed, 0 otherwise */
int is_USB_removal() {

	libusb_hotplug_callback_handle hp1;
	int result;
	result = libusb_hotplug_register_callback(NULL,
			LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT, 0, LIBUSB_HOTPLUG_MATCH_ANY,
			LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY,
			hotplug_callback_detach, NULL, &hp1);
	if (LIBUSB_SUCCESS != result) {
		fprintf(stderr, "Error registering callback 1 %d\n", result);
		libusb_exit(NULL );
		return EXIT_FAILURE;
	}
	return result;
}
