/*******************************************************************************
 * File:        Process.h
 * Programmer:  Joseph McDade
 * zID:         1757419
 * Due Date:    10/12/2018
 *
 * Purpose:     Class definitions for the Process object class
 ******************************************************************************/

#include "Process.h"

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  Constructors  /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 * Default Constructor
 * Arguments: none
 * Notes:     Builds the processes
 ******************************************************************************/
Process::Process()
{
	string ProcessName = "NULL";
	unsigned Priority = 0;
	pid_t ProcessID = 0;
	int ArrivalTime = 0;
	event History[10];
	int Sub = 0;
	int CPUTimer = 0;
	int IOTimer = 0;
	int CPUTotal = 0;
	int ITotal = 0;
	int OTotal = 0;
	int CPUCount = 0;
	int ICount = 0;
	int OCount = 0;
}

unsigned Process::getPriority() const{
	return(Priority);
}
void Process::setPriority(unsigned newPriority){
	Priority = newPriority;
}
bool Process::operator>(const Process& rhs) const{
	return(this->Priority > rhs.getPriority());
}
bool Process::operator<(const Process& rhs) const{
	return(this->Priority < rhs.getPriority());
}


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////Operator Overloads///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
