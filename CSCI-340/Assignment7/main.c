#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for string to integer conversion, random numbers */
#include "mem.h"

/*
  The main program will accept four paramemters on the command line.
  The first parameter is the memory size.  The second parameter is the
  duration of the each simulation run.  The third parameter is the
  number of times to repeat each experiment (ie. number of runs). The
  fourth parameter is a random number seed. Here is an example command
  line:

  ./hw7 1000 3000 100 1235

  This means that your program should initialize physical memory to
  1,000 units, perform 100 runs with each run taking 3000 units of
  time, and the random number generator should be seeded (one time)
  with the value 1235.
*/

int main(int argc, char** argv)
{  
	int mem_arg;
	int duration_simulation_run;
	int runs;
	int random_seed;
	int i;
	int bestfit_probes;
	int bestfit_fails;
	int temp_probes;
	int nextfit_probes;
	int nextfit_fails;
	int firstfit_probes;
	int firstfit_fails;
	int bestfit_frags;
	int firstfit_frags;
	int nextfit_frags;
	
	int random_dur;
	int random_size;
	
	srand(random_seed);
	
	
	mem_arg = strtol(argv[1],NULL,0);
	duration_simulation_run = strtol(argv[2],NULL,0);
	runs = strtol(argv[3],NULL,0);
	random_seed = strtol(argv[4],NULL,0);
	
	mem_init(mem_arg);
	
	
	
	mem_clear();
	bestfit_frags = 0;
	bestfit_probes = 0;
	bestfit_fails = 0;
	for(i=0;i<runs;i++){//BESTFIT
		random_dur = MIN_DURATION + rand() % (MAX_DURATION-MIN_DURATION);
		random_size = MIN_REQUEST_SIZE  + rand() % (MAX_REQUEST_SIZE-MIN_REQUEST_SIZE);

		temp_probes = mem_allocate(BESTFIT,random_size,random_dur);
		if(temp_probes == -1){
			bestfit_fails++;
		}
		else{
			bestfit_probes = bestfit_probes + temp_probes;
		}
		mem_single_time_unit_transpired();
	}
	bestfit_frags = mem_fragment_count(MIN_REQUEST_SIZE-1);
	mem_clear();
	
	nextfit_frags = 0;
	nextfit_probes = 0;
	nextfit_fails = 0;
	for(i=0;i<runs;i++){//NEXTFIT
		random_dur = MIN_DURATION + rand() % (MAX_DURATION-MIN_DURATION);
		random_size = MIN_REQUEST_SIZE  + rand() % (MAX_REQUEST_SIZE-MIN_REQUEST_SIZE);

		temp_probes = mem_allocate(NEXTFIT,random_size,random_dur);
		if(temp_probes == -1){
			nextfit_fails++;
		}
		else{
			nextfit_probes = bestfit_probes + temp_probes;
		}
		mem_single_time_unit_transpired();
	}
	nextfit_frags = mem_fragment_count(MIN_REQUEST_SIZE-1);
	mem_clear();
	
	firstfit_frags = 0;
	firstfit_probes = 0;
	firstfit_fails = 0;
	for(i=0;i<runs;i++){//FIRSTFIT
		random_dur = MIN_DURATION + rand() % (MAX_DURATION-MIN_DURATION);
		random_size = MIN_REQUEST_SIZE  + rand() % (MAX_REQUEST_SIZE-MIN_REQUEST_SIZE);

		temp_probes = mem_allocate(FIRSTFIT,random_size,random_dur);
		if(temp_probes == -1){
			firstfit_fails++;
		}
		else{
			firstfit_probes = bestfit_probes + temp_probes;
		}
		mem_single_time_unit_transpired();
	}
	firstfit_frags = mem_fragment_count(MIN_REQUEST_SIZE-1);
	mem_clear();
	
	
	
	printf("BESTFIT\n");
	
	printf("mean fragment count = %.6f\n",(float)bestfit_frags / (float)runs);
	printf("mean number of probes = %.6f\n",(float)bestfit_probes/(float)runs);
	printf("mean number of fails = %.6f\n",(float)bestfit_fails/(float)runs);
	//printf("probes %d\n",bestfit_probes);
	
	
	printf("FIRSTFIT\n");
	
	printf("mean fragment count = %.6f\n",(float)firstfit_frags / (float)runs);
	printf("mean number of probes = %.6f\n",(float)firstfit_probes/(float)runs);
	printf("mean number of fails = %.6f\n",(float)firstfit_fails/(float)runs);
	//printf("probes %d\n",bestfit_probes);
	
	
	
	printf("NEXTFIT\n");
	
	printf("mean fragment count = %.6f\n",(float)nextfit_frags / (float)runs);
	printf("mean number of probes = %.6f\n",(float)nextfit_probes/(float)runs);
	printf("mean number of fails = %.6f\n",(float)nextfit_fails/(float)runs);
	//printf("probes %d\n",bestfit_probes);
	
	mem_free();
	
  return 0;
}
