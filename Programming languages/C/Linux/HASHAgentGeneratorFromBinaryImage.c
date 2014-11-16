/*
 * main.c
 *
 *  Created on: Sep 2, 2014
 *      Author: secnok
 */

#include <stdio.h>
#include <openssl/md5.h>
#include "polarssl/md5.h"

#define MIN_FILE_READ 1
#define MAX_FILE_READ 1024
#define MD5_DIGEST_LENGTH 16

/* Constants for readArgumentsFromConfigFile */
#define MAX_BUFFER_READ_ARGUMENTS 50
#define MAX_BUFFER_READ_ARGUMENTS_OF_PROCESSES 2000
#define MAX_STRING 1000
#define MIN_ID 1
#define MAX_ID 100
#define MIN_THRESHOLD 0
#define MAX_THRESHOLD 100

/* Global variables */
int my_id = 1;
char * detector_ip;
char * flagUsbDevices;
char * flagPs2SerialDevices;
char *agentHASH;
unsigned char agentHASHv2[MD5_DIGEST_LENGTH];
long double threshold;
int memoryThreshold;
int cpuAgentToSwitchOff;
long double lengthCircularBuffer;
long double auditFunctionTime;
int isAliveFunctionTime;
char *arrayOfProcesses[30];
int numberOfProcesses;

/* Get arguments from the config file */
int readArgumentsFromConfigFile() {
	FILE * cF;
	char bufr[MAX_BUFFER_READ_ARGUMENTS];
	char bufrProcesses[MAX_BUFFER_READ_ARGUMENTS_OF_PROCESSES];
	char processes[MAX_STRING];

	printf("-------------------------------------\n");
	printf("-------SNOK Agent Configuration------\n");
	printf("-------------------------------------\n");
	/* open the file */
	cF = fopen("config.txt", "r");
	if (cF != NULL ) {
		/* get Agent id */
		fgets(bufr, MAX_STRING, cF);
		sscanf(bufr + 8, "%d", &my_id);
		printf("Agent id is %d\n", my_id);

		/* get ip_detector */
		detector_ip = (char *) malloc(15);
		fgets(bufr, MAX_STRING, cF);
		sscanf(bufr + 11, "%s", detector_ip);
		printf("Ip detector is %s\n", detector_ip);

		/* get cpuThresold */
		fgets(bufr, MAX_STRING, cF);
		double cpuT; // receive double
		sscanf(bufr + 13, "%lf", &cpuT);
		threshold = cpuT; // double to long double
		printf("Cpu thresold is %2.Lf\n", threshold);

		/* get memoryThresold */
		fgets(bufr, MAX_STRING, cF);
		int memoryT; // receive double
		sscanf(bufr + 16, "%d", &memoryT);
		memoryThreshold = memoryT;
		printf("Memory threshold is %d\n", memoryThreshold);

		/* get cpuAgentToSwitchOff */
		fgets(bufr, MAX_STRING, cF);
		int cpuSwitchOffT;
		sscanf(bufr + 20, "%d", &cpuSwitchOffT);
		cpuAgentToSwitchOff = cpuSwitchOffT;
		printf("Cpu Agent to switch off: %d\n", cpuAgentToSwitchOff);

		/* get flag usb devices */
		flagUsbDevices = (char *) malloc(3);
		fgets(bufr, MAX_STRING, cF);
		sscanf(bufr + 11, "%s", flagUsbDevices);
		printf("Detection usb devices: %s\n", flagUsbDevices);

		/* get flag ps2/serial devices */
		flagPs2SerialDevices = (char *) malloc(3);
		fgets(bufr, MAX_STRING, cF);
		sscanf(bufr + 17, "%s", flagPs2SerialDevices);
		printf("Detection ps2/serial devices: %s\n", flagPs2SerialDevices);

		/* get length circular buffer */
		fgets(bufr, MAX_STRING, cF);
		double circularL; // receive double
		sscanf(bufr + 21, "%lf", &circularL);
		lengthCircularBuffer = circularL;
		printf("Length circular buffer is %2.Lf\n", lengthCircularBuffer);

		/* get time audit function */
		fgets(bufr, MAX_STRING, cF);
		double auditFunctionT; // receive double
		sscanf(bufr + 18, "%lf", &auditFunctionT);
		auditFunctionTime = auditFunctionT;
		printf("Audit function time is %2.Lf\n", auditFunctionTime);

		/* get time alive function */
		fgets(bufr, MAX_STRING, cF);
		int isAliveFunctionT;
		sscanf(bufr + 20, "%d", &isAliveFunctionT);
		isAliveFunctionTime = isAliveFunctionT;
		printf("isAlive function time is %d\n", isAliveFunctionTime);

		/* get Agent HASH */
		agentHASH = (char *) malloc(40);
		fgets(bufr, MAX_STRING, cF);
		sscanf(bufr + 10, "%s", agentHASH);
		printf("The Agent HASH is %s\n", agentHASH);
		fflush(stdout);

		/* get processes */
		fgets(bufrProcesses, MAX_BUFFER_READ_ARGUMENTS_OF_PROCESSES, cF);
		strcpy(processes, bufrProcesses + 15);

		// Remove '\n' from processes
		char *newline = strchr(processes, '\n');
		if (newline) {
			*newline = 0;
		}

		char *token1 = NULL;

		token1 = strtok(processes, " ");
		int i = 0;

		/* obtain the processes from the string and assign to array of strings */
		while (token1 != NULL ) {

			// Memory allocation for each process
			arrayOfProcesses[i] = malloc(strlen(token1) + 1);

			strcpy(arrayOfProcesses[i], token1);
			if (token1 != NULL ) {
				token1 = strtok(NULL, " ");
				i++;
			}

		}
		numberOfProcesses = i;
		printf("The number of processes is %d\n", numberOfProcesses);
		/* print the list of processes */
		printf("List of processes: ");
		for (i = 0; i < numberOfProcesses; i++) {
			printf("%s ", arrayOfProcesses[i]);
		//	insertIntoCriticalList(get_process_id_by_name(arrayOfProcesses[i]),
				//	arrayOfProcesses[i]);
		}
		printf("\n");

	} else {
		printf("Error open config file\n ");
	}
	/* if my_id or threshold is incorrect the program will stop */
	if ((my_id < MIN_ID || my_id > MAX_ID)
			|| (threshold < MIN_THRESHOLD || threshold > MAX_THRESHOLD)) {
		printf("Any argument is incorrect, please insert the correct values\n");
		return 1;
	}
	return 0;

}

