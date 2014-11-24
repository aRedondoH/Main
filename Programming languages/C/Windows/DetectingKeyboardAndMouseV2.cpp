// DetectingKeyboardAndMouseV2.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>


/*#ifdef _DEBUG
#define new DEBUG_NEW
#endif*/

int checkPS2SerialDevices(){

	int nRetCode = 0;
	// TODO: code your application's behavior here.
	UINT nDevices;
	PRAWINPUTDEVICELIST pRawInputDeviceList;
	if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0)
	{
		printf("Errors...\n");
		return 1;
	}

	if ((pRawInputDeviceList = (PRAWINPUTDEVICELIST)malloc(sizeof(RAWINPUTDEVICELIST) * nDevices)) == NULL)
	{
		printf("Initialization failed...\n");
		return 1;
	}

	int nNoOfDevices = 0;
	if ((nNoOfDevices = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST))) == ((UINT)-1))
	{
		return 1;
	}
	RID_DEVICE_INFO rdi;
	rdi.cbSize = sizeof(RID_DEVICE_INFO);
	printf("****************************************************\n");
	printf("PS/2 serial devices connected\n");
	for (int i = 0; i < nNoOfDevices; i++)
	{
		UINT size = 256;
		TCHAR tBuffer[256] = { 0 };
		if (GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, tBuffer, &size) < 0)
		{
			// Error in reading device name
		}
		_tprintf(L"Device Name: %s\n", tBuffer);

		UINT cbSize = rdi.cbSize;
		if (GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &rdi, &cbSize) < 0)
		{
			// Error in reading information
		}

		if (rdi.dwType == RIM_TYPEMOUSE)
		{
			printf("ID for Mouse: %ld\n", rdi.mouse.dwId);
			printf("Number of Buttons: %ld\n", rdi.mouse.dwNumberOfButtons);
			//printf("Sample rate(Number of data points): %ld\n", rdi.mouse.dwSampleRate);
			printf("\n");
		}
		if (rdi.dwType == RIM_TYPEKEYBOARD)
		{
			printf("Keyboard Mode: %ld\n", rdi.keyboard.dwKeyboardMode);
			//printf("Number of function keys: %ld\n", rdi.keyboard.dwNumberOfIndicators);
			//printf("Number of indicators: %ld\n", rdi.keyboard.dwNumberOfIndicators);
			printf("Number of total keys: %ld\n", rdi.keyboard.dwNumberOfKeysTotal);
			printf("Type of the keyboard: %ld\n", rdi.keyboard.dwType);
			printf("Sybtype of the keyboard: %ld\n", rdi.keyboard.dwKeyboardMode);
			printf("\n");
		}
		if (rdi.dwType == RIM_TYPEHID)
		{
			printf("Vendor Id: %ld\n", rdi.hid.dwVendorId);
			printf("Product Id: %ld\n", rdi.hid.dwProductId);
			printf("Version No: %ld\n", rdi.hid.dwVersionNumber);
			//printf("Usage for the device: %ld\n", rdi.hid.usUsage);
			//printf("Usage Page for the device: %ld\n", rdi.hid.usUsagePage);
			printf("\n");
		}
	}
	free(pRawInputDeviceList);
	return 0;
}


int main()
{
	checkPS2SerialDevices();
	return 0;
}

