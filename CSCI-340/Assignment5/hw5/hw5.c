#include <stdio.h>         // for printf()
#include <pthread.h>       // for pthread_xxx() routines
#include <sys/time.h>
#include <sys/resource.h>
#include <limits.h>
#include <stdlib.h>

#include "mcsim.h" // monte carlo simulation function prototypes

double gcount;    // global counter -- a double to handle large sums (billions+)
long numits;      // global variable for number of iterations (see step 3 below)

int main(int argc, char** argv)
{
	int i;
	int max_os_threads;
	struct rlimit rlim;
	pthread_t* threads;
	int user_threads;
	int user_iterations;
	char * x;
	struct timespec time_start, time_end;
	float elapsed_time;
	float total_dots;
	float prob;
	float pi;
	
	//Setting the attr up
	pthread_attr_t attr;
	pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    
    //User input was empty 
    if(argv[1]==NULL || argv[2]==NULL){
			exit(0);
	}
    //User input
	user_threads = strtol(argv[1], &x, 10);
	user_iterations = strtol(argv[2], &x, 10);
	
	numits = user_iterations;
	gcount = 0;
	total_dots = (float)user_threads * (float)user_iterations;
	
	//Max OS thread limit
	getrlimit(RLIMIT_NPROC, &rlim);
	max_os_threads=rlim.rlim_cur;
	
	//printf("argc: %d \n",argc);
	//for(i=0;i<argc;i++){
		//printf("argv [%d]: %s \n",i,argv[i]);
	//}
	//printf("max os theads: %d \n",max_os_threads);
	//printf("user_threads: %d \n",user_threads);
	//printf("user_iterations: %d \n",user_iterations);
	
	threads = malloc(user_threads*sizeof(pthread_t));
	
	//CLOCK START TIME
	clock_gettime(CLOCK_MONOTONIC, &time_start);
	
	if(!(user_threads>max_os_threads)){
		//printf("Do stuff \n");
		
		
		for(i=0;i<user_threads;i++){ //CREATE THREADS
			if(pthread_create(&threads[i], &attr,th_routine, (void*)i)==0){
				//SUCESS
			}
			else{
				exit(1);
			}
		}
		
		for(i=0;i<user_threads;i++){ //JOIN THREADS
			
			if(pthread_join(threads[i],NULL)==0){
				//SUCESS
			}
			else{
				exit(1);
			}
		}
		
		prob = ((float)gcount/(float)total_dots);
		pi = 4 * prob;
		printf("monte carlo value of PI = %.6f \n",pi); 
		
		//CLOCK END TIME
		clock_gettime(CLOCK_MONOTONIC, &time_end);
		
		//Sending info to mydifftime
		elapsed_time = (float)mydifftime(&time_start,&time_end);
		elapsed_time = elapsed_time/1000000000;
		printf("value of count = %.0f \n",gcount);
		printf("time in seconds = %.4f \n",elapsed_time);
	}
	else{
		exit(1);
		
	}
	
	free(threads);
	pthread_exit(NULL);
  /*

    ---------------------------------------------------------------------
    Step-by-Step procedure for Monte carlo simulator to estimate PI
    ---------------------------------------------------------------------
    1. Create the following variables:
       - pointer to an array of pthread structures
       - counting variables for loops
       - thread id
       - exit status of joined thread
       - number of threads to run
       - maximum number of threads (hint: rlimit)
       - nanosecond start and stop timespec structs
    2. Get number of threads input by user from argv[1]
    3. Get number of iterations input by user from argv[2]
    4. Get maximum number of threads the OS can create (man getrlimit function)
    5. If number of threads > maximum OS threads then goto 14, else goto step 6
    6. Allocate array of pthread structures using number of threads from step 2
    7. Get start time of simulation and store in timespec struct
    8. Create a pthread for each position in pthread array created in step 6
       - if an error occurs during thread creation exit simulation immediately
    9. Join each pthread created in the pthread array
       - if an error occurs during thread join exit simulation immediately
    10. Get stop time of simulation and store in timespec struct
    11. Print out:
       - value of PI using 6 decimal places
       - value stored in global variable gcount using 0 decimal places
       - time in seconds to run the simulation using 4 decimal places (hint: use mydifftime function)
    12. Free memory allocated for pthread array
    13. Call pthread terminate function (hint: pthread_exit function)
    14. exit simulation program

    ---------------------------------------------------------------------
    Example input and output of Monte carlo simulator to estimate PI
    ---------------------------------------------------------------------

    # ./hw5 300 100  // i.e. run simulatior using 300 threads and 100 iterations

    monte carlo value of PI = 3.141200
    value of count = 23559
    time in seconds = 0.0761
  */

  return 0;

} // end main function
