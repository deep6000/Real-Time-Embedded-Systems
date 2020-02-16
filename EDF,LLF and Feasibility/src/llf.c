
/**********************
@File Name	: llf.c
@Description: 	: Scheduling Tasks based on llf policy
@Author		: Deepesh Sonigra 
@Date		: 02/15/2020
@reference 	:   
*******************/


#include "llf.h"
#include "edf.h"


#define TRUE 	(1)
#define FALSE 	(0)
#define ERROR 	(-1)

#define U32_T unsigned int 

int
least_laxity_first(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]){

	U32_T _deadline[numServices];
	U32_T _period[numServices];
	U32_T _computation[numServices];
 	U32_T _laxity[numServices];
	U32_T min_laxity;
	
		// creating copies of array as we don't want to manipulate the original values 
	for(int i = 0 ; i < numServices; i++){
		_deadline[i] = deadline[i];
		_period[i] = period[i];
		_computation[i] = wcet[i];    	
	}
	long int lcm = get_lcm(period,numServices);
	
	//run the services for the lcm time slots
	for( int timeslot = 1; timeslot <= lcm; timeslot++){
			// Calculate the laxity
		 for(int task_id = 0 ; task_id < numServices; task_id++)
			_laxity[task_id] = _deadline[task_id] - _computation[task_id];
		
		min_laxity = find_nonzero_min(_laxity,numServices);
		if(min_laxity == -1)
			break;	

		// executing the task with least deadline		
		if (_computation[min_laxity] != 0)
			_computation[min_laxity]--;
		
		for(int task_id = 0 ; task_id < numServices; task_id++){	
			_deadline[task_id]--;

		if(_deadline[task_id] == 0 && _computation[task_id]!= 0)
			return FALSE;

		//if computation is over make deadline 0 so that it is not selected as next task
		else if(_computation[task_id] == 0)
			_deadline[task_id] = 0;


		if((timeslot % period[task_id] == 0)){
		// if 1 period is over restore the period
			_period[task_id] = period[task_id];
			_deadline[task_id] = deadline[task_id];
			_computation[task_id] = wcet[task_id];
			}
					
	
		}
	
	}
		
		return TRUE; 	

		
}
