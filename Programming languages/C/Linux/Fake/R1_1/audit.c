/*
 * audit.c
 *
 *  Created on: May 27, 2014
 *      Author: secnok
 */

#include "audit.h"
#include "snok_agent.h"


/* --------------------------------------------*/
/* -------------- AUDIT FUNCTIONS -------------*/
/* --------------------------------------------*/
/* Get general audit*/
int audit(int previous_running_state[]) {
	FILE *fp;
	char osIdentityOutput[300];
	char portsOutput[1000];

	printf("\n");
	printf("********************************************\n");
	printf("----- General audit from SNOK Agent id %d ---\n", my_id);
	printf("\n");
	fflush(stdout);
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
		transferEvent(my_id, OS_IDENTITY, osIdentityOutput);
	}

	/* Check Firewall status */
	is_firewall_enabled(0);

	/* Get open ports */
	/* Read /proc/version */
	fp =
			popen(
					"iptables -nL | grep \"ACCEPT \" | grep dpt | cut -d':' -f 2 | sort -u| grep -o '[0-9]*' ",
					"r");
	if (fp == NULL ) {
		printf("Failed to run command\n");
		return 1;
	}
	/* Read the output a line at a time - output it. */
	while (fgets(portsOutput, sizeof(portsOutput) - 1, fp) != NULL ) {
		printf("Port open: %s", portsOutput);
		transferEvent(my_id, PORT_OPEN, portsOutput);
	}

	/* Check all the processes running */
	listEveryProcessRunning();
	printf("********************************************\n");
	printf("\n");
	fflush(stdout);
	/* close */
	pclose(fp);

	return 0;

}
