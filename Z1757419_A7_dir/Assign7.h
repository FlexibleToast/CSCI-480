#ifndef ASSIGN7_H
#define ASSIGN7_H
/*******************************************************************************
 * File:        Assign7.h
 * Programmer:  Joseph McDade
 * zID:         1757419
 * Due Date:    11/30/2018
 *
 * Purpose:     Header file for Assign7 program
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>

// Prototyping statements
void initialize_directory();
void readline(string);
int allocate(size_t, int pass_start_block = 0);
int reallocate(size_t, int);
void deallocate(int);
void tokenize(string, vector<string>&);
int find_empty(int);
void print_fat();

// Set global constants
#define HOW_OFTEN 6
#define BLOCK_SIZE 512
#define BLOCK_ENTRIES 12
#define PRINT 24

// Create global variables
short fat[4096] = {0};	// FAT12 table
list<Entry> directory;	// List of entries in the directory
	int sim_counter = 0;	// Tracks cycles of the simulation

#endif
