// CheckAntivirus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Convertion types */
#include <comdef.h>  // for _bstr_t
#include <atlbase.h>
#include <atlconv.h>
#include <atlstr.h>
#include <iostream.>
#include <cstdlib>
#include <comutil.h>

# pragma comment(lib, "wbemuuid.lib")

int counterPreVista = 0;
int counterPostVista = 0;

/* Constants */
#define MAXLENGHTLINE 200
#define MAXISENABLED 10
/* Structure to store antivirus information */
struct node_antivirus{
	char antivirusName[MAXLENGHTLINE];
	int isEnabled; // isEnabled=1 means yes and isEnabled=0 means no
	struct node_antivirus *next;
}*antivirus;

/* List Operations */
/* Append */
void appendAntivirus(char antivirusNameToInsert[MAXLENGHTLINE], int isEnabledToInsert){
	
	
	struct node_antivirus *right, *temp;
	/* Allocate memory for the rule */
	temp = (struct node_antivirus*) malloc(sizeof(struct node_antivirus));

	/* Assign the specific information in fields */
	strcpy(temp->antivirusName, antivirusNameToInsert);
	temp->isEnabled=isEnabledToInsert;

	/* Append */
	right = (struct node_antivirus *) antivirus;
	while (right->next != NULL)
		right = right->next;
	right->next = temp;
	right = temp;
	right->next = NULL;
}

/* Add antivirus */
void addAntivirus(char antivirusNameToInsert[MAXLENGHTLINE], int isEnabledToInsert){

	struct node_antivirus *temp;
	/* Allocate memory for the rule */
	temp = (struct node_antivirus*) malloc(sizeof(struct node_antivirus));

	/* Assign the specific information in fields */
	strcpy(temp->antivirusName, antivirusNameToInsert);
	temp->isEnabled=isEnabledToInsert;

	/* Add rule to the list */
	if (antivirus == NULL) {
		antivirus = temp;
		antivirus->next = NULL;
	}
	else {
		temp->next = antivirus;
		antivirus = temp;
	}
}

/* Add in a specific location */
void addAntivirusAfter(int loc, char antivirusNameToInsert[MAXLENGHTLINE], int isEnabledToInsert){

	int i;
	struct node_antivirus *left, *right, *temp;
	/* initialize left pointer */
	left = NULL;

	/* Addafter in main list */
	right = antivirus;

	/* Go to the specific location */
	for (i = 1; i < loc; i++) {
		left = right;
		right = right->next;
	}
	/* Allocate memory for the node */
	temp = (struct node_antivirus *) malloc(sizeof(struct node_antivirus));

	/* Assign the specific information in fields */
	strcpy(temp->antivirusName, antivirusNameToInsert);
	temp->isEnabled=isEnabledToInsert;

	/* Add in a specific */
	left->next = temp;
	left = temp;
	left->next = right;
	return;

}

/* Count element of the antivirus list */
int countAntivirus() {
	struct node_antivirus *n;
	int c = 0;
	n = antivirus;
	while (n != NULL) {
		n = n->next;
		c++;
	}
	return c;
}

/* Insert antivirus in the list */
void insertAntivirus(char antivirusNameTemp[MAXLENGHTLINE], int isEnabledTemp){

	int c = 0;
	struct node_antivirus *temp;

	/* Assign the antivirus list to the temp list */
	temp = antivirus;

	if (temp == NULL){
		addAntivirus(antivirusNameTemp, isEnabledTemp);
	}
	else{
		c = countAntivirus();
		if (c == 0){
			addAntivirus(antivirusNameTemp, isEnabledTemp);
		}
		else if (c < countAntivirus()){
			addAntivirusAfter(++c, antivirusNameTemp, isEnabledTemp);
		}
		else{
			appendAntivirus(antivirusNameTemp, isEnabledTemp);
		}
	}
}

/* Display list of antivirus */
void displayListOfAntivirus(){
	struct node_antivirus *r;
	r = antivirus;
	if (r == NULL){
		printf("The list of antivirus is empty\n");
	}
	else{
		printf("List of Antivirus\n");
		while (r != NULL){
			printf("-------------------------\n");
			printf("Antivirus name: %s\n", r->antivirusName);
			printf("Enabled: %d\n", r->isEnabled);
			r = r->next;
		}
	}
}



/* Check if the antivirus is enabled or disabled in Windows pre-vista versions*/
int CheckIfAntivirusIsEnabledOrDisabledPreVista(){
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

		_bstr_t(L"ROOT\\SecurityCenter"), // WMI namespace
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

	//cout << "Connected to ROOT\\SecurityCenter2 WMI namespace" << endl;
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

	// For example, query for all the running processes
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM AntiVirusProduct"),
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
			// Get the value of the Name property
			hres = pclsObj->Get(L"displayName", 0, &vtProp, 0, 0);
			//wcout << "Product name: " << vtProp.bstrVal << endl;

			// Get the value of the Product state
			hres = pclsObj->Get(L"productState", 0, &vtProp, 0, 0);
			char hex[10];
			// Insert the value of producState into hex string
			sprintf(hex, "0%x", vtProp.intVal);

			//printf("Hex: %c %c %c %c %c %c \n", hex[0], hex[1], hex[2], hex[3], hex[4], hex[5]);
			//std::cout << "Product state(hex): " << std::hex << vtProp.pintVal << '\n';
			if (hex[2] == '1'){
				//printf("The antivirus is enabled\n");
			}
			else{
				//printf("The antivirus is disabled\n");
			}
			printf("\n");
			VariantClear(&vtProp);
			counterPreVista++;
		}
		//printf("Counter is %d\n", counter);
	

	}

	// Cleanup
	// ========

	pSvc->Release();
	pLoc->Release();
	CoUninitialize();

	return 0;   // Program successfully completed.

}


