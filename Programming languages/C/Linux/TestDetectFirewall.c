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


int read_int(const char* tempFile){
	// Open file
	FILE* file = fopen(tempFile, "r");
	int i=0;
	// Read int from file
	fscanf (file, "%d", &i);
	// Close file
	fclose(file);
	return i;
}

void firewall_is_connected(){

	// Make command for Counting lines from drop ports in iptables
	const char * cmd = "sudo iptables -L -n | wc -l > temp";
	// Run command
	system(cmd);
	const char* temp="temp";
	int lines = read_int(temp);

	// Check if the Firewall is enabled/disabled
	if (lines==8){
		printf("Firewall is disabled\n");
	}else{
		printf("Firewall is enabled\n");
	}
}

int main(void) {
	printf("we are going to check if the firewall is switch on/off: \n");
	// Check if the firewall is on/off
	firewall_is_connected();
	// Remove temp file
	system("rm temp");
}
