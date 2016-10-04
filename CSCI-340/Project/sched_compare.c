#include <stdio.h>   // for printf()
#include <stdlib.h>  // for atoi()

#include "procs.h"
#include "procheap.h"

// DO NOT CHANGE THESE TWO CONSTANTS !
#define INTER_ARRIVAL_TIME 3   // mean poisson dist
#define SERVICE_TIME       5   // mean poisson dist


double myvalue(proc_t *proc){
	return proc->service_time;
}

void FCFS(proc_t* ary, int total){
	
	printf("FCFS\n");
	int i;
	double total_time = 0;
	double average_wait;
	double average_turn;
	for(i=0;i<total;i++){
		while(ary[i].arrival_time>total_time){
			total_time++;
		}
		if(ary[i].arrival_time<total_time){
			ary[i].wait_time=total_time-ary[i].arrival_time;
		}
		total_time = total_time + ary[i].service_time;
	}
	
	average_wait = 0;
	average_turn = 0;
	
	for (i = 0; i < total; i++) {
		average_wait = average_wait + ary[i].wait_time;
		average_turn = average_turn + (ary[i].wait_time + ary[i].service_time);
	}
	
	average_wait = average_wait / total;
	average_turn =  average_turn / total;
	
	printf("Average wait time is: %f\n",average_wait);
	printf("Average turnaround time is: %f\n",average_turn);
	
}


void highest_response_ratio_next(proc_t* procs, int numprocs){
	int i;
	int j;
	int run;
	int ran[numprocs];
	
	double average_wait;
	double average_turn;
	double current_time;
	
	
	int hrrnInt;
	
	for(i=0;i<numprocs;i++){
		ran[i]=0;
	}
	printf("HRRN\n");
	
	current_time = 0;
	hrrnInt=-1;
	i=0;
	run=0;
	
	while(i<numprocs){
		run=0;
		for(j=0;j<numprocs;j++){
			if(procs[j].arrival_time<=current_time && ran[j]==0){
				run = 1;
				procs[j].wait_time=current_time-procs[j].arrival_time;
				if( hrrnInt==-1 || ((procs[j].wait_time + procs[j].service_time) / procs[j].service_time )> ((procs[hrrnInt].wait_time + procs[hrrnInt].service_time) / procs[hrrnInt].service_time)  ){
					hrrnInt=j;
				}
				
			}
			
		}
		if(run == 1){
			ran[hrrnInt]=1;
			procs[hrrnInt].wait_time=current_time-procs[hrrnInt].arrival_time;
			current_time = current_time + procs[hrrnInt].service_time;
			hrrnInt=-1;
			i++;
			
		}	
		else{
			current_time++;
		}
	}
	
	average_wait = 0;
	average_turn = 0;
	
	for (i = 0; i < numprocs; i++) {
		average_wait = average_wait + procs[i].wait_time;
		average_turn = average_turn + (procs[i].wait_time + procs[i].service_time);
	}
	
	average_wait = average_wait / numprocs;
	average_turn =  average_turn / numprocs;
	
	printf("Average wait time is: %f\n",average_wait);
	printf("Average turnaround time is: %f\n",average_turn);
	
}

void shortest_process_next(proc_t* procs, int numprocs){
	
	int i;
	int j;
	int run;
	int ran[numprocs];
	double average_wait;
	double average_turn;
	double current_time;
	int shortInt;
	
	
	for(i=0;i<numprocs;i++){
		ran[i]=0;
	}
	
	printf("SPN\n");
	current_time = 0;
	shortInt=-1;
	i=0;
	run=0;
	while(i<numprocs){
		run=0;
		for(j=0;j<numprocs;j++){
			if(procs[j].arrival_time<=current_time && ran[j]==0){
				run = 1;
				if( shortInt==-1 || procs[j].service_time<procs[shortInt].service_time  ){
					shortInt=j;
				}
				
			}
			
		}
		if(run == 1){
			ran[shortInt]=1;
			procs[shortInt].wait_time=current_time-procs[shortInt].arrival_time;
			current_time = current_time + procs[shortInt].service_time;
			shortInt=-1;
			i++;
			
		}	
		else{
			current_time++;
		}
	}
	
	
	average_wait = 0;
	average_turn = 0;
	
	for (i = 0; i < numprocs; i++) {
		average_wait = average_wait + procs[i].wait_time;
		average_turn = average_turn + (procs[i].wait_time + procs[i].service_time);
	}
	
	average_wait = average_wait / numprocs;
	average_turn =  average_turn / numprocs;
	
	printf("Average wait time is: %f\n",average_wait);
	printf("Average turnaround time is: %f\n",average_turn);
	
}




int main(int argc, char** argv)
{
  int numprocs, seed;
  proc_t *procs;   // array of procs with service time and arrival time

  if (argc < 3) {
    fprintf(stderr, "USAGE: %s numprocs seed\n", argv[0]);
    return 1;
  }

  numprocs = atoi(argv[1]);
  seed = atoi(argv[2]);

  // create an array of numprocs randomly generate (arrival time, service time)
  procs = procs_random_create(numprocs, seed, INTER_ARRIVAL_TIME, SERVICE_TIME);
  
  // Uncomment the next block of code and comment the line above if
  // you want to read the input from a file instead of generating
  // random values. This can be useful for debugging your code with
  // known inputs.  The file, "book_example.txt", contains an example
  // from the book.

  /*
  if ((procs = procs_read("book_example.txt", &numprocs)) == NULL) {
    fprintf(stderr, "Error reading procs array\n");
    return 2;
  }
  */

  printf("procs array:\n");
  printf("(arrival time, service time)\n");
  procs_print(procs, numprocs);

  /* Either call your implemented functions for performing FCFS, SPN,
     and HRRN, or insert your code here to perform these algorithms.
     My recommendation is to write one or more functions for these
     algorithms in order for your main to be more readable and
     manageable.
  */
  
  
  //OUR CODE 
  shortest_process_next(procs,numprocs);
  procs = procs_random_create(numprocs, seed, INTER_ARRIVAL_TIME, SERVICE_TIME);
  highest_response_ratio_next(procs,numprocs);
  procs = procs_random_create(numprocs, seed, INTER_ARRIVAL_TIME, SERVICE_TIME);
  FCFS(procs,numprocs);
  

  free(procs);   // procs array was dynamically allocated, so free up

  return 0;
}



























