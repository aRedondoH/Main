/*
 ============================================================================
 Name        : ParsingLinesIptables.c
 Author      : Alberto.R.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants */
#define MAXLENGHTLINE 200

/* Record to save the rules*/
struct node_rule {
	char ruleName[MAXLENGHTLINE];
	int direction; // direction==1 is IN and direction==0 is OUT
	char ipSource[MAXLENGHTLINE];
	char ipDestination[MAXLENGHTLINE];
	int action;
	char freeTextRule[MAXLENGHTLINE];
	char protocol[MAXLENGHTLINE];
	struct node_rule *next;
}*rules;

/* Variables */
int counter=0;

void getInputRules() {

	char line[MAXLENGHTLINE];
	FILE *fp;

	/* Temp variables */
	char ruleNameTemp[MAXLENGHTLINE];
	int directionTemp; // direction==1 is IN and direction==0 is OUT
	char ipSourceTemp[MAXLENGHTLINE];
	char ipDestinationTemp[MAXLENGHTLINE];
	int actionTemp;
	char freeTextRuleTemp[MAXLENGHTLINE];
	char protocolTemp[MAXLENGHTLINE];

	/* Command to obtain all the rules */
	fp = popen("iptables -L INPUT -n -v | tail -n +3", "r");
	/* Error run command */
	if (fp == NULL ) {
		printf("Failed o run command\n");
	}
	char * token1;

	/* Read output from the command running */
	while (fgets(line, sizeof line, fp) != NULL ) {

		/* Get rule name*/
		sprintf(ruleNameTemp, "Rule-%d",counter);
		printf("Rule name: %s\n",ruleNameTemp);

		/* Adding INPUT direction value */
		directionTemp=1;
		printf("Direction: %d\n",directionTemp);

		token1 = strtok(line, " ");
		/* Go to the next value*/
		token1 = strtok(NULL, " ");

		/* Go to the Action value*/
		token1 = strtok(NULL, " ");
		/* Get Action*/
		if (strcmp("ACCEPT", token1) == 0) {
			actionTemp = 1;
		}
		if (strcmp("DROP", token1) == 0) {
			actionTemp = 0;
		}
		printf("Action %d\n", actionTemp);

		/* Go to the protocol value */
		token1 = strtok(NULL, " ");
		/* Get protocol value */
		strcpy(protocolTemp, token1);
		printf("Protocol: %s\n", protocolTemp);

		/* Go to ipSource value */
		token1 = strtok(NULL, " ");
		token1 = strtok(NULL, " ");
		token1 = strtok(NULL, " ");
		token1 = strtok(NULL, " ");
		/* Get ipSource value */
		strcpy(ipSourceTemp, token1);
		printf("IP Source: %s\n", ipSourceTemp);

		/* Go to ipDestination value*/
		token1 = strtok(NULL, " ");
		/* Get ipDestination */
		strcpy(ipDestinationTemp, token1);
		printf("IP Destination: %s\n", ipDestinationTemp);

		/* Go to free text value */
		token1 = strtok(NULL, " ");
		/* Get free text value */
		strcpy(freeTextRuleTemp, "");
		while (token1 != NULL ) {
			strcat(freeTextRuleTemp, token1);
			strcat(freeTextRuleTemp, " ");
			token1 = strtok(NULL, " ");
		}
		printf("Free text value: %s\n", freeTextRuleTemp);
		counter++;
	}

}

void makeListWithFirewallRules() {
	getInputRules();

}

int main(void) {
	printf("we going to parsing rules from Iptables\n"); /* prints we going to switch off the Agent */
	//makeListWithFirewallRules();
	getInputRules();
	return EXIT_SUCCESS;
}
