/*
 * firewall.c
 *
 *  Created on: May 27, 2014
 *      Author: secnok
 */

#include "firewall.h"
#include "snok_agent.h"


/* --------------------------------------------*/
/* ----------- FIREWALL FUNCTIONS -------------*/
/* --------------------------------------------*/
/* Check if firewall is enabled/disabled */
void is_firewall_enabled(int checkState) {
	FILE *fp;

	/* Open the command for reading. */
	fp = popen("iptables -L -n | wc -l", "r");
	if (fp == NULL ) {
		printf("Failed to run command\n");
		//exit;
	}

	/* Read the file information */
	int lines = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d", &lines);
	}

	// Check if the Firewall is enabled/disabled
	if (lines == 8) {
		currentlyFirewallStatus = 0;
	} else {
		currentlyFirewallStatus = 1;
	}

	// if the state is different or we don't want to check the state
	if ((currentlyFirewallStatus != lastFirewallStatus) || (checkState == 0)) {
		if (currentlyFirewallStatus == 0) {
			transferEvent(my_id, FIREWALL_OFF, "Firewall is disabled\n");
			printf("Firewall is disabled\n");
		} else {
			transferEvent(my_id, FIREWALL_ON, "Firewall is enabled\n");
			printf("Firewall is enabled\n");
		}
		lastFirewallStatus = currentlyFirewallStatus;
	}

	/* close */
	pclose(fp);
}
