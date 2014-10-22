/* libraries */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Constants */
#define MAXLENGHTLINE 200

/* Structures for storing the rules */
struct node_rule{
	char ruleName[MAXLENGHTLINE];
	int enabled; // enabled==1 means yes and enabled==0 means no
	int direction; // direction==1 means IN and direction==0 means OUT
	int publicP; // PublicP==1 means enabled and PublicP==0 means disabled
	int privateP; // PrivateP==1 means enabled and PrivateP==0 means disabled
	int domainP; // DomainP==1 means enabled and DomainP==0 means disabled
	char localIp[MAXLENGHTLINE];
	char remoteIP[MAXLENGHTLINE];
	char protocol[MAXLENGHTLINE];
	char localPort[MAXLENGHTLINE];
	int remotePort[MAXLENGHTLINE];
	int action; // action==1 means allow and action==0 means reject
	struct node_rule *next;
}*rules;

/* List Operations */
/* Append */
void append(char ruleToInsert[MAXLENGHTLINE],
	int enabledToInsert,
	int directionToInsert,
	int privateToInsert,
	int domainToInsert,
	int publicToInsert,
	char localIpToInsert[MAXLENGHTLINE],
	char remoteIPToInsert[MAXLENGHTLINE],
	char protocolToInsert[MAXLENGHTLINE],
	char localPortToInsert[MAXLENGHTLINE],
	char remotePortToInsert[MAXLENGHTLINE],
	int actionToInsert) {
	/* Allocate memory for the node */
	struct node_rule *right, *temp;

	temp = (struct node_rule *) malloc(sizeof(struct node_rule));
	/* Assign the specific information in fields */
	strcpy(temp->ruleName, ruleToInsert);
	temp->enabled = enabledToInsert;
	temp->direction = directionToInsert;
	temp->privateP = privateToInsert;
	temp->domainP = domainToInsert;
	temp->publicP = publicToInsert;
	strcpy(temp->localIp, localIpToInsert);
	strcpy(temp->remoteIP, remoteIPToInsert);
	strcpy(temp->protocol, protocolToInsert);
	strcpy(temp->localPort, localPortToInsert);
	strcpy(temp->remotePort, remotePortToInsert);
	temp->action = actionToInsert;

	right = (struct node_rule *) rules;
	while (right->next != NULL)
		right = right->next;
	right->next = temp;
	right = temp;
	right->next = NULL;

}

/* Add */
void add(char ruleToInsert[MAXLENGHTLINE],
	int enabledToInsert,
	int directionToInsert,
	int privateToInsert,
	int domainToInsert,
	int publicToInsert,
	char localIpToInsert[MAXLENGHTLINE],
	char remoteIPToInsert[MAXLENGHTLINE],
	char protocolToInsert[MAXLENGHTLINE],
	char localPortToInsert[MAXLENGHTLINE],
	char remotePortToInsert[MAXLENGHTLINE],
	int actionToInsert) {

	struct node_rule *temp;
	/* Allocate memory for the node */
	temp = (struct node_rule *) malloc(sizeof(struct node_rule));
	/* Assign the specific information in fields */
	strcpy(temp->ruleName, ruleToInsert);
	temp->enabled = enabledToInsert;
	temp->direction = directionToInsert;
	temp->privateP = privateToInsert;
	temp->domainP = domainToInsert;
	temp->publicP = publicToInsert;
	strcpy(temp->localIp, localIpToInsert);
	strcpy(temp->remoteIP, remoteIPToInsert);
	strcpy(temp->protocol, protocolToInsert);
	strcpy(temp->localPort, localPortToInsert);
	strcpy(temp->remotePort, remotePortToInsert);
	temp->action = actionToInsert;


	/* Add to rule list */
	if (rules == NULL) {
		rules = temp;
		rules->next = NULL;
	}
	else {
		temp->next = rules;
		rules = temp;
	}

}

