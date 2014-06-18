/*
 * cpu.h
 *
 *  Created on: May 27, 2014
 *      Author: secnok
 */

#ifndef CPU_H_
#define CPU_H_



/* CPU FUNCTIONS HEADERS */
/* Get the current CPU load */
long double calculateCpuLoad();
/* Check CPU state */
void checkCpuUsage(int checkstate); // if checkstate=0 the function doesn't take into account the last state
									// if checkstate=1 the function take into account the last state


#endif /* CPU_H_ */
