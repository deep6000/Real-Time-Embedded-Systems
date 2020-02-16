
/**********************
@File Name	: edf.h
@Description: 	: Scheduling Tasks based on RMA policy
@Date		: 02/15/2020
@reference	: feasibility_tests.c Prof. Sam Siewerts 
*******************/


#include "rma.h"


#define TRUE 	(1)
#define FALSE 	(0)
#define ERROR 	(-1)

#define U32_T unsigned int 


 /*
@description: calculates the feasability of the task based on rma policy
@return     : returns true or false 
*/

int completion_time_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[])
{
  int i, j;
  U32_T an, anext;
  
  // assume feasible until we find otherwise
  int set_feasible=TRUE;
   
  //printf("numServices=%d\n", numServices);
  
  for (i=0; i < numServices; i++)
  {
       an=0; anext=0;
       
       for (j=0; j <= i; j++)
       {
           an+=wcet[j];
       }
       
	   //printf("i=%d, an=%d\n", i, an);

       while(1)
       {
             anext=wcet[i];
	     
             for (j=0; j < i; j++)
                 anext += ceil(((double)an)/((double)period[j]))*wcet[j];
		 
             if (anext == an)
                break;
             else
                an=anext;

			 //printf("an=%d, anext=%d\n", an, anext);
       }
       
	   //printf("an=%d, deadline[%d]=%d\n", an, i, deadline[i]);

       if (an > deadline[i])
       {
          set_feasible=FALSE;
       }
  }
  
  return set_feasible;
}


 /*
@description: calculates the feasability of the task based on rma policy
@return     : returns true or false 
*/

int scheduling_point_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[])
{
   int rc = TRUE, i, j, k, l, status, temp;

   for (i=0; i < numServices; i++) // iterate from highest to lowest priority
   {
      status=0;

      for (k=0; k<=i; k++) 
      {
          for (l=1; l <= (floor((double)period[i]/(double)period[k])); l++)
          {
               temp=0;

               for (j=0; j<=i; j++) temp += wcet[j] * ceil((double)l*(double)period[k]/(double)period[j]);

               if (temp <= (l*period[k]))
			   {
				   status=1;
				   break;
			   }
           }
           if (status) break;
      }
      if (!status) rc=FALSE;
   }
   return rc;
}



