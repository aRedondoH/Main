/*
 * CheckDiskUsageMain.c
 *
 *  Created on: Mar 24, 2015
 *      Author: secnok
 */

#include <stdio.h>
#include <stdlib.h>

void checkDiskUsage() {
	FILE *fp;
	int diskUsage;
	char line[100];
	char command[100];

	// Command to get percentage disk usage
	sprintf(command, "df -hT /home | tail -n +2 | awk '{printf \" %%s \",$6}' ");

	fp = popen(command, "r");
	/* Error run command */
	if (fp == NULL ) {
		printf("Failed to run command to get disk usage \n");
	} else {
		/* Read output from command running*/
		while (fgets(line, sizeof line, fp) != NULL ) {
			diskUsage = atoi(line);
		}
	}
	/* close file */
	fclose(fp);
	printf("%d\n", diskUsage);
}

int main(int argc, char *argv[]) {

	checkDiskUsage();

	return 0;

}

