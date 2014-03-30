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

void chr_fw(){
	// Make command for obtaining LOG_FILTER from iptables
	const char * cmd = "sudo iptables -L -n | grep -e dpt | grep DROP";
	// Run command in shell
	system(cmd);
}

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
	const char * cmd = "sudo iptables -L -n | grep -A 18 \"Chain INPUT\" | wc -l > temp";
	// Run command
	system(cmd);
	const char* temp="temp";
	int lines = read_int(temp);
	// Check if there are some ports drop
	if (lines==19){
		printf("Firewall is enabled\n");
	}else{
		if (lines==8){
			printf("Firewall is disabled\n");
		}
	}
}

int main(void) {
	printf("we are going to check if the firewall is switch on/off\n");
	// Show LOG_FILTER from iptables
	chr_fw();
	// Check if the firewall is on/off
	firewall_is_connected();
	// Remove temp file
	system("rm temp");
}
