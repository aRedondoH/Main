/*
 ============================================================================
 Name        : TestDetectFirewall.c
 Author      : Alberto R
 Version     :
 Copyright   : Your copyright notice
 Description : Test if Firewall is on/off
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int read_int(const char* tempFile) {

	// Open file
	FILE* file = fopen(tempFile, "ab+");
	// Give file permissions
	system("chmod 700 temp");
	int i = 0;
	// Read int from file
	fscanf(file, "%d", &i);
	// Close file
	fclose(file);
	// Remove temp file
	system("rm temp");

	return i;
}

void firewall_is_connected_method_1() {

	// Make command for Counting lines from drop ports in iptables
	const char * cmd = "iptables -L -n | wc -l > temp";

	// Run command
	system(cmd);
	const char* temp = "temp";
	int lines = read_int(temp);

	// Check if the Firewall is enabled/disabled
	if (lines == 8) {
		printf("Firewall is disabled\n");
	} else {
		printf("Firewall is enabled\n");
	}
}

void method_2(){
	  FILE *fp;
	  int status;
	  char path[1035];

	  /* Open the command for reading. */
	  fp = popen("iptables -L -n | wc -l", "r");
	  if (fp == NULL) {
	    printf("Failed to run command\n" );
	    exit;
	  }

	  int lines = 0;
	  while (!feof (fp))
	     {
	       fscanf (fp, "%d", &lines);
	     }
	  // Check if the Firewall is enabled/disabled
	  	if (lines == 8) {
	  		printf("Firewall is disabled\n");
	  	} else {
	  		printf("Firewall is enabled\n");
	  	}

	  /* close */
	  pclose(fp);
}

int main(void) {
	printf("we are going to check if the firewall is switch on/off: \n");
	// Check if the firewall is on/off
	for (;;){
		//firewall_is_connected_method_1();
		method_2();
		sleep(1);
	}
}
