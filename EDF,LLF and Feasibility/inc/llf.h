/**********************
@File Name	: llf.h
@Description: 	: Scheduling Tasks based on llf policy
@Author		: Deepesh Sonigra 
@Date		: 02/15/2020  
*******************/


#ifndef LLF_H_
#define LLF_H_

#include <stdio.h>


#define U32_T unsigned int


 /*
@description: calculates the feasability of the task based on llf policy
@return     : returns true or false 
*/

int
least_laxity_first(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);

#endif
