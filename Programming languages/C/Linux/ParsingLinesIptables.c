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

/* List Operations */
/* Append */
void append(char ruleNameToInsert[MAXLENGHTLINE],
		int directionToInsert, // direction==1 is IN and direction==0 is OUT
		char ipSourceToInsert[MAXLENGHTLINE],
		char ipDestinationToInsert[MAXLENGHTLINE], int actionToInsert,
		char freeTextRuleToInsert[MAXLENGHTLINE],
		char protocolToInsert[MAXLENGHTLINE]) {

	/* Allocate memory for the node */
	struct node_rule *right, *temp;
	temp = (struct node_rule *) malloc(sizeof(struct node_rule));
	/* Assign the specific information in fields */
	strcpy(temp->ruleName, ruleNameToInsert);
	temp->direction = directionToInsert;
	strcpy(temp->ipSource, ipSourceToInsert);
	strcpy(temp->ipDestination, ipDestinationToInsert);
	temp->action = actionToInsert;
	strcpy(temp->freeTextRule, freeTextRuleToInsert);
	strcpy(temp->protocol, protocolToInsert);

	right = (struct node_rule *) rules;
	while (right->next != NULL )
		right = right->next;
	right->next = temp;
	right = temp;
	right->next = NULL;

}

/* Add */
void add(char ruleNameToInsert[MAXLENGHTLINE],
		int directionToInsert, // direction==1 is IN and direction==0 is OUT
		char ipSourceToInsert[MAXLENGHTLINE],
		char ipDestinationToInsert[MAXLENGHTLINE], int actionToInsert,
		char freeTextRuleToInsert[MAXLENGHTLINE],
		char protocolToInsert[MAXLENGHTLINE]) {

	/* Create a node to fill it with the temporal information */
	struct node_rule *temp;
	/* Allocate memory for the node */
	temp = (struct node_rule *) malloc(sizeof(struct node_rule));
	/* Assign the specific information in fields */
	strcpy(temp->ruleName, ruleNameToInsert);
	temp->direction = directionToInsert;
	strcpy(temp->ipSource, ipSourceToInsert);
	strcpy(temp->ipDestination, ipDestinationToInsert);
	temp->action = actionToInsert;
	strcpy(temp->freeTextRule, freeTextRuleToInsert);
	strcpy(temp->protocol, protocolToInsert);

	/* Add to rule list */
	if (rules == NULL ) {
		rules = temp;
		rules->next = NULL;
	} else {
		temp->next = rules;
		rules = temp;
	}

}

/* Add in a specific location */
void addAfter(int loc, char ruleNameToInsert[MAXLENGHTLINE],
		int directionToInsert, // direction==1 is IN and direction==0 is OUT
		char ipSourceToInsert[MAXLENGHTLINE],
		char ipDestinationToInsert[MAXLENGHTLINE], int actionToInsert,
		char freeTextRuleToInsert[MAXLENGHTLINE],
		char protocolToInsert[MAXLENGHTLINE]) {

	int i;
	struct node_rule *left, *right, *temp;
	left = NULL;

	/* Addafter in main list */
	right = rules;

	for (i = 1; i < loc; i++) {
		left = right;
		right = right->next;
	}
	/* Allocate memory for the node */
	temp = (struct node_rule *) malloc(sizeof(struct node_rule));

	/* Assign the specific information in fields */
	strcpy(temp->ruleName, ruleNameToInsert);
	temp->direction = directionToInsert;
	strcpy(temp->ipSource, ipSourceToInsert);
	strcpy(temp->ipDestination, ipDestinationToInsert);
	temp->action = actionToInsert;
	strcpy(temp->freeTextRule, freeTextRuleToInsert);
	strcpy(temp->protocol, protocolToInsert);

	left->next = temp;
	left = temp;
	left->next = right;
}

/* Count element of the list */
int count() {
	struct node_rule *n;
	int c = 0;
	n = rules;
	while (n != NULL ) {
		n = n->next;
		c++;
	}
	return c;
}

/* Insert rule */
void insertRule(char ruleNameTemp[MAXLENGHTLINE],
		int directionTemp, // direction==1 is IN and direction==0 is OUT
		char ipSourceTemp[MAXLENGHTLINE], char ipDestinationTemp[MAXLENGHTLINE],
		int actionToInsert, char freeTextRuleTemp[MAXLENGHTLINE],
		char protocolTemp[MAXLENGHTLINE]) {

	int c = 0;
	struct node_rule *temp;

	/* Asign the rules list to temp */
	temp = rules;
	if (temp == NULL ) {
		add(ruleNameTemp,
				directionTemp, // direction==1 is IN and direction==0 is OUT
				ipSourceTemp, ipDestinationTemp, actionToInsert,
				freeTextRuleTemp, protocolTemp);
	} else {
		c = count();
		if (c == 0)
			add(ruleNameTemp,
					directionTemp, // direction==1 is IN and direction==0 is OUT
					ipSourceTemp, ipDestinationTemp, actionToInsert,
					freeTextRuleTemp, protocolTemp); // insert at the beginning
		else if (c < count())
			addAfter(++c, ruleNameTemp,
					directionTemp, // direction==1 is IN and direction==0 is OUT
					ipSourceTemp, ipDestinationTemp, actionToInsert,
					freeTextRuleTemp, protocolTemp); // insert after a number
		else {
			append(ruleNameTemp,
					directionTemp, // direction==1 is IN and direction==0 is OUT
					ipSourceTemp, ipDestinationTemp, actionToInsert,
					freeTextRuleTemp, protocolTemp); // insert at the end
		}
	}
}

