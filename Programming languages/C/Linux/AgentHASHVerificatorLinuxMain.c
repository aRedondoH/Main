/*
 * AgentHASHVerificatorLinuxMain.c
 *
 *  Created on: Nov 18, 2014
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

/* Generate HASH of a binary file with PolarSSL
 * * return 0 if HASH verification is right
 * return 1 if HASH verification is wrong */
int generateAndCheckHASHwithPolarSSL(char * arguments[]) {

	unsigned char c[MD5_DIGEST_LENGTH];
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
	printf("Creating HASH for specific Agent... \n");

	int ret2 = generateAndCheckHASHwithPolarSSL(argv);
	if (ret2 == 0) {
		printf("HASH generated correctly with PolarSSL \n");
	}

	return 0;
}

