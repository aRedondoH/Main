#include<stdio.h>
#include<Windows.h>
#include<VersionHelpers.h>
#include<stdlib.h>


void getWindowsVersion(__in int argc, __in_ecount(argc) PCWSTR argv[]){
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	if (IsWindowsXPOrGreater() && !IsWindowsXPSP1OrGreater()){
		printf("Windows XP\n");
	}
	if (IsWindowsXPSP1OrGreater() && !IsWindowsXPSP2OrGreater()){
		printf("Windows XP SP1\n");
	}
	if (IsWindowsXPSP2OrGreater() && !IsWindowsXPSP3OrGreater()){
		printf("Windows XP SP2\n");
	}
	if (IsWindowsXPSP3OrGreater() && !IsWindowsVistaOrGreater()){
		printf("Windows XP SP3\n");
	}
	if (IsWindowsVistaOrGreater() && !IsWindowsVistaSP1OrGreater()){
		printf("Windows Vista\n");
	}
	if (IsWindowsVistaSP1OrGreater() && !IsWindowsVistaSP2OrGreater()){
		printf("Windows Vista SP1\n");
	}
	if (IsWindowsVistaSP2OrGreater() && !IsWindows7OrGreater()){
		printf("Windows Vista SP2\n");
	}
	if (IsWindows7OrGreater() && !IsWindows7SP1OrGreater()){
		printf("Windows 7\n");
	}
	if (IsWindows7SP1OrGreater() && !IsWindows8OrGreater()){
		printf("Windows 7 SP1\n");
	}
	if (IsWindows8OrGreater() && !IsWindows8Point1OrGreater()){
		printf("Windows 8\n");
	}
	if (IsWindows8Point1OrGreater()){
		printf("Windows 8.x\n");
	}

}


void getOpenPorts(){
	FILE *fp;
	errno_t err;
	char portsOutput[5000];
	/* Get open ports */
	system("netsh firewall show state > tempFirewallOutput.txt");
	err = fopen_s(&fp,"tempFirewallOutput.txt", "r");
	if (err != 0){
		printf("Error %d when open file", err);
	}
	/* Read the output a line at a time - output it. */
	while (fgets(portsOutput, sizeof(portsOutput)-1, fp) != NULL) {
		printf("%s", portsOutput);
	}
	
}
void audit(__in int argc, __in_ecount(argc) PCWSTR argv[]){

	/* Get Windows version */
	getWindowsVersion(argc, argv);
	/* Get Open ports*/
	getOpenPorts();
}

int __cdecl wmain(__in int argc, __in_ecount(argc) PCWSTR argv[])
{
	audit(argc, argv);
}