/**********************
@File Name	: edf.h
@Description: 	: Scheduling Tasks based on EDF policy
@Author		: Deepesh Sonigra 
@Date		: 02/15/2020
@reference 	:  https://embeddedbhavesh.wordpress.com/2015/10/04/earliest-deadline-first-edf-scheduling-in-c/   
*******************/


#ifndef EDF_H_
#define EDF_H_



#include <math.h>
#include <stdio.h>
#include<limits.h>

#define TRUE 	(1)
#define FALSE 	(0)
#define ERROR 	(-1)

#define U32_T unsigned int 





/*
@description: calculates the greatest common divisor
@return     : returns the gcd 
*/

int 
get_gcd(int a,int b);

/*
@description: calculates the least common multiple 
@return     : returns the lcm
@reference  : GeeksforGeeks 
*/
long int 
get_lcm( U32_T arr[], U32_T size);



/*
@description: calculates the pos of minimum non zero number in array
@return     : returns the pos
@reference  : GeeksforGeeks 
*/

U32_T 
find_nonzero_min(U32_T arr[] , U32_T size);


 /*
@description: calculates the feasability of the task based on edf policy
@return     : returns true or false 
*/
int
earliest_deadline_first(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);

#endif

