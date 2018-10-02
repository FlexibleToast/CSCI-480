#ifndef PROCESS_H
#define PROCESS_H
/*******************************************************************************
 * Programmer:  Joseph McDade
 * zID:         1757419
 * Due Date:    10/12/2018
 *
 * Purpose:     Header file for process object
 ******************************************************************************/
#include <stdio.h>

typedef struct{
char Operation;
int value;
} event;

struct process{
	char *ProcessName;
	unsigned Priority;
	pid_t ProcessID;
	int ArrivalTime;
	event History[10];
	int Sub;
	int CPUTimer;
	int IOTimer;
	int CPUTotal;
	int ITotal;
	int OTotal;
	int CPUCount;
	int ICount;
	int OCount;
};

#endif
