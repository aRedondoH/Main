#include<stdio.h>
#include<Windows.h>
#include<VersionHelpers.h>

void getWindowsVersion(__in int argc, __in_ecount(argc) PCWSTR argv[]){
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	if (IsWindowsServer())
	{
		printf("This Windows is a server\n");
	}
	else
	{
		printf("This Windows is a client\n");
	}

	if (IsWindowsXPOrGreater() && !IsWindowsXPSP1OrGreater())
	{
		printf("Windows XP\n");
	}

	if (IsWindowsXPSP1OrGreater() && !IsWindowsXPSP2OrGreater())
	{
		printf("Windows XPSP1\n");
	}

	if (IsWindowsXPSP2OrGreater() && !IsWindowsXPSP3OrGreater())
	{
		printf("Windows XPSP2\n");
	}

	if (IsWindowsXPSP3OrGreater() && !IsWindowsVistaOrGreater())
	{
		printf("Windows XPSP3\n");
	}

	if (IsWindowsVistaOrGreater() && !IsWindowsVistaSP1OrGreater())
	{
		printf("Windows Vista\n");
	}

	if (IsWindowsVistaSP1OrGreater() && !IsWindowsVistaSP2OrGreater())
	{
		printf("Windows VistaSP1\n");
	}

	if (IsWindowsVistaSP2OrGreater() && !IsWindows7OrGreater())
	{
		printf("Windows VistaSP2\n");
	}

	if (IsWindows7OrGreater() && !IsWindows7SP1OrGreater())
	{
		printf("Windows 7\n");
	}

	if (IsWindows7SP1OrGreater() && !IsWindows8OrGreater())
	{
		printf("Windows 7SP1\n");
	}

	if (IsWindows8OrGreater() && !IsWindows8Point1OrGreater())
	{
		printf("Windows 8\n");
	}

	if (IsWindows8Point1OrGreater())
	{
		printf("Windows 8.x\n");
	}

	
}



void audit(){
	//getWindowsVersion();
}

int __cdecl wmain(__in int argc, __in_ecount(argc) PCWSTR argv[])
{
	getWindowsVersion(argc, argv);




}