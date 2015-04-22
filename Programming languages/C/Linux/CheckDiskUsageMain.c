/*
 * CheckDiskUsageMain.c
 *
 *  Created on: Mar 24, 2015
 *      Author: secnok
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int hardDiskPercentageWarning = 3;
int oldDiskUsage;
int currentDiskUsage;

/* Set the disk usage at the beginning */
void setDiskUsageAtTheBeginning() {
	FILE *fp;
	char line[100];
	char command[100];

	// Command to get percentage disk usage
	sprintf(command,
			"df -hT /home | tail -n +2 | awk '{printf \" %%s \",$6}' ");

	fp = popen(command, "r");
	/* Error run command */
	if (fp == NULL ) {
		printf("Failed to run command to get disk usage \n");
	} else {
		/* Read output from command running*/
		while (fgets(line, sizeof line, fp) != NULL ) {
			oldDiskUsage = atoi(line);
		}
	}
	/* close file */
	fclose(fp);
	printf("The percentage of disk usage is: %d%%\n", oldDiskUsage);

}

/* Get current disk usage */
void getCurrentDiskUsage() {
	FILE *fp;
	char line[100];
	char command[100];

	// Command to get percentage disk usage
	sprintf(command,
			"df -hT /home | tail -n +2 | awk '{printf \" %%s \",$6}' ");

	fp = popen(command, "r");
	/* Error run command */
	if (fp == NULL ) {
		printf("Failed to run command to get disk usage \n");
	} else {
		/* Read output from command running*/
		while (fgets(line, sizeof line, fp) != NULL ) {
			currentDiskUsage = atoi(line);
		}
	}
	/* close file */
	fclose(fp);
	//printf("The percentage of disk usage is: %d%%\n", diskUsage);

}

/* check disk usage status */
void checkDiskUsageStatus() {

	getCurrentDiskUsage();

	printf("Comparing old: %d with current: %d\n", oldDiskUsage,
			currentDiskUsage);

	if (currentDiskUsage != oldDiskUsage) {
		if ((currentDiskUsage - oldDiskUsage) == hardDiskPercentageWarning) {
			printf("The hard disk increase %d%%\n", hardDiskPercentageWarning);
			printf("The current hard disk usage is %d%%\n", currentDiskUsage);
			// Update old disk usage
			oldDiskUsage = currentDiskUsage;
		}

		if ((oldDiskUsage - currentDiskUsage) == hardDiskPercentageWarning) {
			printf("The hard disk decrease %d%%\n", hardDiskPercentageWarning);
			printf("The current hard disk usage is %d%%\n", currentDiskUsage);
			// Update old disk usage
			oldDiskUsage = currentDiskUsage;
		}

	}

}

int main(int argc, char *argv[]) {

	// Get the disk usage percentage of the machine at the beginning
	setDiskUsageAtTheBeginning();

	for (;;) {
		checkDiskUsageStatus();
		sleep(1);
	}
	return 0;

}

