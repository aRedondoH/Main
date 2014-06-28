/*
 * cpu.c
 *
 *  Created on: May 27, 2014
 *      Author: secnok
 */

#include "cpu.h"
#include "snok_agent.h"

/* --------------------------------------------*/
/* -------------- CPU FUNCTIONS ---------------*/
/* --------------------------------------------*/
/* Get the current CPU load */
long double calculateCpuLoad() {
	long double a[4], b[4], average_load;
	FILE *fp;

	fp = fopen("/proc/stat", "r");
	fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &a[0], &a[1], &a[2], &a[3]);
	fclose(fp);

	/* Wait one second between two samples */
	fflush(stdout);
	sleep(1);

	fp = fopen("/proc/stat", "r");
	fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &b[0], &b[1], &b[2], &b[3]);
	fclose(fp);

	/* Calculate average load from two samples */
	/* Times 100 for percentage */
	average_load = 100 * ((b[0] + b[1] + b[2]) - (a[0] + a[1] + a[2]))
			/ ((b[0] + b[1] + b[2] + b[3]) - (a[0] + a[1] + a[2] + a[3]));

	return average_load;
}

/* Return 1 if CPU state changes, 0 otherwise */
void checkCpuUsage(int checkstate) {

	char temp_string[200];
	long double newCPUload;

	/* Get CPU threshold */
	newCPUload = calculateCpuLoad();

	/* currentlyCPUstate=1 if CPU_excess and
	currentlyCPUstate=0 if CPU_normal*/
	if (newCPUload>threshold){
		currentlyCPUstate=1;
	}else{
		currentlyCPUstate=0;
	}

	/* if the CPU state change, it sends an event */
	if ((lastCPUstate != currentlyCPUstate)||(checkstate==0)){
		// if the new_average_load is higher than normal threshold, it sends an event
		if (newCPUload >= threshold) {
				/* Event detail information */
				snprintf(temp_string, 200,
						"CPU: %.2Lf%% is on excess usage > %.2Lf%%\n",
						newCPUload, threshold);
				transferEvent(my_id, CPU_EXCESS, temp_string);
				printf("CPU: %.2Lf%% is on excess usage > %.2Lf%%\n",
						newCPUload, threshold);
			}
		// if the new_average_load is lower than normal threshold, it sends an event
		if (newCPUload < threshold) {
			/* Event detail information */
			snprintf(temp_string, 200,
					"CPU: %.2Lf%% is on normal usage < %.2Lf%%\n",
					newCPUload, threshold);
			transferEvent(my_id, CPU_NORMAL, temp_string);
			printf("CPU: %.2Lf%% is on normal usage < %.2Lf%%\n",
					newCPUload, threshold);
		}
	}
	/* Update new load for the next calculation */
	lastCPUstate = currentlyCPUstate;
}