/* Check if the antivirus is enabled or disabled in Windows post-vista versions*/
int CheckIfAntivirusIsEnabledOrDisabledPostVista(){
	HRESULT hres;
	char antivirusTempName[MAXLENGHTLINE];
	int isEnabledTemp;

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

		_bstr_t(L"ROOT\\SecurityCenter2"), // WMI namespace
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

	//cout << "Connected to ROOT\\SecurityCenter2 WMI namespace" << endl;
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

	// For example, query for all the running processes
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM AntiVirusProduct"),
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
			// Get the value of the Name property
			hres = pclsObj->Get(L"displayName", 0, &vtProp, 0, 0);
			
			/* Convert BSTR to char array */
			_bstr_t bstrVal(vtProp.bstrVal);
			strcpy(antivirusTempName, bstrVal);

			// Get the value of the Product state
			hres = pclsObj->Get(L"productState", 0, &vtProp, 0, 0);
			char hex[10];
			int tempIsEnabled;
			// Insert the value of producState into hex string
			sprintf(hex, "0%x", vtProp.intVal);

			//printf("Hex: %c %c %c %c %c %c \n", hex[0], hex[1], hex[2], hex[3], hex[4], hex[5]);
			
			if (hex[2] == '1'){
			//	printf("The antivirus is enabled\n");
				tempIsEnabled = 1;
			}
			else{
				//printf("The antivirus is disabled\n");
				tempIsEnabled = 0;
			}
			printf("\n");
			
			/* Insert antivirus into the list */
			insertAntivirus(antivirusTempName, tempIsEnabled);
			VariantClear(&vtProp);
			counterPostVista++;
		}
		

	}

	// Cleanup
	// ========

	pSvc->Release();
	pLoc->Release();
	CoUninitialize();

	return 0;   // Program successfully completed.

}

void checkIndividualStatus(char antivirusTempToCheck[MAXLENGHTLINE], int isEnabledToCheck){
	struct node_antivirus *r;
	r = antivirus;
	if (r == NULL){
		printf("The list of antivirus is empty\n");
	}
	else{
		while (r != NULL){
			/* check the right antivirus */
			if(strcmp(r->antivirusName, antivirusTempToCheck) == 0){
				/* check if the status has changed */
				if (r->isEnabled != isEnabledToCheck){
					/* if the status has change send event*/
					if (isEnabledToCheck == 1){
						printf("Antivirus %s enabled\n", antivirusTempToCheck);
						r->isEnabled = isEnabledToCheck;
					}
					else{
						printf("Antivirus %s disabled\n", antivirusTempToCheck);
						r->isEnabled = isEnabledToCheck;
					}
				}
			}			
			r = r->next;
		}
	}

}

int checkAntivirusStatus(){

	HRESULT hres;
	char antivirusTempName[MAXLENGHTLINE];
	int isEnabledTemp;

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

		_bstr_t(L"ROOT\\SecurityCenter2"), // WMI namespace
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

	// For example, query for all the running processes
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM AntiVirusProduct"),
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
			// Get the value of the Name property
			hres = pclsObj->Get(L"displayName", 0, &vtProp, 0, 0);

			/* Convert BSTR to char array */
			_bstr_t bstrVal(vtProp.bstrVal);
			strcpy(antivirusTempName, bstrVal);

			// Get the value of the Product state
			hres = pclsObj->Get(L"productState", 0, &vtProp, 0, 0);
			char hex[10];
			int tempIsEnabled;
			// Insert the value of producState into hex string
			sprintf(hex, "0%x", vtProp.intVal);

			//printf("Hex: %c %c %c %c %c %c \n", hex[0], hex[1], hex[2], hex[3], hex[4], hex[5]);

			if (hex[2] == '1'){
				//	printf("The antivirus is enabled\n");
				tempIsEnabled = 1;
			}
			else{
				//printf("The antivirus is disabled\n");
				tempIsEnabled = 0;
			}
			

			/* Check individual status */
			checkIndividualStatus(antivirusTempName, tempIsEnabled);
			VariantClear(&vtProp);
			counterPostVista++;
		}


	}

	// Cleanup
	// ========

	pSvc->Release();
	pLoc->Release();
	CoUninitialize();

	return 0;   // Program successfully completed.


}


void main(int argc, char **argv)
{
	//CheckIfAntivirusIsEnabledOrDisabledPreVista();
	CheckIfAntivirusIsEnabledOrDisabledPostVista();
	/* Display list */
	displayListOfAntivirus();

	for (;;){
		checkAntivirusStatus();
		Sleep(1000);
	}
}
