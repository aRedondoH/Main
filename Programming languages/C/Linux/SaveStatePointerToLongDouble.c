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

void second(int** loadv2){
	**loadv2=**loadv2+30;

}
void is_cpu_state_change(int* previous_load){

	printf("The last cpu load inside the function %d\n", *previous_load);
	*previous_load=*previous_load+50;
	second(&previous_load);
	printf("Should be work: %d\n", *previous_load);
}


int main(void) {
	puts("\n");
	int p=50;
	printf("The last cpu load first %d\n", p);
	is_cpu_state_change((int*)&p);
	printf("The last cpu load was %d\n", p);

	int* paco=malloc(sizeof(p));
	*paco=p;
	*paco=*paco+30;
	printf("Paco is incremented in 30: %d\n", *paco);
	getchar();
	return EXIT_SUCCESS;
}
