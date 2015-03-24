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

	// Execute a process listing

	//sprintf(command, "df -hT /home | tail -n +2 | awk '{ printf \"%-10s\n\", $6}' | cut -d \" % \" -f 1");
	sprintf(command, "df -hT /home | tail -n +2");

	fp = popen(command, "r");
	/* Error run command */
	if (fp == NULL ) {
		printf("Failed to run command to get disk usage \n");
	} else {
		/* Read output from command running*/
		while (fgets(line, sizeof line, fp) != NULL ) {
			diskUsage = atoi(line);
			printf("%s\n", line);
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

