#include <stdio.h>       
#include <pthread.h>       // for pthread_xxx() routines
#include <sys/time.h>
#include <sys/resource.h>
#include <limits.h>
#include <stdlib.h>


#include "dpsim.h" 

/**************************************************

Main Function:
	int main( int argc, char** argv )

------------------------------------------------
In this function perform the following steps:
------------------------------------------------
1. Create the following variables:
	- main_thread (pthread_t)
	- status (join status value)
2. Create a main_thread 
	- If the return value != 0, then display an error message and 
	  immediately exit program with status value 1.
3. Join the main_thread
	- If the return value != 0, then display an error message and
	  immediately exit the program with status value 2.
4. Display join status value.
5. Exit program.

*/

int main( int argc, char** argv ) {


	// ---------------------------------------
	// TODO: you add your implementation here
	
	pthread_t main_thread;
	int status;
	void* th_main_args;
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	
    //pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    
    //main_thread = malloc(1*sizeof(pthread_t));
    status = 0;
    //printf("Attemp to create.\n");
    if(pthread_create(&main_thread, NULL,th_main,(void*)main_thread)==0){
				//SUCESS
				//printf("success\n");
	}
	else{
		perror("Create had an error!\n");
		status=1;
		exit(1);
	}
	//printf("Attemp to join.\n");
	if(pthread_join(main_thread,NULL)==0){
				//SUCESS
				//printf("success\n");
	}
	else{
		perror("Join had an error!\n");
		status=2;
		exit(1);
	}
	
	//printf("we good\n");
	printf("Status: %d\n",status);
	//free(main_thread);
	//pthread_exit(NULL);

	return 0;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

} // end main function