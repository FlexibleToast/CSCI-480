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
////////////////////////////////  Constructors  ////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Get Methods /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 * Method:
 * Arguments:
 *
 * Returns:
 * Notes:
 ******************************************************************************/
 char Process::getNextEvent(){
	 Sub++;
	 return(History[Sub].Operation);
 }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Set Methods /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 * Method:		void Process::importQueue(queue<string> &inputQueue, pid_t newPID)
 * Arguments: &inputQueue - A queue of strings read from a file that contains
 *													values for the initialization of the process
 *						newPID - The PID of the new process
 * Returns:   none
 * Notes:     Changes a process to have values passed as a queue
 ******************************************************************************/
void Process::importQueue(queue<string> &inputQueue, pid_t newPID){
	ProcessID = newPID;
	ProcessName = inputQueue.front();
	inputQueue.pop();
	Priority = stoi(inputQueue.front());
	inputQueue.pop();
	ArrivalTime = stoi(inputQueue.front());
	inputQueue.pop();
	for(int i = 0; i < 10; i++)
	{
		History[i].Operation = inputQueue.front().c_str()[0];
		inputQueue.pop();
		History[i].Value = stoi(inputQueue.front());
		inputQueue.pop();
	}
	while(!inputQueue.empty())
	{	// Empty the inputQueue
		inputQueue.pop();
	}
}
/*******************************************************************************
 * Method:		int Process::iterateCPUTimer()
 * Arguments: none
 * Returns:   Current number of CPU cycles
 * Notes:			Used to iterate the time in CPU and compare to cycles needed
 ******************************************************************************/
 int Process::iterateCPUTimer(){
	 CPUTimer++;
	 return(CPUTimer);
 }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// Operator Overloads //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool Process::operator>(const Process& rhs) const{
	if(this->Priority == rhs.Priority)
		return(this->Timestamp < rhs.Timestamp);
	return(this->Priority > rhs.Priority);
}
bool Process::operator<(const Process& rhs) const{
	if(this->Priority == rhs.Priority)
		return(this->Timestamp > rhs.Timestamp);
	return(this->Priority < rhs.Priority);
}
Process& Process::operator=(const Process& alpha)
{
	this->ProcessName = alpha.ProcessName;
	this->Priority = alpha.Priority;
	this->ProcessID = alpha.ProcessID;
	this->ArrivalTime = alpha.ArrivalTime;
	this->Sub = alpha.Sub;
	this->CPUTimer = alpha.CPUTimer;
	this->IOTimer = alpha.IOTimer;
	this->CPUTotal = alpha.CPUTotal;
	this->ITotal = alpha.ITotal;
	this->OTotal = alpha.OTotal;
	this->CPUCount = CPUCount;
	this->ICount = alpha.ICount;
	this->OCount = alpha.OCount;
	this->Timestamp = alpha.Timestamp;
	// Copy all elements of History
	for(int i = 0; i < 10; i++)
	{	this->History[i] = alpha.History[i]; }
	return *this;
}
