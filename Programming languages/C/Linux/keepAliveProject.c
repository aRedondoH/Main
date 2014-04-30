/*
 ============================================================================
 Name        : keepAliveProject.c
 Author      : Alberto.R.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

time_t lastTime;
time_t sec;
time_t countDownSeconds;
time_t stopCountDown;
void methodV1(){
	unsigned int x_hours = 0;
		unsigned int x_minutes = 0;
		unsigned int x_seconds = 0;
		unsigned int x_milliseconds = 0;
		unsigned int totaltime = 0, count_down_time_in_secs = 0, time_left = 0;

		clock_t x_startTime, x_countTime;
		count_down_time_in_secs = 10;  // 1 minute is 60, 1 hour is 3600

		x_startTime = clock();  // start clock
		time_left = count_down_time_in_secs - x_seconds;   // update timer

		while (time_left > 0) {
			x_countTime = clock(); // update timer difference
			x_milliseconds = x_countTime - x_startTime;
			x_seconds = (x_milliseconds / (CLOCKS_PER_SEC)) - (x_minutes * 60);
			x_minutes = (x_milliseconds / (CLOCKS_PER_SEC)) / 60;
			x_hours = x_minutes / 60;

			time_left = count_down_time_in_secs - x_seconds; // subtract to get difference

			printf("\rYou have %d seconds left ( %d ) count down timer by TopCoder",
					time_left, count_down_time_in_secs);
		}

		printf("\n\n\nTime's out\n\n\n");

}


void methodV2(){
	    sec = time (NULL);
	    countDownSeconds = sec - lastTime;
	    stopCountDown = 60;
	    if (countDownSeconds == stopCountDown){
	    	printf("1 minute left");
	    }
	    printf ("Seconds:  %ld \n", countDownSeconds);

}



int main(void) {
	puts("We are going to make a keep alive function "); /* prints We are going to make a keep alive function  */
	lastTime = time(NULL);
	for(;;){
		methodV2();

	}
	return 0;
}