/* Display list of rules */
void displayListOfRules() {

	struct node_rule *r;
	r = rules;
	if (r == NULL ) {
		printf("The list of rules is empty\n");
	} else {
		printf("List of Rules\n");
		while (r != NULL ) {
			printf("------------------------------\n");
			printf("Rule name: %s\n", r->ruleName);
			printf("Direction: %d\n", r->direction);
			printf("Local IP: %s\n", r->ipSource);
			printf("Remote IP: %s\n", r->ipDestination);
			printf("Action: %d\n", r->action);
			printf("Protocol: %s\n", r->protocol);
			printf("Settings configured %s\n", r->freeTextRule);
			/*Pointing to the next rule in the list*/
			r = r->next;
		}
	}

}

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
	int counter = 0;
	//printf("List of Input rules\n");
	/* Read output from the command running */
	while (fgets(line, sizeof line, fp) != NULL ) {

		/* Get rule name*/
		sprintf(ruleNameTemp, "Rule-Input-%d", counter);
		//printf("Rule name: %s\n", ruleNameTemp);

		/* Adding INPUT direction value */
		directionTemp = 1;
		//printf("Direction: %d\n", directionTemp);

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
		//printf("Action %d\n", actionTemp);

		/* Go to the protocol value */
		token1 = strtok(NULL, " ");
		/* Get protocol value */
		strcpy(protocolTemp, token1);
		//printf("Protocol: %s\n", protocolTemp);

		/* Go to ipSource value */
		token1 = strtok(NULL, " ");
		token1 = strtok(NULL, " ");
		token1 = strtok(NULL, " ");
		token1 = strtok(NULL, " ");
		/* Get ipSource value */
		strcpy(ipSourceTemp, token1);
		//printf("IP Source: %s\n", ipSourceTemp);

		/* Go to ipDestination value*/
		token1 = strtok(NULL, " ");
		/* Get ipDestination */
		strcpy(ipDestinationTemp, token1);
		//printf("IP Destination: %s\n", ipDestinationTemp);

		/* Go to free text value */
		token1 = strtok(NULL, " ");
		/* Get free text value */
		strcpy(freeTextRuleTemp, "");
		while (token1 != NULL ) {
			strcat(freeTextRuleTemp, token1);
			strcat(freeTextRuleTemp, " ");
			token1 = strtok(NULL, " ");
		}
		/* Insert rule into the */
		insertRule(ruleNameTemp,
				directionTemp, // direction==1 is IN and direction==0 is OUT
				ipSourceTemp, ipDestinationTemp, actionTemp, freeTextRuleTemp,
				protocolTemp);
		//printf("Free text value: %s\n", freeTextRuleTemp);
		counter++;
	}

}

/* Get output rules from iptables command */
void getOutputRules() {

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
	fp = popen("iptables -L OUTPUT -n -v | tail -n +3", "r");
	/* Error run command */
	if (fp == NULL ) {
		printf("Failed o run command\n");
	}
	char * token1;
	int counter = 0;
	//printf("List of Output rules\n");
	/* Read output from the command running */
	while (fgets(line, sizeof line, fp) != NULL ) {

		/* Get rule name*/
		sprintf(ruleNameTemp, "Rule-Output-%d", counter);
		//printf("Rule name: %s\n", ruleNameTemp);

		/* Adding INPUT direction value */
		directionTemp = 1;
		//printf("Direction: %d\n", directionTemp);

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
		//printf("Action %d\n", actionTemp);

		/* Go to the protocol value */
		token1 = strtok(NULL, " ");
		/* Get protocol value */
		strcpy(protocolTemp, token1);
		//printf("Protocol: %s\n", protocolTemp);

		/* Go to ipSource value */
		token1 = strtok(NULL, " ");
		token1 = strtok(NULL, " ");
		token1 = strtok(NULL, " ");
		token1 = strtok(NULL, " ");
		/* Get ipSource value */
		strcpy(ipSourceTemp, token1);
		//printf("IP Source: %s\n", ipSourceTemp);

		/* Go to ipDestination value*/
		token1 = strtok(NULL, " ");
		/* Get ipDestination */
		strcpy(ipDestinationTemp, token1);
		//printf("IP Destination: %s\n", ipDestinationTemp);

		/* Go to free text value */
		token1 = strtok(NULL, " ");
		/* Get free text value */
		strcpy(freeTextRuleTemp, "");
		while (token1 != NULL ) {
			strcat(freeTextRuleTemp, token1);
			strcat(freeTextRuleTemp, " ");
			token1 = strtok(NULL, " ");
		}
		/* Insert rule into the */
		insertRule(ruleNameTemp,
				directionTemp, // direction==1 is IN and direction==0 is OUT
				ipSourceTemp, ipDestinationTemp, actionTemp, freeTextRuleTemp,
				protocolTemp);
		//printf("Free text value: %s\n", freeTextRuleTemp);
		counter++;
	}

}

void makeListWithFirewallRules() {
	getInputRules();
	getOutputRules();

}

int main(void) {
	printf("we going to parsing rules from Iptables\n"); /* prints we going to switch off the Agent */
	makeListWithFirewallRules();
	displayListOfRules();
	return EXIT_SUCCESS;
}
