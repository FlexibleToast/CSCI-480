#ifndef ASSIGN4_H
#define ASSIGN4_H
/*******************************************************************************
 * File:        Assign4.h
 * Programmer:  Joseph McDade
 * zID:         1757419
 * Due Date:    10/12/2018
 *
 * Purpose:     Header file for Assign4 program
 ******************************************************************************/
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <string.h>

// Prototyping statements
queue<Process> buildEntryQueue();

// Set global constants
#define MAX_TIME 500
#define AT_ONCE 5
#define QUEUE_SIZE 20
#define ARRAY_SIZE 10
#define HOW_OFTEN 25

int Timer = 0;

#endif
