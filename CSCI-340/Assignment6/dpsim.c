#include "dpsim.h"


static const unsigned int NUM_PHILOSPHERS = 5;
static const unsigned int NUM_CHOPSTICKS = 5;

static int chopsticks[5];
static pthread_mutex_t mutex[5];
static pthread_t philosphers[5];


void* th_main( void* th_main_args ) {

	// ---------------------------------------
	// TODO: you add your implementation here
	int i;
	int deadlockCheck;
	
	//printf("We in th_main\n");
	for(i=0;i<NUM_CHOPSTICKS;i++){
		chopsticks[i]=-1;
		printf("Chopstick %d is: %d\n",i,chopsticks[i]);
	}
	
	for(i=0;i<NUM_PHILOSPHERS;i++){ //CREATE THREADS
		if(pthread_create(&philosphers[i], NULL,th_phil, (void*)i)==0){
			//SUCESS
			
		}
		else{
			perror("Create had an error!\n");
			exit(1);
		}
	}
	
	while(TRUE){
		delay(10000);
		
		printf("Philopsher(s) ");
		for(i=0;i<NUM_CHOPSTICKS;i++){
			if((chopsticks[i]==chopsticks[(i+1)%5])&&chopsticks[i]!=-1){
				printf("%d ",i);
			}
		}
		printf("are eating.\n");
		
		if((chopsticks[0]==0&&chopsticks[1]==1&&chopsticks[2]==2&&chopsticks[3]==3&&chopsticks[4]==4)&&chopsticks[0]!=-1){
			deadlockCheck++;
			//printf("deadlock count: %d\n",deadlock);
		}
		if(deadlockCheck==100){
			printf("Deadlock condition (0,1,2,3,4) ... terminating\n");
			
			for(i=0;i<NUM_CHOPSTICKS;i++){
				
				pthread_kill(&philosphers[i],1);		
			}
			pthread_exit(0);
		}
		
	}
	

} // end th_main function


void* th_phil( void* th_phil_args ) {

	// ---------------------------------------
	// TODO: you add your implementation here
	int i;
	int breaker;
	i = (int)th_phil_args;
	
	
	while(TRUE){
		
		//printf("Philosopher %d is thinking!\n",i);
		delay(10000);
		//printf("Philosopher %d is trying to eat!\n",i);
		eat(i);
		
	}	

} // end th_phil function


void delay( long nanosec ) {
	
	struct timespec t_spec;

	t_spec.tv_sec = 0;
	t_spec.tv_nsec = nanosec;

	nanosleep( &t_spec, NULL );

} // end think function


void eat( int phil_id ) {

	// ---------------------------------------
	// TODO: you add your implementation here
	int i;
	i = (int)phil_id;
	//printf("Philosopher %d is eating\n",i);
	delay(10000);
	pthread_mutex_lock(&mutex[i]);
	chopsticks[i]=i;
	delay(10000);
	pthread_mutex_lock(&mutex[(i+1) % 5]);
	chopsticks[(i+1) % 5]=i;
	delay(10000);
	chopsticks[(i+1) % 5]=-1;
	pthread_mutex_unlock(&mutex[(i+1) % 5]);
	chopsticks[i]=-1;
	pthread_mutex_unlock(&mutex[i]);
	printf("Philosopher %d successfully finished eating!\n",i);



} // end eat function
