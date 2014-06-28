/*
 * usb.h
 *
 *  Created on: May 27, 2014
 *      Author: secnok
 */

#ifndef USB_H_
#define USB_H_

/* libusb library */
#include <libusb.h>

/* usb interface */
#define usb_interface interface

libusb_device_handle *handle;

/* GENERAL FUNCTION HEADERS */
/* check if the usb device is installed in the machine */
int checkUsbInstallation();
/* Check if the usb is compatible with the currently Linux version */
int checkUsbCompatibility();

/* USB FUNCTION HEADERS */
/* Called when a USB device is inserted */
static int hotplug_callback(libusb_context *ctx, libusb_device *dev,
		libusb_hotplug_event event, void *user_data);
/* Called when a USB device is removal */
static int hotplug_callback_detach(libusb_context *ctx, libusb_device *dev,
		libusb_hotplug_event event, void *user_data);
/* Return 1 if a new USB is inserted, 0 otherwise */
int is_USB_insertion();
/* Return 1 if a USB is removed, 0 otherwise */
int is_USB_removal();


#endif /* USB_H_ */
