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
#include <string.h>

/* Remove blanks from strings */
char* deblank(char* input) {
	int i, j;
	char *output = input;
	for (i = 0, j = 0; i < strlen(input); i++, j++) {
		if (input[i] != ' ')
			output[j] = input[i];
		else
			j--;
	}
	output[j] = 0;
	return output;
}

/* Parsing the processes lines */
void parsingLine(char line[200]) {

	char* stringToCut;

	// Parsing processes thats begin with '['
	if (line[1] == '[') {
		line[1] = ' ';
		stringToCut = strtok(line, "]");
		stringToCut = deblank(stringToCut);
		printf("%s\n", stringToCut);
	} else if (line[1] == '/') { // Parsing processes thats begin with '/'
		char *processToPrint;
		stringToCut = strtok(line, "/");
		while (stringToCut != NULL ) {
			processToPrint = stringToCut;
			stringToCut = strtok(NULL, "/");
		}
		printf("%s", processToPrint);
	} else {
		// if the process does not need to parsing do nothing
		printf("%s", deblank(line));
	}

}

void listEveryProcessRunning() {
	char line[200];

	FILE *fp;
	fp =
			popen(
					"ps aux | awk '{printf $11 \" \\n \"}' | uniq -u | head -n -7 | tail -n +2",
					"r");

	/* Error open file */
	if (fp == NULL ) {
		printf("Failed to run command\n");
	}

	/* Read the output a line at a time -output it. */
	while (fgets(line, sizeof line, fp) != NULL ) {
		parsingLine(line);
	}

	/* Close */
	pclose(fp);
}

int main(void) {
	printf("we going to check all the processes running in the machine:\n");
	listEveryProcessRunning();
	return EXIT_SUCCESS;
}
