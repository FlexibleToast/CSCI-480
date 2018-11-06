#ifndef ASSIGN6_H
#define ASSIGN6_H
/*******************************************************************************
 * File:        Assign6.h
 * Programmer:  Joseph McDade
 * zID:         1757419
 * Due Date:    11/14/2018
 *
 * Purpose:     Header file for Assign6 program
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <list>
#include <string>

// Prototyping statements
void initialize_avail();
void print_avail();

// Set global constants
#define HOW_OFTEN 5
#define MAX_SIZE 4194304 // Max block size in bytes
#define MB 1048576 // MB in bytes

// Global variables
list<Memblock> avail, inuse;

#endif
