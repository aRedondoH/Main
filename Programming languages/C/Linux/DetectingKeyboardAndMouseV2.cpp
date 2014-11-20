// DetectingKeyboardAndMouseV2.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>


/*#ifdef _DEBUG
#define new DEBUG_NEW
#endif*/

//using namespace std;

int main()
{
	int nRetCode = 0;

	
	
	
		// TODO: code your application's behavior here.


		UINT nDevices;
		PRAWINPUTDEVICELIST pRawInputDeviceList;
		if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0)
		{
			//cout << "Errors..." << endl;
			printf("Errors...\n");
			return 1;
		}

		if ((pRawInputDeviceList = (PRAWINPUTDEVICELIST)malloc(sizeof(RAWINPUTDEVICELIST) * nDevices)) == NULL)
		{
			//cout << "Initialization failed..." << endl;
			printf("Initialization failed...\n");
			return 1;
		}

		int nNoOfDevices = 0;
		if ((nNoOfDevices = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST))) == ((UINT)-1))
		{
			// Error
			return 1;
		}

		RID_DEVICE_INFO rdi;
		rdi.cbSize = sizeof(RID_DEVICE_INFO);

		for (int i = 0; i < nNoOfDevices; i++)
		{
			UINT size = 256;
			TCHAR tBuffer[256] = { 0 };
			if (GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, tBuffer, &size) < 0)
			{
				// Error in reading device name
			}

			// cout << "Device Name: " << tBuffer << endl;
			_tprintf(L"Device Name: %s\n", tBuffer);

			UINT cbSize = rdi.cbSize;
			if (GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &rdi, &cbSize) < 0)
			{
				// Error in reading information
			}

			if (rdi.dwType == RIM_TYPEMOUSE)
			{
				//cout << "ID for Mouse:" << rdi.mouse.dwId << endl;
				//cout << "Number of Buttons:" << rdi.mouse.dwNumberOfButtons << endl;
				//cout << "Sample rate(Number of data points):" << rdi.mouse.dwSampleRate << endl;
				//cout << "**************************" << endl;
				printf("ID for Mouse: %ld\n", rdi.mouse.dwId);
				printf("Number of Buttons: %ld\n", rdi.mouse.dwNumberOfButtons);
				printf("Sample rate(Number of data points): %ld\n", rdi.mouse.dwSampleRate);
				printf("**************************\n");

			}

			if (rdi.dwType == RIM_TYPEKEYBOARD)
			{
				//cout << "Keyboard Mode:" << rdi.keyboard.dwKeyboardMode << endl;
				//cout << "Number of function keys:" << rdi.keyboard.dwNumberOfFunctionKeys << endl;
				//cout << "Number of indicators:" << rdi.keyboard.dwNumberOfIndicators << endl;
				//cout << "Number of keys total: " << rdi.keyboard.dwNumberOfKeysTotal << endl;
				//cout << "Type of the keyboard: " << rdi.keyboard.dwType << endl;
				//cout << "Subtype of the keyboard: " << rdi.keyboard.dwSubType << endl;
				//cout << "***********************" << endl;
				printf("Keyboard Mode: %ld\n", rdi.keyboard.dwKeyboardMode);
				printf("Number of function keys: %ld\n", rdi.keyboard.dwNumberOfIndicators);
				printf("Number of indicators: %ld\n", rdi.keyboard.dwNumberOfIndicators);
				printf("Number of total keys: %ld\n", rdi.keyboard.dwNumberOfKeysTotal);
				printf("Type of the keyboard: %ld\n", rdi.keyboard.dwType);
				printf("Sybtype of the keyboard: %ld\n", rdi.keyboard.dwKeyboardMode);
				printf("***********************\n");
			}

			if (rdi.dwType == RIM_TYPEHID)
			{
				
			/*	cout << "Vendor Id:" << rdi.hid.dwVendorId << endl;
				cout << "Product Id:" << rdi.hid.dwProductId << endl;
				cout << "Version No:" << rdi.hid.dwVersionNumber << endl;
				cout << "Usage for the device: " << rdi.hid.usUsage << endl;
				cout << "Usage Page for the device: " << rdi.hid.usUsagePage << endl;
				cout << "***********************" << endl;*/
				printf("Vendor Id: %ld\n", rdi.hid.dwVendorId);
				printf("Product Id: %ld\n", rdi.hid.dwProductId);
				printf("Version No: %ld\n", rdi.hid.dwVersionNumber);
				printf("Usage for the device: %ld\n", rdi.hid.usUsage);
				printf("Usage Page for the device: %ld\n", rdi.hid.usUsagePage);
				printf("***********************\n");
			}
		}

		//free(pRawInputDeviceList);
	

		return 0;
}

