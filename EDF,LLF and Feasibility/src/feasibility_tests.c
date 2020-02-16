
/**********************
@File Name	: feasibility_tests.c
@Description: 	: Scheduling Tasks based on different policies (RMA,EDF,LLF)
@Date		: 02/15/2020
@reference https://github.com/jabezwinston/Earliest_Deadline_First/blob/master/func_def.c

*******************/

#include<stdio.h>
#include<math.h>
#include "edf.h"
#include "rma.h"


#define TRUE 1
#define FALSE 0
#define U32_T unsigned int

// U=0.7333
U32_T ex0_period[] = {2, 10, 15};
U32_T ex0_wcet[] = {1, 1, 2};

// U=0.9857
U32_T ex1_period[] = {2, 5, 7};
U32_T ex1_wcet[] = {1, 1, 2};

// U=0.9967
U32_T ex2_period[] = {2, 5, 7, 13};
U32_T ex2_wcet[] = {1, 1, 1, 2};

// U=0.93
U32_T ex3_period[] = {3, 5, 15};
U32_T ex3_wcet[] = {1, 2, 3};

// U=1.0
U32_T ex4_period[] = {2, 4, 16};
U32_T ex4_wcet[] = {1, 1, 4};

// U = 1.0
U32_T ex5_period[] = {2, 5, 10};
U32_T ex5_wcet[] = {1, 2, 1};

// U = 0.996
U32_T ex6_period[] = {2, 5, 7,13};
U32_T ex6_wcet[] = {1, 1 ,1, 2};

// U = 1.0
U32_T ex7_period[] = {3, 5, 15};
U32_T ex7_wcet[] = {1, 2, 4};


// U = 1.20
U32_T ex8_period[] = {2, 5,7,13};
U32_T ex8_wcet[] = {1, 2,1 ,2};




