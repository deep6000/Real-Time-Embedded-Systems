/**********************
@File Name	: edf.h
@Description: 	: Scheduling Tasks based on EDF policy 
@Date		: 02/15/2020
@reference 	: Prof Sam Seiwert feasibility_tests.c   
*******************/

#ifndef RMA_H_
#define RMA_H_

#include <stdio.h>
#include <math.h>

#define U32_T unsigned int

 /*
@description: calculates the feasability of the task based on rma policy
@return     : returns true or false 
*/
int completion_time_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);


 /*
@description: calculates the feasability of the task based on rma policy
@return     : returns true or false 
*/

int scheduling_point_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);

#endif
