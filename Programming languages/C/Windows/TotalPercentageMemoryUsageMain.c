/* MEM includes */
#include<windows.h>
#include<stdio.h>   
//#include<tchar.h>

// Use to convert bytes to MB
#define DIV 1048576
#define WIDTH 7

void getPorcentageMemoryInUse(){
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);

	//_tprintf(TEXT("There is  %*ld percent of memory in use.\n"), WIDTH, statex.dwMemoryLoad);
	int paco = statex.dwMemoryLoad;
	printf("There is %d%% percent of memory in use.\n", paco);
	/*_tprintf(TEXT("There are %*I64d total Mbytes of physical memory.\n"), WIDTH, statex.ullTotalPhys / DIV);
	_tprintf(TEXT("There are %*I64d free Mbytes of physical memory.\n"), WIDTH, statex.ullAvailPhys / DIV);
	_tprintf(TEXT("There are %*I64d total Mbytes of paging file.\n"), WIDTH, statex.ullTotalPageFile / DIV);
	_tprintf(TEXT("There are %*I64d free Mbytes of paging file.\n"), WIDTH, statex.ullAvailPageFile / DIV);
	_tprintf(TEXT("There are %*I64d total Mbytes of virtual memory.\n"), WIDTH, statex.ullTotalVirtual / DIV);
	_tprintf(TEXT("There are %*I64d free Mbytes of virtual memory.\n"), WIDTH, statex.ullAvailVirtual / DIV);
	_tprintf(TEXT("There are %*I64d free Mbytes of extended memory.\n"), WIDTH, statex.ullAvailExtendedVirtual / DIV);*/

}


int main(){

	printf("In the Pinocho's house only they count to eight\n");
	getPorcentageMemoryInUse();

	return 0;
}