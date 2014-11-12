/*
 ============================================================================
 Name        : ChechTotalPercentageMemoryUsage.c
 Author      : Alberto.R.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define MAXLENGHTLINE 200

/* Global variables*/
int percentageMemoryUsage=0;

/* Check the percentage of total memory usage */
void checkTotalPercentageMemoryUsage(){
	char line[MAXLENGHTLINE];
	FILE *fp;

	/* Command to obtain the percentage of total memory usage */
	fp = popen("free | grep Mem | awk '{print $3/$2 * 100.0}'", "r");
	/* Error run command */
	if (fp == NULL){
		printf("Failed to run command\n");
	}

	/* Read output from command running*/
	while(fgets(line,sizeof line, fp)!=NULL){
		percentageMemoryUsage=atoi(line);
	}
	printf("Total percentage memory usage: %d%%\n", percentageMemoryUsage);
}

int main(void) {
	printf("we going to check the total percentage memory usage\n");
	checkTotalPercentageMemoryUsage();
	return EXIT_SUCCESS;
}
