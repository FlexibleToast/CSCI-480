#ifndef PROCESS_H
#define PROCESS_H
/*******************************************************************************
 * File:        Process.h
 * Programmer:  Joseph McDade
 * zID:         1757419
 * Due Date:    10/12/2018
 *
 * Purpose:     Header file for Process object class
 ******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <queue>

using namespace std;

struct event
{
	char Operation;
	int Value;
};

class Process
{
  public:
    Process();

    //Accessor Methods
		//Get Methods
		string getName() const { return(ProcessName); };
		int getPriority() const { return(Priority); };
		int getProcessID() const { return(ProcessID); };
		int getArrivalTime() const { return(ArrivalTime); };
		int getTimestamp() const { return(Timestamp); };
		int getValue() const { return(History[Sub].Value); };
		int getCPUTotal() const { return(CPUTotal); };
		int getCPUCount() const { return(CPUCount); };
		int getITotal() const { return(ITotal); };
		int getICount() const { return(ICount); };
		int getOTotal() const { return(OTotal); };
		int getOCount() const { return(OCount); };
		char getNextEvent();
		int getQueuetime() const { return(TotalQueuetime); };

		//Set Methods
		void importQueue(queue<string>&, pid_t);
		void setTimestamp(int newTimestamp){ Timestamp = newTimestamp; };
		int  iterateCPUTimer();
		void clearCPUTimer() { CPUTimer = 0; };
		int  iterateIOTimer();
		void clearIOTimer() { IOTimer = 0; };
		void incrementSub(){ Sub++; };
		void incrementICount() { ICount++; };
		void incrementITotal() { ITotal++; };
		void incrementOCount() { OCount++; };
		void incrementOTotal() { OTotal++; };
		void incrementCPUTotal(){ CPUTotal++; };
		void incrementCPUCount() { CPUCount++; };
		void addQueuetime(int);

    //Utility Methods

		//Operator Overload
		bool operator>(const Process&) const;
		bool operator<(const Process&) const;
		Process& operator=(const Process&);

  private:
		string ProcessName;	// Process name
		int Priority;				// Priority of the process
		int ProcessID;			// ID of the process
		int ArrivalTime;		// Which cycle the process is allowed to enter ready
												// queue if not at AT_ONCE
		event History[10];	// Operations to be performed
		int Sub;						// Current operation needed to be performed
		int CPUTimer;				// Counts clock ticks of current CPU burst
		int IOTimer;				// Counts clock ticks of current I/O burst
		int CPUTotal;				// Counts total CPU clocks
		int ITotal;					// Counts total clocks as IActive
		int OTotal;					// Counts total clocks as OActive
		int CPUCount;				// Counts number of times process needed CPU burst
		int ICount;					// Counts number of times needed Input burst
		int OCount;					// Counts number of times needed Output burst
		int Timestamp;			// Timestamp of TIMER when entered queue
		int TotalQueuetime;	// Total time spent in a queue other than entry
};

#endif
