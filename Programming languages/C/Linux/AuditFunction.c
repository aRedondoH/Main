/*
 ============================================================================
 Name        : AuditFunction.c
 Author      : Alberto.R.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int audit() {
	FILE *fp;
	char osIdentityOutput[300];
	char portsOutput[1000];
	/* OS identity and version */

	/* Read /proc/version */
	fp = popen("cat /proc/version | cut -d ' ' -f 1,2,3,8,9", "r");
	if (fp == NULL ) {
		printf("Failed to run command\n");
		return 1;
	}

	/* Read the output a line at a time - output it. */
	while (fgets(osIdentityOutput, sizeof(osIdentityOutput) - 1, fp) != NULL ) {
		printf("OS identity: %s", osIdentityOutput);
	}

	/* Get open ports */
	/* Read /proc/version */
	fp = popen("sudo iptables -nL | grep \"ACCEPT \" | grep dpt | cut -d':' -f 2 | sort -u", "r");
	if (fp == NULL ) {
		printf("Failed to run command\n");
		return 1;
	}
	/* Read the output a line at a time - output it. */
	while (fgets(portsOutput, sizeof(portsOutput) - 1, fp) != NULL ) {
		printf("Port opened %s", portsOutput);
	}

	/* close */
	pclose(fp);

	return 0;

}

int main(void) {
	printf("we are goint to audit things\n"); /* prints we are goint to audit things */
	//system("cat /proc/version | cut -d ' ' -f 1,2,3,8,9");
	int ret = audit();
	if (ret != 0) {
		printf("Something goes wrong\n");
	}
	return EXIT_SUCCESS;
}