int main(void)
{ 
	
	U32_T numServices;
    
	// Example 0
	printf("----------------------------------------------------------------\n");
 	printf("Ex-0 U=%4.4f (C1=1, C2=1, C3=2; T1=2, T2=10, T3=15; T=D):\n",
		   ((1.0/2.0) + (1.0/10.0) + (2.0/15.0)));
	numServices = sizeof(ex0_period)/sizeof(U32_T);
	printf("----------------------------------------------------------------\n");
	printf("Completion Time Feasibility         |   ");
   	if(completion_time_feasibility(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
        	printf("FEASIBLE\n");
    	else
        	printf("INFEASIBLE\n");

	printf("Scheduling Time Feasibility         |   ");
	if(scheduling_point_feasibility(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Earliest Deadline first Feasibility |   ");
	if(earliest_deadline_first(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");
 
	printf("Least Laxity first Feasibility      |   ");
	if(least_laxity_first(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("\n\n");


	// Example 1
	printf("----------------------------------------------------------------\n");
	printf("Ex-1 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=5, T3=7; T=D):\n", 
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0)));
	printf("----------------------------------------------------------------\n");	
	numServices = sizeof(ex1_period)/sizeof(U32_T);
	printf("Completion Time Feasibility         |   ");
   	if(completion_time_feasibility(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
        	printf("FEASIBLE\n");
    	else
        	printf("INFEASIBLE\n");
	
	printf("Scheduling Time Feasibility         |   ");
	if(scheduling_point_feasibility(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
       		printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Earliest Deadline first Feasibility |   ");
	if(earliest_deadline_first(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");
	
	printf("Least Laxity first Feasibility      |   ");
	if(least_laxity_first(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");
	printf("\n\n");
	
	//Example 2
	printf("----------------------------------------------------------------\n");
 	printf("Ex-2 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D):\n",
		   (float)((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex2_period)/sizeof(U32_T);
	printf("----------------------------------------------------------------\n");	

	printf("Completion Time Feasibility         |   ");
    	if(completion_time_feasibility(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
    		printf("FEASIBLE\n");
    	else
        	printf("INFEASIBLE\n");

	printf("Scheduling Time Feasibility         |   ");
	if(scheduling_point_feasibility(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Earliest Deadline first Feasibility |   ");
	if(earliest_deadline_first(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Least Laxity first Feasibility      |   ");
	if(least_laxity_first(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");
	printf("\n\n");
	
	//Example 3
	printf("----------------------------------------------------------------\n");
    	printf("Ex-3 U=%4.2f (C1=1, C2=2, C3=3; T1=3, T2=5, T3=15; T=D):\n",
		   ((1.0/3.0) + (2.0/5.0) + (3.0/15.0)));
	printf("----------------------------------------------------------------\n");	
	numServices = sizeof(ex3_period)/sizeof(U32_T);
	
	printf("Completion Time Feasibility         |   ");	
	if(completion_time_feasibility(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
        	printf("FEASIBLE\n");
    	else
        	printf("INFEASIBLE\n");
	
	printf("Scheduling Time Feasibility         |   ");
	if(scheduling_point_feasibility(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Earliest Deadline first Feasibility |   ");
	if(earliest_deadline_first(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Least Laxity first Feasibility      |   ");
	if(least_laxity_first(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");
	printf("\n\n");
	
	//Example 4
	printf("----------------------------------------------------------------\n");    	
	printf("Ex-4 U=%4.2f (C1=1, C2=1, C3=4; T1=2, T2=4, T3=16; T=D):\n",
		   ((1.0/2.0) + (1.0/4.0) + (4.0/16.0)));
	numServices = sizeof(ex4_period)/sizeof(U32_T);
	printf("----------------------------------------------------------------\n");
	printf("Completion Time Feasibility         |   ");	
	if(completion_time_feasibility(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Scheduling Time Feasibility         |   ");
	if(scheduling_point_feasibility(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Earliest Deadline First Feasibility |   ");
	if(earliest_deadline_first(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Least Laxity first Feasibility      |   ");
	if(least_laxity_first(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");
	printf("\n\n");

	// Example 5
	printf("----------------------------------------------------------------\n");
 	printf("Ex-5 U=%4.2f (C1=1, C2=2, C3=1; T1=2, T2=5, T3=10; T=D):\n",
		   ((1.0/2.0) + (2.0/5.0) + (1.0/10.0)));
	numServices = sizeof(ex5_period)/sizeof(U32_T);
	printf("----------------------------------------------------------------\n");
	printf("Completion Time Feasibility         |   ");
   	if(completion_time_feasibility(numServices, ex5_period, ex5_wcet, ex5_period) == TRUE)
        	printf("FEASIBLE\n");
    	else
        	printf("INFEASIBLE\n");

	printf("Scheduling Time Feasibility         |   ");
	if(scheduling_point_feasibility(numServices, ex5_period, ex5_wcet, ex5_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Earliest Deadline first Feasibility |   ");
	if(earliest_deadline_first(numServices, ex5_period, ex5_wcet, ex5_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Least Laxity first Feasibility      |   ");
	if(least_laxity_first(numServices, ex5_period, ex5_wcet, ex5_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");


	printf("\n\n");
	// Example 6
	printf("----------------------------------------------------------------\n");
 	printf("Ex-6 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D):\n",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex6_period)/sizeof(U32_T);
	printf("----------------------------------------------------------------\n");
	printf("Completion Time Feasibility         |   ");
   	if(completion_time_feasibility(numServices, ex6_period, ex6_wcet, ex6_period) == TRUE)
        	printf("FEASIBLE\n");
    	else
        	printf("INFEASIBLE\n");

	printf("Scheduling Time Feasibility         |   ");
	if(scheduling_point_feasibility(numServices, ex6_period, ex6_wcet, ex6_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Earliest Deadline first Feasibility |   ");
	if(earliest_deadline_first(numServices, ex6_period, ex6_wcet, ex6_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Least Laxity first Feasibility      |   ");
	if(least_laxity_first(numServices, ex6_period, ex6_wcet, ex6_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("\n\n");

	// Example 7
	printf("----------------------------------------------------------------\n");
 	printf("Ex-7 U=%4.2f (C1=1, C2=2, C3=4; T1=3, T2=5, T3=15; T=D):\n",
		   ((1.0/3.0) + (2.0/5.0) + (4.0/15.0)));
	numServices = sizeof(ex7_period)/sizeof(U32_T);
	printf("----------------------------------------------------------------\n");
	printf("Completion Time Feasibility         |   ");
   	if(completion_time_feasibility(numServices, ex7_period, ex7_wcet, ex7_period) == TRUE)
        	printf("FEASIBLE\n");
    	else
        	printf("INFEASIBLE\n");

	printf("Scheduling Time Feasibility         |   ");
	if(scheduling_point_feasibility(numServices, ex7_period, ex7_wcet, ex7_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Earliest Deadline first Feasibility |   ");
	if(earliest_deadline_first(numServices, ex7_period, ex7_wcet, ex7_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Least Laxity first Feasibility      |   ");
	if(least_laxity_first(numServices, ex7_period, ex7_wcet, ex7_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");
	printf("\n\n");

	// Example 8
	printf("----------------------------------------------------------------\n");
 	printf("Ex-8 U=%4.2f (C1=1, C2=2, C3=1 , C4=2; T1=2, T2=5, T3=7 , T4=13; T=D):\n",
		   ((1.0/2.0) + (2.0/5.0) + (1.0/7.0)+ (2.0/13.0)));
	numServices = sizeof(ex8_period)/sizeof(U32_T);
	printf("----------------------------------------------------------------\n");
	printf("Completion Time Feasibility         |   ");
   	if(completion_time_feasibility(numServices, ex8_period, ex8_wcet, ex8_period) == TRUE)
        	printf("FEASIBLE\n");
    	else
        	printf("INFEASIBLE\n");

	printf("Scheduling Time Feasibility         |   ");
	if(scheduling_point_feasibility(numServices, ex8_period, ex8_wcet, ex8_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Earliest Deadline first Feasibility |   ");
	if(earliest_deadline_first(numServices, ex8_period, ex8_wcet, ex8_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("Least Laxity first Feasibility      |   ");
	if(least_laxity_first(numServices, ex8_period, ex8_wcet, ex8_period) == TRUE)
        	printf("FEASIBLE\n");
   	else
        	printf("INFEASIBLE\n");

	printf("\n\n");


}




