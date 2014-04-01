#include "TCHAR.h"
#include "pdh.h"
#include <stdio.h>


static PDH_HQUERY cpuQuery;
static PDH_HCOUNTER cpuTotal;


void init(){
	PdhOpenQuery(NULL, NULL, &cpuQuery);
	PdhAddCounter(cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
	PdhCollectQueryData(cpuQuery);
}


double getCurrentValue(){
	PDH_FMT_COUNTERVALUE counterVal;


	PdhCollectQueryData(cpuQuery);
	PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
	return counterVal.doubleValue;
}

int main(){

	init();
	for (;;){
		int CPUusage = getCurrentValue();
		printf("The CPU usage is: %d\n", CPUusage);
		Sleep(1500);
	}
	getchar();


	return 0;
}