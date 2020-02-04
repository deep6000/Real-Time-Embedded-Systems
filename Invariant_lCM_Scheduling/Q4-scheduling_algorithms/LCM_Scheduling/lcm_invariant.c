/**********************
@File Name	: lcm_invariant.c
@Description: 	: Scheduling Tasks based on RM policy
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 02/03/2020
*******************

@references - http://ecee.colorado.edu/~ecen5623/ecen/labs/Linux/IS/Report.pdf

@references - nanosleep.h by Prof Sam Siewert
***/

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>

#include <time.h>
#include <sys/types.h>

#include <pthread.h>
#include <semaphore.h>
#include <sys/param.h>
#include <syslog.h>



#define NUM_OF_THREADS 	(2) // two threads to be scheduled based on the time period and computation
#define NUM_OF_CPUs	(1) // All threads to be scheduled on CPU core 0 

#define C1		(10000) // task 1 computation time 10ms 
#define C2		(20000)	// task 2 computation time 20ms


#define THREAD1_ID 	(0)     //thread1 ID 
#define THREAD2_ID 	(1)	//thread2 ID


#define NSEC_PER_SEC (1000000000)   // Conversions 
#define NSEC_PER_MSEC (1000000)
#define NSEC_PER_MICROSEC (1000)

unsigned int idx = 0, jdx = 1;
unsigned int seqIterations = 47;
unsigned int reqIterations[2] = {1200000,2400000};
volatile unsigned int fib = 0, fib0 = 0, fib1 = 1;

/**
Function to calculate the Fibonacci 
**/
#define FIB_TEST(seqCnt, iterCnt)      \
   for( idx=0; idx < iterCnt; idx++)    \
   {                                   \
      fib = fib0 + fib1;               \
      while(jdx < seqCnt)              \
      {                                \
         fib0 = fib1;                  \
         fib1 = fib;                   \
         fib = fib0 + fib1;            \
         jdx++;                        \
      }                                \
   }                                   \

typedef struct ThreadParams_t
{
 uint32_t threadID;
}ThreadParams_t;



// flags to abort task1 and task2
int aborttask1 = 0;
int aborttask2 = 0;

// global thread variables
pthread_t task_thread1, task_thread2;
pthread_attr_t attr_main, attr_thread1, attr_thread2;

struct sched_param rt_params_thread1,rt_params_thread2,param_main;

// structure for thread parameters
ThreadParams_t params_thread1, params_thread2;

//timestamp structures to calculate exectuion timestamp
struct timespec start_time = {0, 0};
struct timespec stop_time = {0, 0};
struct timespec diff_final_time = {0, 0};


//creating semaphores
sem_t sem_thread1, sem_thread2;



/*
@description: calculates the difference between the two timestamps and stores in third one
@return     : returns 1 on success
@reference  : nanosleep.c by Prof Sam Siewert 
*/