/* add in a specific location */
void addafter(int loc, char ruleToInsert[MAXLENGHTLINE],
	int enabledToInsert,
	int directionToInsert,
	int privateToInsert,
	int domainToInsert,
	int publicToInsert,
	char localIpToInsert[MAXLENGHTLINE],
	char remoteIPToInsert[MAXLENGHTLINE],
	char protocolToInsert[MAXLENGHTLINE],
	char localPortToInsert[MAXLENGHTLINE],
	char remotePortToInsert[MAXLENGHTLINE],
	int actionToInsert) {
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
	strcpy(temp->ruleName, ruleToInsert);
	temp->enabled = enabledToInsert;
	temp->direction = directionToInsert;
	temp->privateP = privateToInsert;
	temp->domainP = domainToInsert;
	temp->publicP = publicToInsert;
	strcpy(temp->localIp, localIpToInsert);
	strcpy(temp->remoteIP, remoteIPToInsert);
	strcpy(temp->protocol, protocolToInsert);
	strcpy(temp->localPort, localPortToInsert);
	strcpy(temp->remotePort, remotePortToInsert);
	temp->action = actionToInsert;

	left->next = temp;
	left = temp;
	left->next = right;
	return;
}

/* Count element of the list */
int count() {
	struct node_rule *n;
	int c = 0;
	n = rules;
	while (n != NULL) {
		n = n->next;
		c++;
	}
	return c;
}

/* insert rule*/
void insertRule(
	char ruleNameTemp[MAXLENGHTLINE],
	int enabledTemp,
	int directionTemp,
	int publicPTemp,
	int privatePTemp,
	int domainPTemp,
	char localIpTemp[MAXLENGHTLINE],
	char remoteIPTemp[MAXLENGHTLINE],
	char protocolTemp[MAXLENGHTLINE],
	char localPortTemp[MAXLENGHTLINE],
	char remotePortTemp[MAXLENGHTLINE],
	int actionTemp) {
	int c = 0;
	struct node_rule *temp;

	/* Asign the rules list to temp */
	temp = rules;
	if (temp == NULL) {
		add(ruleNameTemp, enabledTemp, directionTemp, publicPTemp, privatePTemp, publicPTemp, domainPTemp, localIpTemp, remoteIPTemp, protocolTemp, localPortTemp, remotePortTemp);
	}
	else {
		c = count();
		if (c == 0)
			add(ruleNameTemp, enabledTemp, directionTemp, publicPTemp, privatePTemp, publicPTemp, domainPTemp, localIpTemp, remoteIPTemp, protocolTemp, localPortTemp, remotePortTemp); // insert at the beginning
		else if (c < count())
			addafter(++c, ruleNameTemp, enabledTemp, directionTemp, publicPTemp, privatePTemp, publicPTemp, domainPTemp, localIpTemp, remoteIPTemp, protocolTemp, localPortTemp, remotePortTemp); // insert after a number
		else {
			append(ruleNameTemp, enabledTemp, directionTemp, publicPTemp, privatePTemp, publicPTemp, domainPTemp, localIpTemp, remoteIPTemp, protocolTemp, localPortTemp, remotePortTemp); // insert at the end
		}
	}
}


/*Remove white space*/
char* trimwhitespace(char *str_base) {
	char* buffer = str_base;
	while ((buffer = strchr(str_base, ' '))) {
		strcpy(buffer, buffer + 1);
	}
	return str_base;
}

/* Remove NewLine */
char* removeNewLine(char *str_base){
	char *pos;
	if ((pos = strchr(str_base, '\n')) != NULL)
		*pos = '\0';
	return str_base;
}



