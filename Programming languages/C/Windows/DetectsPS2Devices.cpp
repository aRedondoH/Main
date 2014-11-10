// DetectsPS2Devices.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

#define _WIN32_DCOM
#include "stdafx.h"


#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#include <string.h>
# pragma comment(lib, "wbemuuid.lib")


void checkMouseInformation(){

	BOOL fResult;
	int aMouseInfo[3];

	fResult = GetSystemMetrics(SM_MOUSEPRESENT);

	if (fResult == 0)
		printf("No mouse installed.\n");
	else
	{
		printf("Mouse installed.\n");

		// Determine whether the buttons are swapped. 

		fResult = GetSystemMetrics(SM_SWAPBUTTON);

		if (fResult == 0)
			printf("Buttons not swapped.\n");
		else printf("Buttons swapped.\n");

		// Get the mouse speed and the threshold values. 

		fResult = SystemParametersInfo(
			SPI_GETMOUSE,  // get mouse information 
			0,             // not used 
			&aMouseInfo,   // holds mouse information 
			0);            // not used 

		if (fResult)
		{
			printf("Speed: %d\n", aMouseInfo[2]);
			printf("Threshold (x,y): %d,%d\n",
				aMouseInfo[0], aMouseInfo[1]);
		}
	}

}

int checkSerialPorts(){

	HRESULT hres;

	// Initialize COM.
	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
		cout << "Failed to initialize COM library. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		return 1;              // Program has failed.
	}

	// Initialize 
	hres = CoInitializeSecurity(
		NULL,
		-1,      // COM negotiates service                  
		NULL,    // Authentication services
		NULL,    // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,    // authentication
		RPC_C_IMP_LEVEL_IMPERSONATE,  // Impersonation
		NULL,             // Authentication info 
		EOAC_NONE,        // Additional capabilities
		NULL              // Reserved
		);


	if (FAILED(hres))
	{
		cout << "Failed to initialize security. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return 1;          // Program has failed.
	}

	// Obtain the initial locator to Windows Management
	// on a particular host computer.
	IWbemLocator *pLoc = 0;

	hres = CoCreateInstance(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID *)&pLoc);

	if (FAILED(hres))
	{
		cout << "Failed to create IWbemLocator object. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return 1;       // Program has failed.
	}

	IWbemServices *pSvc = 0;

	// Connect to the root\cimv2 namespace with the
	// current user and obtain pointer pSvc
	// to make IWbemServices calls.

	hres = pLoc->ConnectServer(

		_bstr_t(L"ROOT\\cimv2"), // WMI namespace
		NULL,                    // User name
		NULL,                    // User password
		0,                       // Locale
		NULL,                    // Security flags                 
		0,                       // Authority       
		0,                       // Context object
		&pSvc                    // IWbemServices proxy
		);

	if (FAILED(hres))
	{
		cout << "Could not connect. Error code = 0x"
			<< hex << hres << endl;
		pLoc->Release();
		CoUninitialize();
		return 1;                // Program has failed.
	}

	
	printf("\n");
	// Set the IWbemServices proxy so that impersonation
	// of the user (client) occurs.
	hres = CoSetProxyBlanket(

		pSvc,                         // the proxy to set
		RPC_C_AUTHN_WINNT,            // authentication service
		RPC_C_AUTHZ_NONE,             // authorization service
		NULL,                         // Server principal name
		RPC_C_AUTHN_LEVEL_CALL,       // authentication level
		RPC_C_IMP_LEVEL_IMPERSONATE,  // impersonation level
		NULL,                         // client identity 
		EOAC_NONE                     // proxy capabilities     
		);

	if (FAILED(hres))
	{
		cout << "Could not set proxy blanket. Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 1;               // Program has failed.
	}


	// Use the IWbemServices pointer to make requests of WMI. 
	// Make requests here:

	// For example, query to obtain information of devices connected
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_Keyboard"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hres))
	{
		cout << "Query for processes failed. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 1;               // Program has failed.
	}
	else
	{
		IWbemClassObject *pclsObj;
		ULONG uReturn = 0;


		while (pEnumerator)
		{
			hres = pEnumerator->Next(WBEM_INFINITE, 1,
				&pclsObj, &uReturn);

			if (0 == uReturn)
			{
				break;
			}

			VARIANT vtProp;
			VariantInit(&vtProp);
			// Get the value of Description
			hres = pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
			wcout << "Description: " << vtProp.bstrVal << endl;

			// Get the value of Description
			hres = pclsObj->Get(L"Layout", 0, &vtProp, 0, 0);
			wcout << "Layout: " << vtProp.bstrVal << endl;

			// Get the value of Description
			hres = pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);
			wcout << "DeviceID: " << vtProp.bstrVal << endl;

			// Get the value of Description
			hres = pclsObj->Get(L"PNPDeviceID", 0, &vtProp, 0, 0);
			wcout << "PNPDeviceID: " << vtProp.bstrVal << endl;

			// Get the value of Description
			hres = pclsObj->Get(L"Status", 0, &vtProp, 0, 0);
			wcout << "Status: " << vtProp.bstrVal << endl;
	
			printf("\n");
			VariantClear(&vtProp);
		
		}



	}

	// Cleanup
	// ========

	pSvc->Release();
	pLoc->Release();
	CoUninitialize();

	return 0;   // Program successfully completed.



}

void main()
{
	checkSerialPorts();
}

