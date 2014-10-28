/*
 ============================================================================
 Name        : KeepDifferentTimminAuditAndIsAlive.c
 Author      : Alberto.R.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Constants */
#define MAX_TEMP_STRING_CHECKIFALIVE 150

/* Variables */
/* time */
time_t lastTimeAudit;
time_t lastTimeIsAlive;

/* Check each 1 minute is alive */
void checkIsAliveTiming() {
	/* give the currently seconds */
	time_t sec = time(NULL );
	/* obtain the seconds spent */
	time_t countDownSeconds = sec - lastTimeIsAlive;
	long int intCountDownSeconds = (long int) countDownSeconds;
	long int stopCountDown = 60; // how much seconds we need to check (60sec)

	char tempMsg[MAX_TEMP_STRING_CHECKIFALIVE];

	/* send the event if each 1 minutes */
	if (intCountDownSeconds >= stopCountDown) {
		printf("The Agent is alive after %d\n", intCountDownSeconds);
		lastTimeIsAlive = time(NULL );

	}
}

/* Check each 2 minutes audit timing  */
void checkAuditTiming() {
	/* give the currently seconds */
	time_t sec = time(NULL );
	/* obtain the seconds spent */
	time_t countDownSeconds = sec - lastTimeAudit;
	long int intCountDownSeconds = (long int) countDownSeconds;
	long int stopCountDown = 120; // how much seconds we need to check (120sec)

	char tempMsg[MAX_TEMP_STRING_CHECKIFALIVE];

	/* send the event if each 2 minutes */
	if (intCountDownSeconds >= stopCountDown) {
		printf("Running audit function after %d\n", intCountDownSeconds);
		lastTimeAudit = time(NULL );

	}

}

int main(void) {
	puts("we are going to keep two different timing Audit and isAlive\n"); /* prints we going to switch off the Agent */
	/* Initialize isAlive and Audit timing */
	lastTimeAudit=time(NULL);
	lastTimeIsAlive=time(NULL);

	for (;;){
		checkIsAliveTiming();
		checkAuditTiming();
		sleep(1);
	}


	return EXIT_SUCCESS;
}
