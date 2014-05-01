#include<stdio.h>
#include<time.h>
#include<Windows.h>


clock_t lastTime;
void countDownMethodV1(){
	
	clock_t currentlyTime = clock();
	int stopCountDown = 10; // seconds stop Count Down
	clock_t secondsSpent = (currentlyTime - lastTime)/1000;
	int intCurrentlyTime = (int)currentlyTime;
	int intLastTime = (int)lastTime;

	printf("Seconds spent %d\n", (int)secondsSpent);
	if (secondsSpent >= stopCountDown){
		printf("10 seconds left\n");
		lastTime = currentlyTime;
	}
	
}

main()
{

	lastTime = clock();
	printf("we going to make a countDown\n");
	for (;;){
		countDownMethodV1();
		Sleep(1000);
	}

}