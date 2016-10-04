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
	void run_tests(enum mem_strats);
	void print_results(int);
	void clear_results();
	int probes = 0;
	int frags = 0;
	int avg_probes = 0;
	int avg_failures = 0;
	int avg_frags = 0;
	int total_probes = 0;
	int total_failures = 0;
	int total_frags = 0;

int main(int argc, char** argv)
{
	int i, j;
	int mem_size = (int) strtol(argv[1], 0, 10); //mem_size
	int duration = (int) strtol(argv[2], 0, 10); //for loop a
	int num_runs = (int) strtol(argv[3], 0, 10); //for loop b
	int randseed = (int) strtol(argv[4], 0, 10); //seed

	mem_init(mem_size);
	mem_clear();
	srand(randseed);

	/*********************************
	 * BESTFIT
	 ********************************/
	for(i = 1; i <= duration; i++)
		for(j = 1; j <= num_runs; j++)
			run_tests(BESTFIT);

	mem_clear();
	srand(randseed);

	printf("\n========= BESTFIT =========\n");
	print_results(num_runs);
	clear_results();//*/

	/*********************************
	 * FIRSTFIT
	 ********************************/
	for(i = 1; i <= duration; i++)
		for(j = 1; j <= num_runs; j++)
			run_tests(FIRSTFIT);

	mem_clear();
	srand(randseed);

	printf("\n========= FIRSTFIT =========\n");
	print_results(num_runs);
	clear_results();//*/

	/*********************************
	 * NEXTFIT
	 ********************************/
	for(i = 1; i <= duration; i++)
		for(j = 1; j <= num_runs; j++)
			run_tests(NEXTFIT);

	mem_clear();
	srand(randseed);

	printf("\n========= NEXTFIT =========\n");
	print_results(num_runs);
	clear_results();//*/

	mem_free();

	return 0;
}

void run_tests(enum mem_strats strat)
{
	int size;
	dur_t dura;

	size = rand() % MAX_REQUEST_SIZE + MIN_REQUEST_SIZE;
	dura = rand() % MAX_DURATION + MIN_DURATION;

	//See what need
	//printf("\n[%d, %d]", size, dura);

	probes = mem_allocate(strat, size, dura);

	if(probes != -1)
		total_probes += probes;
	else if(probes == -1)
		total_failures++;

	frags = mem_fragment_count(MIN_REQUEST_SIZE - 1);
	total_frags += frags;

	//Use only with small numbers
	//mem_print();

	mem_single_time_unit_transpired();
}

void print_results(int runs)
{
	//Calculate the averages
	avg_frags = total_frags / runs;
	avg_probes = total_probes / runs;
	avg_failures = total_failures / runs;

	//Print said averages
	printf("Avg. Probes: %i\n", avg_probes);
	printf("Avg. Failures: %i\n", avg_failures);
	printf("Avg. Fragments: %i\n", avg_frags);
}

void clear_results()
{
	probes = 0;
	frags = 0;
	avg_probes = 0;
	avg_failures = 0;
	avg_frags = 0;
	total_probes = 0;
	total_failures = 0;
	total_frags = 0;
}
