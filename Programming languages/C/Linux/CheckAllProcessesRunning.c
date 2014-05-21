/*
 ============================================================================
 Name        : CheckAllProcessesRunning.c
 Author      : Alberto.R.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void listEveryProcessRunning() {
	char line[200];
	static const char filename[]= "temp.txt";

	/* Get list the processes running */
		system("ps aux | awk '{printf $11 \" \\n \"}' | uniq -u | head -n -7 | tail -n +2 > temp.txt");

	FILE *fp=fopen(filename, "r");
	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		printf("Process running: %s\n", line);
	}

	/* Close */
	pclose(fp);

	/* Remove file*/
	int status = remove(filename);
	if (status == 0){
		printf("File %s deleted successfully.\n", filename);
	}else{
		printf("Unable to delete the file\n");
	}
}

int main(void) {
	puts("we going to check all the processes running in the machine:\n ");
	listEveryProcessRunning();
	return EXIT_SUCCESS;
}
