/*******************************************************************************
 * File:        Memblock.cc
 * Programmer:  Joseph McDade
 * zID:         1757419
 * Due Date:    11/14/2018
 *
 * Purpose:     Class definitions for the Memblock object class
 ******************************************************************************/

#include "Memblock.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////  Constructors  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 * Default Constructor
 * Arguments: none
 * Notes:     Builds the default Memblock
 ******************************************************************************/
Memblock::Memblock()
{
	start = 0;
	size = 0;
	process_id = "NULL";
	block_id = "NULL";
}

Memblock::Memblock(int new_start, size_t new_size){
	start = new_start;
	size = new_size;
	process_id = "NULL";
	block_id = "NULL";
}

Memblock::Memblock(int new_start, size_t new_size,
	string new_pid, string new_bid)
{
	start = new_start;
	size = new_size;
	process_id = new_pid;
	block_id = new_bid;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Get Methods /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 * Method:
 * Arguments:
 * Returns:
 * Notes:
 ******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Set Methods /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 * Method:
 * Arguments:
 * Returns:
 * Notes:
 ******************************************************************************/
void Memblock::update(int new_start, size_t new_size){
	start = new_start;
	size = new_size;
}
void Memblock::update(int new_start, size_t new_size,
	string new_pid, string new_bid){
		start = new_start;
		size = new_size;
		process_id = new_pid;
		block_id = new_bid;
	}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// Operator Overloads //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 * Method:
 * Arguments:
 * Returns:
 * Notes:
 ******************************************************************************/
Memblock& Memblock::operator=(const Memblock& alpha){
	this->start = alpha.start;
	this->size = alpha.size;
	this->process_id = alpha.process_id;
	this->block_id = alpha.block_id;
	return *this;
}
