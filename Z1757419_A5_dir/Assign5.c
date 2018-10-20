/*******************************************************************************
   PROGRAM:			CSCI 480 Assignment 5
   PROGRAMMER:	Joseph McDade
   LOGON ID:		z1757419
   DUE DATE:		10/26/2018
	 Note:				Uses hard tabs set to display as 2 spaces

   FUNCTION:		Producer and Consumer problem using multiple producer and
	 							consumer POSIX threads, semaphores, and mutexes.
*******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Prototyping statements
void* insert_run(void* tID);
void* remove_run(void* tID);

// Set global constants
#define P_NUMBER 6
#define C_NUMBER 4
#define BUFFER_SIZE 12
#define N_P_STEPS 4
#define N_C_STEPS 6

// Create buffer
size_t widgets;
// Create semaphores and mutex
sem_t not_full, not_empty;
pthread_mutex_t counter_lock;

int main() {
	// Create pthreads
	pthread_t	producers[P_NUMBER];
	pthread_t consumers[C_NUMBER];
	// Create buffer
	size_t widgets;
	// Create thread IDs
	size_t id_size;
	if(P_NUMBER > C_NUMBER)
	{ // If more producers, create producer number of IDs
		id_size = P_NUMBER;
	} else { // Else use consumer numer of IDs
		id_size = C_NUMBER;
	}
	size_t tID[id_size];
	for(size_t i = 1; i <= (id_size); i++)
	{	// Initialize the IDs
		tID[i-1] = i;
	}
	// Initialize semaphores
	sem_init(&not_full, 0, (unsigned)BUFFER_SIZE);
	sem_init(&not_empty, 0, (unsigned)0);

	for(int i = 0; i < P_NUMBER; i++)
	{
		pthread_create(&producers[i], NULL, insert_run, (void*) &tID[i]);
	}
	for(int i = 0; i < C_NUMBER; i++)
	{
		pthread_create(&consumers[i], NULL, remove_run, (void*) &tID[i]);
	}
	for(int i = 0; i < P_NUMBER; i++)
	{
		pthread_join(producers[i], NULL);
	}
	for(int i = 0; i < C_NUMBER; i++)
	{
		pthread_join(consumers[i], NULL);
	}
	// Remove semaphores and mutex
	sem_destroy(&not_full);
	sem_destroy(&not_empty);
	pthread_mutex_destroy(&counter_lock);

  return 0;
}
/////////////////////////////////  Functions  //////////////////////////////////
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void* insert_run(void* tID){
	int *ID = (void*) tID;
	for(int i = 0; i < N_P_STEPS; i++)
	{
		sem_wait(&not_full);
		pthread_mutex_lock(&counter_lock);
		widgets++;
		printf("Producer %d inserted a widget. Total is now %d\n", *ID,
			(int)widgets);
		sem_post(&not_empty);
		pthread_mutex_unlock(&counter_lock);
		sleep(1);
	}
	return NULL;
}
/////////////////////////////////  Functions  //////////////////////////////////
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void* remove_run(void* tID){
	int *ID = (void*) tID;
	for(int i = 0; i < N_C_STEPS; i++)
	{
		sem_wait(&not_empty);
		pthread_mutex_lock(&counter_lock);
		widgets--;
		printf("Consumer %d removed a widget. Total is now %d\n", *ID,
			(int)widgets);
		sem_post(&not_full);
		pthread_mutex_unlock(&counter_lock);
		sleep(1);
	}
	return NULL;
}
