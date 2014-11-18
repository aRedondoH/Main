
#include <stdio.h>
#include <stdlib.h>
//#include <openssl/md5.h>
#include "polarssl/md5.h"

#define MIN_FILE_READ 1
#define MAX_FILE_READ 1024
#define MD5_DIGEST_LENGTH 16

/* Constants definition */
#define MAX_NUMBER_CRITICAL_PROCESSES 200
#define MAX_LENGTH_MSG_CHECKINITIALSTATE 150
// Constants definition on readArgumentsFromConfigFile
#define MAX_LENGTH_NORMAL_BUFFER 50
#define MAX_LENGTH_BUFFER_OF_PROCESSES 2000
#define MAX_LENGHT_STRING_PROCESSES 1000
#define MAX_LENGHT_COMMON_STRING 1000
#define MAX_CPU_THRESHOLD 100
#define MIN_CPU_THRESHOLD 0
#define MAX_ID 1000
#define MIN_ID 1
#define MAX_LENGTH_MSG_CHECKISALIVE 150

/* Global variables */
int my_id = 1;
char *detector_ip;
char * flagUsbDevices;
char * flagPs2SerialDevices;
char * agentHASH;
int cpuThreshold;
int memThreshold;
int cpuAgentToSwitchOff;
long double lengthCircularBuffer;
long double auditFunctionTime;
int isAliveFunctionTime;
char *arrayOfProcesses[MAX_NUMBER_CRITICAL_PROCESSES]; // Array of critical processes 
int flagCpuGratefulFallbackMode = 0; // if flagCpuGratefulFallbackMode=0 is off and if flagCpuGratefulFallbackMode=1 is on
int flagMemGratefulFallbackMode = 0; // if flagMemGratefulFallbackMode=0 is off and if flagMemGratefulFallbackMode=1 is on

int numberOfProcesses;



