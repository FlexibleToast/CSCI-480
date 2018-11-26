#ifndef ENTRY_H
#define ENTRY_H
/*******************************************************************************
 * File:        Entry.h
 * Programmer:  Joseph McDade
 * zID:         1757419
 * Due Date:    11/30/2018
 *
 * Purpose:     Header file for Entry object class
 ******************************************************************************/
#include <iostream>
#include <stdlib.h>

using namespace std;

class Entry
{
  public:
		//Constructors
    Entry(int new_start, int sim_counter);
		Entry(string new_name, int new_start, int sim_counter);
		Entry(string new_name, size_t new_size, int new_start, int sim_counter);

    //Accessor Methods
		//Get Methods
		inline string get_name() const { return name; };
		inline size_t get_size() const{ return size; };
		inline int get_start() const { return start_block; };

		//Set Methods
		inline void rename(string new_name) { name = new_name; };

    //Utility Methods

		//Operator Overload
		Entry& operator=(const Entry&);

	private:
		string name;			// Name of the entry
		size_t size;			// Size in bytes of the entry
		int start_block;	// Starting block in FAT12 of entry
		int created;			// Simulation cycle created on
};

#endif