/* Generate HASH of a binary file with OpenSSL */
int generateHASHwithOpenSSL() {

	unsigned char c[MD5_DIGEST_LENGTH];
	char *filename = "test1.txt";
	int i;
	MD5_CTX mdContext;
	int bytes;
	unsigned char data[MAX_FILE_READ];

	printf("Generating HASH...\n");

	/* Open file */
	FILE *inFile = fopen(filename, "rb");

	/* Check if the file has opened correctly */
	if (inFile == NULL ) {
		printf("%s can't be opened.\n", filename);
		return 0;
	}

	/* Initialize MD5 */
	MD5_Init(&mdContext);

	/* Update MD5 */
	while ((bytes = fread(data, MIN_FILE_READ, MAX_FILE_READ, inFile)) != 0)
		MD5_Update(&mdContext, data, bytes);

	/* Final conversion */
	MD5_Final(c, &mdContext);

	/* Print HASH and filename */
	printf("HASH with OpenSSL: ");
	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
		printf("%02x", c[i]);
	printf(" %s\n", filename);

	/* Close file */
	fclose(inFile);
	return 0;

}

/* Convert char to unsigned char */
int convertZeroPadedHexIntoByte(char *dataset,unsigned char *bytearray){
	int i = strlen(dataset),j=0,counter=0;
	char c[2];
	unsigned int bytes[2];

	for(j=0;j<i;j++){
		if(0 == j%2){

			c[0] = dataset[j];
			c[1] = dataset[j+1];

			sscanf(c, "%02x", &bytes[0]);

			bytearray[counter] = bytes[0];

			counter++;
		}
	}
	return 0;
}

/* Comparing two unsigned char */
int compareTwoHASH (unsigned char * a, unsigned char * b){
	int i;

		    for(i=0;i<MD5_DIGEST_LENGTH;i++)
		    if(a[i]!=b[i])
		        return 1;

		    return 0;
}

/* HASH verification
 * return 0 if HASH verification is right
 * return 1 if HASH verification is wrong */
int verificationHASH(unsigned char c[MD5_DIGEST_LENGTH]){

	unsigned char temp[MD5_DIGEST_LENGTH];
	convertZeroPadedHexIntoByte(agentHASH,temp);
	/*printf("Comparing: ");
	int i;
	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
			printf("%02x", c[i]);

	printf(" With:  ");
	int p;
	for (p = 0; p < MD5_DIGEST_LENGTH; p++)
			printf("%02x", temp[p]);
	printf("\n");*/
	if (compareTwoHASH(c,temp)==0){
		printf("HASH verification is right\n");
		return 0;
	}else{
		printf("HASH verification is wrong\n");
		return 1;
	}

}

/* Generate HASH of a binary file with PolarSSL */
int generateAndCheckHASHwithPolarSSL() {

	unsigned char c[MD5_DIGEST_LENGTH];
	char *filename = "SNOK-Agent-1.2";
	int i;

	md5_file(filename, c);
	/* Print HASH and filename */
	printf("HASH with PolarSSL: ");
	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
		printf("%02x", c[i]);
	printf(" %s\n", filename);

	verificationHASH(c);

	return 0;
}

int main() {
	printf("We are going to test HASH functions \n");
	//int ret1 = generateHASHwithOpenSSL();
	//if (ret1 == 0) {
		//printf("HASH generated correctly with OpenSSL \n");
	//}
	readArgumentsFromConfigFile();

	int ret2 = generateAndCheckHASHwithPolarSSL();
	if (ret2 == 0) {
		printf("HASH generated correctly with PolarSSL \n");
	}

	return 0;
}
