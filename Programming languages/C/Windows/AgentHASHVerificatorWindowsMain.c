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


/* Generate HASH of a binary file with PolarSSL */
int generateAndCheckHASHwithPolarSSL(char *arguments[]) {

	unsigned char c[MD5_DIGEST_LENGTH];
	//char *filename = "HASHVerification.exe";
	int i;

	md5_file(arguments[1], c);
	/* Print HASH and filename */
	printf("HASH with PolarSSL: ");
	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
		printf("%02x", c[i]);
	printf(" %s\n", arguments[1]);

	return 0;
}

int main(int argc, char *argv[]) {
	printf("Creating HASH for this Agent...\n");
	
	int ret2 = generateAndCheckHASHwithPolarSSL(argv);
	if (ret2 == 0) {
		printf("HASH generated correctly with PolarSSL \n");
	}

	return 0;
}