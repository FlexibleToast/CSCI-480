#ifndef PROCESS_H
#define PROCESS_H
/**********************************************************************************
 * File:        Process.h
 * Programmer:  Joseph McDade
 * zID:         1757419
 * Due Date:    10/12/2018
 *
 * Purpose:     Header file for Process object class
 *********************************************************************************/
#include <iostream>
#include <stdlib.h>

using namespace std;

class Process
{
  public:
    Process();
    ~Process();

    //Accessor Methods

    //Utility Methods
      void    clear()  { vecSize = 0; };

  private:
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