/* Get arguments from the config file */
int readArgumentsFromConfigFile(){

	FILE * cF;
	char bufr[MAX_LENGTH_NORMAL_BUFFER];
	char bufrProcesses[MAX_LENGTH_BUFFER_OF_PROCESSES];
	errno_t err;
	char processes[MAX_LENGHT_STRING_PROCESSES];
	int memoryT; // receive double

	/* open the file */
	err = fopen_s(&cF, "config.txt", "r");
	if (err == 0){
		/* get my_id */
		fgets(bufr, MAX_LENGHT_COMMON_STRING, cF);
		sscanf_s(bufr + 8, "%d", &my_id);
		printf("Agent id is %d\n", my_id);

		/* get ip_detector */
		detector_ip = (char *)malloc(15);
		fgets(bufr, MAX_LENGHT_COMMON_STRING, cF);
		sscanf(bufr + 11, "%s", detector_ip); // with sscanf_s this line crash in Debug mode
		printf("Ip detector is %s\n", detector_ip);

		/* get cpuThresold */
		fgets(bufr, MAX_LENGHT_COMMON_STRING, cF);
		sscanf_s(bufr + 13, "%d", &cpuThreshold);
		printf("Cpu thresold is %d\n", cpuThreshold);

		/* get memoryThresold */
		fgets(bufr, MAX_LENGHT_COMMON_STRING, cF);
		sscanf(bufr + 16, "%d", &memoryT);
		memThreshold = memoryT;
		printf("Memory threshold is %d\n", memThreshold);

		/* get cpuAgentToSwitchOff */
		fgets(bufr, MAX_LENGHT_COMMON_STRING, cF);
		int cpuSwitchOffT;
		sscanf(bufr + 20, "%d", &cpuSwitchOffT);
		cpuAgentToSwitchOff = cpuSwitchOffT;
		printf("Cpu Agent to switch off: %d\n", cpuAgentToSwitchOff);

		/* get flag usb devices */
		flagUsbDevices = (char *)malloc(3);
		fgets(bufr, MAX_LENGHT_COMMON_STRING, cF);
		sscanf(bufr + 11, "%s", flagUsbDevices);
		printf("Detection usb devices: %s\n", flagUsbDevices);

		/* get flag ps2/serial devices */
		flagPs2SerialDevices = (char *)malloc(3);
		fgets(bufr, MAX_LENGHT_COMMON_STRING, cF);
		sscanf(bufr + 17, "%s", flagPs2SerialDevices);
		printf("Detection ps2/serial devices: %s\n", flagPs2SerialDevices);

		/* get length circular buffer */
		fgets(bufr, MAX_LENGHT_COMMON_STRING, cF);
		double circularL; // receive double
		sscanf(bufr + 21, "%lf", &circularL);
		lengthCircularBuffer = circularL;
		printf("Length circular buffer is %2.Lf\n", lengthCircularBuffer);

		/* get time audit function */
		fgets(bufr, MAX_LENGHT_COMMON_STRING, cF);
		double auditFunctionT; // receive double
		sscanf(bufr + 18, "%lf", &auditFunctionT);
		auditFunctionTime = auditFunctionT;
		printf("Audit function time is %2.Lf\n", auditFunctionTime);

		/* get time alive function */
		fgets(bufr, MAX_LENGHT_COMMON_STRING, cF);
		int isAliveFunctionT;
		sscanf(bufr + 20, "%d", &isAliveFunctionT);
		isAliveFunctionTime = isAliveFunctionT;
		printf("isAlive function time is %d\n", isAliveFunctionTime);

		/* get Agent HASH */
		agentHASH = (char *)malloc(40);
		fgets(bufr, MAX_LENGHT_COMMON_STRING, cF);
		sscanf(bufr + 10, "%s", agentHASH);
		printf("The Agent HASH is %s\n", agentHASH);
		fflush(stdout);

		/* get processes */
		fgets(bufrProcesses, MAX_LENGTH_BUFFER_OF_PROCESSES, cF);
		strcpy(processes, bufrProcesses + 16); // with strcpy_s this line crash in Debug mode

		char *token1 = NULL;
		char *nextToken = NULL;
		token1 = strtok_s(processes, " ", &nextToken);
		int i = 0;

		/* obtain the processes from the string and assign to array of strings */
		while (token1 != NULL){
			// Memory allocation for each process
			arrayOfProcesses[i] = (char *)malloc(strlen(token1) + 1);
			strcpy(arrayOfProcesses[i], token1);

			if (token1 != NULL){
				token1 = strtok_s(NULL, " ", &nextToken);
				i++;
			}
		}
		numberOfProcesses = i;
		printf("The number of processes is %d\n", numberOfProcesses);

		/* print the list of processes */
		printf("List of processes: ");
		for (i = 0; i < numberOfProcesses; i++){
			if (arrayOfProcesses[i] != NULL){
				printf("%s ", arrayOfProcesses[i]);

			}
		}
		printf("\n");
	}
	else{
		printf("Error open config file\n ");
	}
	/* if my_id or threshold is incorrect the program will stop */
	if ((my_id < MIN_ID || my_id>MAX_ID) || (cpuThreshold < MIN_CPU_THRESHOLD || cpuThreshold>MAX_CPU_THRESHOLD)){
		printf("Any argument is incorrect, please insert the correct values\n");
		return 1;
	}

	return 0;
}

/* Convert char to unsigned char */
int convertZeroPadedHexIntoByte(char *dataset, unsigned char *bytearray){
	int i = strlen(dataset), j = 0, counter = 0;
	char c[2];
	unsigned int bytes[2];

	for (j = 0; j<i; j++){
		if (0 == j % 2){

			c[0] = dataset[j];
			c[1] = dataset[j + 1];

			sscanf(c, "%02x", &bytes[0]);

			bytearray[counter] = bytes[0];

			counter++;
		}
	}
	return 0;
}

/* Comparing two unsigned char */
int compareTwoHASH(unsigned char * a, unsigned char * b){
	int i;

	for (i = 0; i<MD5_DIGEST_LENGTH; i++)
		if (a[i] != b[i])
			return 1;

	return 0;
}

/* HASH verification
* return 0 if HASH verification is right
* return 1 if HASH verification is wrong */
int verificationHASH(unsigned char c[MD5_DIGEST_LENGTH]){

	unsigned char temp[MD5_DIGEST_LENGTH];
	convertZeroPadedHexIntoByte(agentHASH, temp);
	printf("Comparing: ");
	int i;
	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
	printf("%02x", c[i]);

	printf(" With:  ");
	int p;
	for (p = 0; p < MD5_DIGEST_LENGTH; p++)
	printf("%02x", temp[p]);
	printf("\n");
	if (compareTwoHASH(c, temp) == 0){
		printf("HASH verification is right\n");
		return 0;
	}
	else{
		printf("HASH verification is wrong\n");
		return 1;
	}

}

/* Generate HASH of a binary file with PolarSSL */
int generateAndCheckHASHwithPolarSSL() {

	unsigned char c[MD5_DIGEST_LENGTH];
	char *filename = "HASHVerification.exe";
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

