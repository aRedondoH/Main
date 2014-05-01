#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE * cF;
char bufr[50];
char bufrProcesses[2000];
int my_id;
char *ipServer[50];
int ip_detector;
int cpuThreshold;
char processes[1000];
char *listOfProcesses[25];

main()
{
	errno_t err;
	printf("we goint to read the arguments from a config file\n");
	err = fopen_s(&cF, "config.txt", "r");
	if (err == 0){
		/* get my_id */
		fgets(bufr, 1000, cF);
		sscanf_s(bufr+8, "%d", &my_id);
		printf("Agent id is %d\n", my_id);
		
		/* get ip_detector */
		fgets(bufr, 1000, cF);
		sscanf_s(bufr+11, "%s", ipServer, _countof(ipServer));		
		printf("Ip detector is %s\n", ipServer);

		/* get cpuThresold */
		fgets(bufr, 1000, cF);
		sscanf_s(bufr + 12, "%d", &ip_detector);
		printf("Cpu thresold is %d\n", ip_detector);

		/* get processes */
		fgets(bufrProcesses, 2000, cF);
		strcpy_s(processes, 1000, bufrProcesses+16);
		
		char *token1 = NULL;
		char *nextToken = NULL;
		token1 = strtok_s(processes, " ", &nextToken);
		int i = 0;
		/* obtain the processes from the string and assign to array of strings */
		while (token1!=NULL){
			listOfProcesses[i] = token1;
			if (token1 != NULL){
				token1 = strtok_s(NULL, " ", &nextToken);
				i++;
			}
		}
		/* print the list of processes */
		printf("List of processes: ");
		for (i = 0; i < 25; i++){
			if (listOfProcesses[i] != NULL){
				printf("%s ", listOfProcesses[i]);
			}
		}
	}
	else{
		printf("Error open config file\n ");
	}

}