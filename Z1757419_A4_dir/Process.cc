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
	ProcessName = "NULL";
	Priority = 0;
	ProcessID = 0;
	ArrivalTime = 0;
	Sub = 0;
	CPUTimer = 0;
	IOTimer = 0;
	CPUTotal = 0;
	ITotal = 0;
	OTotal = 0;
	CPUCount = 0;
	ICount = 0;
	OCount = 0;
	Timestamp = 0;
}

void Process::setPriority(int newPriority){
	Priority = newPriority;
}

void Process::setTimestamp(int newTimestamp){
	Timestamp = newTimestamp;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////Operator Overloads///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool Process::operator>(const Process& rhs) const{
	if(this->Priority == rhs.getPriority())
		return(this->Timestamp < rhs.getTimestamp());
	return(this->Priority > rhs.getPriority());
}
bool Process::operator<(const Process& rhs) const{
	if(this->Priority == rhs.getPriority())
		return(this->Timestamp > rhs.getTimestamp());
	return(this->Priority < rhs.getPriority());
}
