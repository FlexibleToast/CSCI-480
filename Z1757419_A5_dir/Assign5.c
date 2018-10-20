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

// Prototyping statements
void* test_run();

// Set global constants
#define P_NUMBER 6
#define C_NUMBER 4
#define BUFFER_SIZE 12
#define N_P_STEPS 4
#define N_C_STEPS 6

// Create buffer
size_t widgets;
// Create semaphores
sem_t not_full, not_empty;

int main() {
	// Create pthreads
	pthread_t	producers[P_NUMBER];
	pthread_t consumers[C_NUMBER];
	// Create buffer
	size_t widgets;
	// Create thread IDs
	size_t tID[P_NUMBER + C_NUMBER];
	for(size_t i = 1; i <= (P_NUMBER+C_NUMBER); i++)
	{
		tID[i-1] = i;
	}
	// Initialize semaphores
	sem_init(&not_full, 0, (unsigned)BUFFER_SIZE);
	sem_init(&not_empty, 0, (unsigned)0);

	pthread_create(&producers[0], NULL, test_run, (void*) &tID[0]);
	pthread_join(producers[0], NULL);
	sem_destroy(&not_full);
	sem_destroy(&not_empty);

  return 0;
}
/////////////////////////////////  Functions  //////////////////////////////////
/*******************************************************************************
Function:
Use:
Arguments:
Returns:
*******************************************************************************/
void* test_run(void* tID){
	int *ID = (void*) tID;
	printf("Hello World, this is thread: %d\n", *ID);
	for(int i = 0; i < 10; i++)
	{
		sem_wait(&not_full);
		widgets++;
		sem_post(&not_empty);
	}
	return NULL;
}