int delta_t(struct timespec *stop, struct timespec *start, struct timespec *delta_t)
{
  int dt_sec=stop->tv_sec - start->tv_sec;
  int dt_nsec=stop->tv_nsec - start->tv_nsec;

  if(dt_sec >= 0)
  {
    if(dt_nsec >= 0)
    {
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }
    else
    {
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }
  else
  {
    if(dt_nsec >= 0)
    {
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }
    else
    {
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }

  return(1);
}

/*
@description: Prints the type of scheduling algorithm 
@return     : void
@reference  : nanosleep.c by Prof Sam Siewert 
*/
void print_scheduler(void)
{
   int schedType;

   schedType = sched_getscheduler(getpid());

   switch(schedType)
   {
     case SCHED_FIFO:
           printf("Pthread Policy is SCHED_FIFO\n");
           break;
     case SCHED_OTHER:
           printf("Pthread Policy is SCHED_OTHER\n");
       break;
     case SCHED_RR:
           printf("Pthread Policy is SCHED_OTHER\n");
           break;
     default:
       printf("Pthread Policy is UNKNOWN\n");
   }

}


/*
@description: thread call back function
@return     : void*
@reference  : nanosleep.c by Prof Sam Siewert 
*/

void *task1(void *params)
{	
    
	pthread_t thread1;
	cpu_set_t cpuset;

	//timestamp structures
    	struct timespec finish_time = {0, 0};
    	struct timespec thread_et = {0, 0};
   
 	ThreadParams_t *ThreadParams = (ThreadParams_t *)params;
	
	// waveform for just 100 ms
    	while(!aborttask1)
    	{	
		//wait until triggered
    		sem_wait(&sem_thread1);
    		thread1=pthread_self();
    		CPU_ZERO(&cpuset);
		//perform task that takes 10ms
    		FIB_TEST(seqIterations, reqIterations[0]);
    		pthread_getaffinity_np(thread1, sizeof(cpu_set_t), &cpuset);
		
    		clock_gettime(CLOCK_REALTIME, &finish_time);
    		delta_t(&finish_time, &start_time, &thread_et);
		
		//print all thread attributes    		
		printf("\nThreadID =%d Thread Priority = %d timestamp: %ld msec (%ld microsec)", ThreadParams->threadID, rt_params_thread1.sched_priority, (thread_et.tv_nsec / NSEC_PER_MSEC), (thread_et.tv_nsec / NSEC_PER_MICROSEC));
		//print core it is running on
    		for(int i=0; i<NUM_OF_CPUs; i++)
        		if(CPU_ISSET(i, &cpuset))  
				printf("Running on CPU Core -%d\n ", i);

    	}
    
}


/*
@description: thread call back function
@return     : void*
@reference  : nanosleep.c by Prof Sam Siewert 
*/

void *task2(void *params)
{	
    	
	pthread_t thread2;
	cpu_set_t cpuset;
    	
	//timestamp structures
	struct timespec finish_time = {0, 0};
    	struct timespec thread_et = {0, 0};

    	ThreadParams_t *ThreadParams = (ThreadParams_t *)params;

	// waveform for just 100 ms
    	while(!aborttask2)
    	{	
					
		//wait until triggered
    		sem_wait(&sem_thread2);
	
    		thread2=pthread_self();
    		CPU_ZERO(&cpuset);
		//perform task that takes 10ms
    		FIB_TEST(seqIterations, reqIterations[1]);
	
    		pthread_getaffinity_np(thread2, sizeof(cpu_set_t), &cpuset);
		
    		clock_gettime(CLOCK_REALTIME, &finish_time);
    		delta_t(&finish_time, &start_time, &thread_et);
		
		//print all thread attributes    		
		printf("\nThreadID =%d Thread Priority = %d timestamp: %ld msec (%ld microsec)", ThreadParams->threadID, rt_params_thread1.sched_priority, (thread_et.tv_nsec / NSEC_PER_MSEC), (thread_et.tv_nsec / NSEC_PER_MICROSEC));
		//print core it is running on
    		for(int i=0; i<NUM_OF_CPUs; i++)
        		if(CPU_ISSET(i, &cpuset))  
				printf("Running on CPU Core -%d\n ", i);

    	}
    
}


int main ()
{	
	int scope;

	// time variables
	useconds_t comp10 = C1, comp20 = C2;
		
	// setting core 0 as CPU 
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	for(int i=0; i < NUM_OF_CPUs; i++)
       		CPU_SET(i, &cpuset);
	
	// Printing current scheduling algorithm
	print_scheduler();	
	
	//Initialize semaphores with value 1
	sem_init(&sem_thread1,0,1);
	sem_init(&sem_thread2,0,1);

	// getting priority values
	int rt_max_prio = sched_get_priority_max(SCHED_FIFO);	
	int rt_min_prio = sched_get_priority_min(SCHED_FIFO); 
	
	// setting main attributes
	pid_t mainID = getpid(); // main pid as main is currently running
	int rc = sched_getparam(mainID, &param_main);
	param_main.sched_priority=rt_max_prio;	 // main gets the highest priority
	rc=sched_setscheduler(mainID, SCHED_FIFO, &param_main);	// setting scheduling algo as FIFO for main thread
	if (rc < 0)
		perror("Error: Setting FIFO scheduler for main thread");
			
	//print scheduler to check if FIFO is set
	print_scheduler();
	
	// Print scope
	pthread_attr_getscope(&attr_main, &scope);
   	if (scope == PTHREAD_SCOPE_SYSTEM)
     		printf("PTHREAD SCOPE SYSTEM\n");
   	else if(scope == PTHREAD_SCOPE_PROCESS)
     		printf("PTHREAD SCOPE PROCESS\n");
   	else
     		printf("PTHREAD SCOPE UNKNOWN\n");

	
	// setting thread 1 parameters   
	rc=pthread_attr_init(&attr_thread1);
	rc=pthread_attr_setinheritsched(&attr_thread1, PTHREAD_EXPLICIT_SCHED);
	rc=pthread_attr_setschedpolicy(&attr_thread1, SCHED_FIFO);
       	rc=pthread_attr_setaffinity_np(&attr_thread1, sizeof(cpu_set_t), &cpuset);
       	rt_params_thread1.sched_priority=rt_max_prio-1;
       	pthread_attr_setschedparam(&attr_thread1, &rt_params_thread1);
       	params_thread1.threadID= THREAD1_ID;

	// setting thread 2 parameters   
	rc=pthread_attr_init(&attr_thread2);
	rc=pthread_attr_setinheritsched(&attr_thread2, PTHREAD_EXPLICIT_SCHED);
	rc=pthread_attr_setschedpolicy(&attr_thread2, SCHED_FIFO);
       	rc=pthread_attr_setaffinity_np(&attr_thread2, sizeof(cpu_set_t), &cpuset);
       	rt_params_thread2.sched_priority=rt_max_prio-2;
       	pthread_attr_setschedparam(&attr_thread2, &rt_params_thread2);
       	params_thread2.threadID= THREAD2_ID;
	
	//getting start time 
	clock_gettime(CLOCK_REALTIME, &start_time);
	
 	pthread_create(&task_thread1,   
                      &attr_thread1,     // thread attributes
                      task1, //  thread callback function
                      (void *)&(params_thread1) // thread parameters
                     );
	
 	pthread_create(&task_thread2,  
                      &attr_thread2,     // thread attributes
                      task2, // thread callback function
                      (void *)&(params_thread2) // thread parameters
                     );
	
	//LCM Invariant routine
	usleep(comp20);          //  20ms Thread1 runs for 10ms and then thread2 is scheduled for 10 ms 
	sem_post(&sem_thread1);  // after 20ms main interrupts as main has highest priority and triggers task1
	usleep(comp20);          // 20ms thread 1 runs for 10 ms and thread2 completes it's remaining 10ms
	sem_post(&sem_thread1);  // main interrupts and signals task1 to run
	usleep(comp10);		 // thread1 is scheduled for 10 ms 
	aborttask2 = 1;		 // thread2 task would be suspended after this run as task2 runs twice in 10ms
	sem_post(&sem_thread2);  //  thread2 was waiting on sem_thread2. hence signals to run task2
	usleep(comp10);          // thread1 is scheduled for 10ms 
	sem_post(&sem_thread1);  // main interrupts and signals task1 to run
	usleep(comp20);		 // thread1 and thread 2 again run for 10ms each (Thread2 finished computation)
	aborttask1 = 1;		 // task1 will abort after this run
	sem_post(&sem_thread1);	 // signaling thread1 to run
	usleep(comp20);		 // Thread1 runs for 10ms 

	// Calculate execution time
	clock_gettime(CLOCK_REALTIME, &stop_time);
        delta_t(&stop_time, &start_time, &diff_final_time);

	printf("\nThe execution time %ld msec (%ld microsec)\n", (diff_final_time.tv_nsec / NSEC_PER_MSEC), (diff_final_time.tv_nsec / NSEC_PER_MICROSEC));

	pthread_join(task_thread1, NULL);
        pthread_join(task_thread2, NULL);

       pthread_attr_destroy(&attr_thread1);
       pthread_attr_destroy(&attr_thread2);

	sem_destroy(&sem_thread1);
	sem_destroy(&sem_thread2);
}
