/*
 ============================================================================
 Name        : SaveStatePointerToLongDouble.c
 Author      : Alberto.R.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


void is_cpu_state_change(int *previous_load){

	printf("The last cpu load inside the function %d\n", *previous_load);
	*previous_load=*previous_load+20;
}

void checkInitialState(int previous_load){

	is_cpu_state_change(&previous_load);
}

int main(void) {
	puts("we going to check saving state of pointer to long double");
	int* p = 50;
	//p = (long double*)malloc(sizeof(long double));
	printf("The last cpu load first %d\n", p);
	//checkInitialState(&p);
	is_cpu_state_change(&p);

	printf("The last cpu load was %d\n", p);
	getchar();
	return EXIT_SUCCESS;
}
