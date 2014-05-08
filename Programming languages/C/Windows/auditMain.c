#include<stdio.h>
#include<Windows.h>
#include<VersionHelpers.h>
#include<stdlib.h>

/* Get currently OS */
void getWindowsVersion(){
	if (IsWindowsXPOrGreater() && !IsWindowsXPSP1OrGreater()){
		printf("OS: Windows XP\n");
	}
	if (IsWindowsXPSP1OrGreater() && !IsWindowsXPSP2OrGreater()){
		printf("OS: Windows XP SP1\n");
	}
	if (IsWindowsXPSP2OrGreater() && !IsWindowsXPSP3OrGreater()){
		printf("OS: Windows XP SP2\n");
	}
	if (IsWindowsXPSP3OrGreater() && !IsWindowsVistaOrGreater()){
		printf("OS: Windows XP SP3\n");
	}
	if (IsWindowsVistaOrGreater() && !IsWindowsVistaSP1OrGreater()){
		printf("OS: Windows Vista\n");
	}
	if (IsWindowsVistaSP1OrGreater() && !IsWindowsVistaSP2OrGreater()){
		printf("OS: Windows Vista SP1\n");
	}
	if (IsWindowsVistaSP2OrGreater() && !IsWindows7OrGreater()){
		printf("OS: Windows Vista SP2\n");
	}
	if (IsWindows7OrGreater() && !IsWindows7SP1OrGreater()){
		printf("OS: Windows 7\n");
	}
	if (IsWindows7SP1OrGreater() && !IsWindows8OrGreater()){
		printf("OS: Windows 7 SP1\n");
	}
	if (IsWindows8OrGreater() && !IsWindows8Point1OrGreater()){
		printf("OS: Windows 8\n");
	}
	if (IsWindows8Point1OrGreater()){
		printf("OS: Windows 8.x\n");
	}
	printf("\n");
}

/* Get currently open ports */
void getOpenPorts(){
	FILE *fp;
	errno_t err;
	char portsOutput[300];
	char portsOutputCopy[300];
	int count = 0;
	char *token;
	char *next_token;
	char str1[30];
	char str2[30];
	int dontPrintAnyMore = 0;

	/* Get open ports */
	system("netsh firewall show state > tempFirewallOutput.txt");
	err = fopen_s(&fp, "tempFirewallOutput.txt", "r");
	if (err != 0){
		printf("Error %d when open file", err);
	}
	strcpy(str2, "IMPORTANT:");

	/* Read the output a line at a time - output it. */
	while (fgets(portsOutput, 300, fp) != NULL) {		
		strcpy(portsOutputCopy, portsOutput); // copy of portsOutput
		token = strtok_s(portsOutputCopy, " ", &next_token);
		strcpy(str1, token);
		/* if it find the word "IMPORTANT:" it doesn't print any more*/
		int ret = strcmp(str1, str2);
		if (ret == 0){
			dontPrintAnyMore = 1;
		}
		/* print output for our purpose */
		if ((count > 10) && (dontPrintAnyMore != 1)){
			printf("%s", portsOutput);
		}
		count++;
	}
}

void audit(){
	/* Get Windows version */
	getWindowsVersion();
	/* Get Open ports*/
	getOpenPorts();
}

int __cdecl wmain(__in int argc, __in_ecount(argc) PCWSTR argv[])
{
	audit();
}