void makeListWithFirewallRules(){
	char line[MAXLENGHTLINE];
	FILE *fp;
	/* Temp variables */
	char ruleNameTemp[MAXLENGHTLINE];
	int enabledTemp;
	int directionTemp;
	int publicPTemp = 0;
	int privatePTemp = 0;
	int domainPTemp = 0;
	char localIpTemp[MAXLENGHTLINE];
	char remoteIPTemp[MAXLENGHTLINE];
	char protocolTemp[MAXLENGHTLINE];
	char localPortTemp[MAXLENGHTLINE];
	char remotePortTemp[MAXLENGHTLINE];
	int actionTemp = 0;

	/* Command to obtain all the rules */
	fp = _popen("netsh advfirewall firewall show rule name=all", "r");
	/* Error open file*/
	if (fp == NULL){
		printf("Failed to run command\n");
	}
	char *token1;
	char *token2;
	/* Read output a line at a time -output it */
	while (fgets(line, sizeof line, fp) != NULL){
		token1 = strtok(line, " ");
		/* Get Rule Name */
		if (token1 != NULL){
			if (strcmp("Rule", token1) == 0){
				strcpy(ruleNameTemp, "");
				if (token1 != NULL){
					/* Increase pointer to avoid Name*/
					token1 = strtok(NULL, " ");
				}
				while (token1 != NULL){
					strcat(ruleNameTemp, token1);
					token1 = strtok(NULL, " ");
				}
				printf("Rule: %s\n", ruleNameTemp);
			}
		}
		/* Store if the rule is enabled or not */
		if (token1 != NULL){
			if (strcmp("Enabled:", token1) == 0){
				/*Increase pointer to get value */
				token1 = strtok(NULL, " ");
				if (strcmp("Yes", token1)){
					enabledTemp = 1;
				}
				if (strcmp("No", token1)){
					enabledTemp = 0;
				}
				printf("Enabled: %s\n", token1);
			}
		}
		/* Get the rule direction*/
		if (token1 != NULL){
			if (strcmp("Direction:", token1) == 0){
				/* Increase pointer to get value */
				token1 = strtok(NULL, " ");
				if (strcmp("In", token1) == 0){
					directionTemp = 1;
				}
				if (strcmp("Out", token1) == 0){
					directionTemp = 0;
				}
				printf("Direction: %s\n", token1);
			}
		}
		/* Get profiles configuration */
		if (token1 != NULL){
			if (strcmp("Profiles:", token1) == 0){
				/* Increase pointer to get value */
				token1 = strtok(NULL, ",");
				/* Remove whites spaces from string */
				token1 = trimwhitespace(token1);
				while (token1 != NULL){
					/* Get Domain profile */
					if (strcmp("Domain", token1) == 0){
						domainPTemp = 1;
					}
					/* Get Private profile */
					if (strcmp("Private", token1) == 0){
						privatePTemp = 1;
					}
					/* Get Public profile */
					if (strcmp("Public", token1) == 0){
						publicPTemp = 1;
					}
					token1 = strtok(NULL, ",");
					/* Remove newline from string */
					if (token1 != NULL){
						token1 = removeNewLine(token1);
					}
				}
				printf("Profiles: %d %d %d\n", domainPTemp, privatePTemp, publicPTemp);
			}
		}
		/* Get localIP */
		if (token1 != NULL){
			if (strcmp("LocalIP:", token1) == 0){
				/*Increase the pointer to get value of localIP */
				token1 = strtok(NULL, " ");
				strcpy(localIpTemp, token1);
				printf("Local IP: %s\n", localIpTemp);
			}
		}
		/* Get remoteIp */
		if (token1 != NULL){
			if (strcmp("RemoteIP:", token1) == 0){
				/*Increase the pointer to get value of remoteIP */
				token1 = strtok(NULL, " ");
				strcpy(remoteIPTemp, token1);
				printf("Remote IP: %s\n", remoteIPTemp);
			}
		}
		/* Get protocol */
		if (token1 != NULL){
			if (strcmp("Protocol:", token1) == 0){
				/*Increase the pointer to get value of protocol */
				token1 = strtok(NULL, " ");
				strcpy(protocolTemp, token1);
				printf("Protocol: %s\n", protocolTemp);
			}
		}
		/* Get localPort */
		if (token1 != NULL){
			if (strcmp("LocalPort:", token1) == 0){
				/*Increase the pointer to get value of local port */
				token1 = strtok(NULL, " ");
				strcpy(localPortTemp, token1);
				printf("LocalPort: %s\n", localPortTemp);
			}
		}
		/* Get remotePort */
		if (token1 != NULL){
			if (strcmp("Remote port:", token1) == 0){
				/*Increase the pointer to get value of remote port */
				token1 = strtok(NULL, " ");
				strcpy(remotePortTemp, token1);
				printf("RemotePort: %s\n", remotePortTemp);
			}
		}
		/* Get action */
		if (token1 != NULL){
			if (strcmp("Action:", token1) == 0){
				/*Increase the pointer to get value of action */
				token1 = strtok(NULL, " ");
				/* Remove newline from string */
				token1 = removeNewLine(token1);
				if (token1 != NULL){
					if (strcmp("Allow", token1) == 0){
						actionTemp = 1;
					}
					if (strcmp("Block", token1) == 0){
						actionTemp = 0;
					}
				}
				printf("Action: %d\n\n", actionTemp);
				/* Insert rule in the list */
				insertRule(ruleNameTemp, enabledTemp, directionTemp, publicPTemp, privatePTemp, domainPTemp, localIpTemp, remoteIPTemp, protocolTemp, localPortTemp, remotePortTemp, actionTemp);
			}
		}

	}
}


main()
{
	printf("We going to parsing firewall rules \n");
	makeListWithFirewallRules();
}