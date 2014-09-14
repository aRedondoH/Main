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
//#define MD5_DIGEST_LENGTH 16

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

/* Generate HASH of a binary file with PolarSSL */
int generateHASHwithPolarSSL() {

	unsigned char c[MD5_DIGEST_LENGTH];
	char *filename = "SNOK-Agent-1.2";
	int i;

	md5_file(filename, c);
	/* Print HASH and filename */
	printf("HASH with PolarSSL: ");
	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
		printf("%02x", c[i]);
	printf(" %s\n", filename);

	return 0;
}

int main() {
	printf("We are going to test HASH functions \n");
	int ret1 = generateHASHwithOpenSSL();
	if (ret1 == 0) {
		printf("HASH generated correctly with OpenSSL \n");
	}
	int ret2 = generateHASHwithPolarSSL();
	if (ret2 == 0) {
		printf("HASH generated correctly with PolarSSL \n");
	}

	return 0;
}
