
/**********************
@File Name	: edf.c
@Description: 	: Scheduling Tasks based on EDF policy
@Author		: Deepesh Sonigra 
@Date		: 02/15/2020
@reference 	:  https://embeddedbhavesh.wordpress.com/2015/10/04/earliest-deadline-first-edf-scheduling-in-c/   
*******************/

#include"edf.h"


#define TRUE 	(1)
#define FALSE 	(0)
#define ERROR 	(-1)

#define U32_T unsigned int 


/*
@description: calculates the greatest common divisor
@return     : returns the gcd 
*/

int 
get_gcd(int a,int b){
	if(b == 0)
		return a;
	else
		get_gcd(b, a%b);
}


/*
@description: calculates the least common multiple 
@return     : returns the lcm
@reference  : GeeksforGeeks 
*/
long int 
get_lcm( U32_T arr[], U32_T size){
	long int res= arr[0]; 	
	for(U32_T i = 0; i<size; i++)
		res = (((arr[i]*res))/ (get_gcd( arr [i],res)));
	return res;
}
/*
@description: calculates the pos of minimum non zero number in array
@return     : returns the pos
@reference  : GeeksforGeeks 
*/

U32_T 
find_nonzero_min(U32_T arr[] , U32_T size){

	U32_T pos = -1;
	U32_T min = UINT_MAX;
	for (U32_T i = 0 ; i < size; i++){		
		if (arr[i] == 0);
		else if( min > arr[i]){
			min = arr[i];
			pos = i;			
		}
	}		
	return pos;

}

int 
earliest_deadline_first(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]) {
	
	U32_T _deadline[numServices];
	U32_T _period[numServices];
	U32_T _computation[numServices]; 
	U32_T min_deadline;
	
	// creating copies of array as we don't want to manipulate the original values 
	for(int i = 0 ; i < numServices; i++){
		_deadline[i] = deadline[i];
		_period[i] = period[i];
		_computation[i] = wcet[i];    	
	}

	long int lcm = get_lcm(period,numServices);
	
	//run the services for the lcm time slots
	for( int timeslot = 1; timeslot <= lcm; timeslot++){
	
		// find the minimum absolute deadline of all tasks 
		min_deadline = find_nonzero_min(_deadline,numServices);
	
		if(min_deadline == -1)
			break;	

		// executing the task with least deadline		
		if (_computation[min_deadline] != 0)
			_computation[min_deadline]--;
			

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




