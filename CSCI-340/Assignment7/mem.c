#include <stdio.h>    /* for printf statements when debugging */
#include <stdlib.h>   /* for malloc() and free() */
#include "mem.h"

/*
  Physical memory array. This is a static global array for all
  functions in this file.  An element in the array with a value of
  zero represents a free unit of memory.
*/
static dur_t* memory;

/*
 The size (i.e. number of units) of the physical memory array. This is
 a static global variable used by functions in this file.
 */
static int mem_size;


/*
 The last_placement_position variable contains the end position of the
 last allocated unit used by the next fit placement algorithm.
 */
static int last_placement_position;

/*
  Using the memory placement algorithm, strategy, allocate size
  units of memory that will reside in memory for duration time units.

  If successful, this function returns the number of contiguous blocks
  (a block is a contiguous "chuck" of units) of free memory probed while 
  searching for a suitable block of memory according to the placement 
  strategy specified.  If unsuccessful, return -1.

  If a suitable contiguous block of memory is found, the first size
  units of this block must be set to the value, duration.
 */
int mem_allocate(mem_strats_t strategy, int size, dur_t duration)
{
	/*
		This function is incomplete.
		
		No idea why but without the last 3 if statements at the end of the function
		probes in main will receive 0.
	*/
	int i;
	int num_probes;
	int current_index;
	int better_index;
	int better_block_size;
	int block_size;
	int allocate = -1;
	
	
	//Final take on the function...instead of using arrays to keep track I
	//tried to go through memory iteratively.
	//Still couldn't get it  :(
	num_probes = 1;
	better_block_size = mem_size + 10000;
	better_index = -1;
	for(i=0;i<mem_size;i++){
		if(i==0){
			//printf("hi\n");
			better_index = i;
			current_index = i;
			break;
		}
		
		if(better_index == -1){
			//printf("\tall full\n");
			return -1;//EVERYTHING FULL
		}
		//printf("\tbefore while\n");
		while(current_index < mem_size){
			//printf("\t in the while loop\n");
			block_size = 0;
			
			for(i=0;i<mem_size;i++){
				if(memory[i]==0){
					block_size = block_size + 1;
				}
				else{
					break;
				}
				
			}
			
			if(block_size == 0){
				//hit a nonzero
				//printf("\tfirst if\n");
			}
			else if(block_size == size){//perfect fit
				allocate = 1;
				//printf("\tfirst elif\n");
				break;
			}
			else if(block_size < better_block_size && block_size > size){//there could be a better size, so check
				allocate = 1;//there is a spot
				//printf("\tsecond elif\n");
				better_block_size = block_size;
				better_index = current_index;
				current_index = current_index + block_size;
			}
			else{
				//printf("\telse\n");
				current_index = current_index + block_size;
				num_probes++;
			}
			
		}
		
		if(allocate = 1){
			for (i = 0; i < size; i++)
				memory[better_index + i] = duration;

			return num_probes;
			
		}
		else{
			return -1;
			
		}
	}
	
	
	
	
	
	
	
	
	/*
	int i;
	int mem_checker[mem_size][1];
	int mem_checker_pos;
	int block_location;
	int block_length;
	int first_nonzero;
	
	memory[10]=5;
	memory[100]=5;
	memory[995]=10;
	
	mem_checker_pos = -1;
	block_length = 0;
	first_nonzero = 1;
	for(i=0;i<mem_size;i++){
		if(memory[i]==0){
			block_length++;
			first_nonzero = 1;
			
		}
		else{
			if(first_nonzero==1){
				mem_checker_pos++;
				mem_checker[mem_checker_pos][0]==block_length;
				mem_checker[mem_checker_pos][1]==i-1;
				first_nonzero=999;
				block_length=0;
			}
			else{
				
				//do nothing
			}
			
			
			
			
		}
		
		
	}
	*/
	
	
	/*
	int i;
	int mem_checker[mem_size][1];
	int length_block;
	int block_location;
	int first_block;
	
	int mem_checker_pos;
	
	memory[10]=5;
	memory[100]=5;
	
	
	mem_checker_pos = -1;
	first_block = 1;
	length_block=0;
	for(i=0;i<mem_size;i++){
		if((memory[i]==0) && (first_block == 1) ){
			mem_checker_pos++;
			length_block++;
			block_location = i;
			printf("first at pos %d\n",i);
			mem_checker[mem_checker_pos][1]=block_location;
			first_block=999;//no longer first
		}
		else if ((memory[i]==0) && (first_block!=1)){
			length_block++;
			mem_checker[mem_checker_pos][0]=length_block;
			//first_block = 1;
		}
		else if(memory[i]!=0){
			length_block=0;
			first_block = 1;
		}
		
	}*/
	/*
	printf("length %d and mem pos %d\n",mem_checker[-2][0],mem_checker[-2][1]);
	printf("length %d and mem pos %d\n",mem_checker[-1][0],mem_checker[-1][1]);
	printf("length %d and mem pos %d\n",mem_checker[0][0],mem_checker[0][1]);
	printf("length %d and mem pos %d\n",mem_checker[1][0],mem_checker[1][1]);
	printf("length %d and mem pos %d\n",mem_checker[2][0],mem_checker[2][1]);
	printf("length %d and mem pos %d\n",mem_checker[3][0],mem_checker[3][1]);
	printf("length %d and mem pos %d\n",mem_checker[4][0],mem_checker[4][1]);
	*/
	
	/*
	int mem_checker[mem_size][1];
	int i;
	int mem_checker_pos;
	int mem_checker_length;
	int isFirst;
	int memory_start_location;
	int has_zero_been_hit;
	
	mem_checker_pos=0;
	mem_checker_length=0;
	isFirst=0;
	memory_start_location=0;
	has_zero_been_hit = 999;
	
	memory[10]=5;
	
	
	for(i=0;i<mem_size;i++){
		if(memory[i]!=0){
			if(isFirst == 0){
				mem_checker_length++;
				isFirst=999;
				memory_start_location = memory[i];
				has_zero_been_hit = 0;
			}
			else if(i==mem_size-1){
				mem_checker[mem_checker_pos][0]=mem_checker_length;
				mem_checker[mem_checker_pos][1]=memory_start_location;
				mem_checker_length = 0;
			}
			
			else{
				memory_start_location++;
				
			}
		}
		else{
			if(has_zero_been_hit){
				mem_checker[mem_checker_pos][0]=mem_checker_length;
				mem_checker[mem_checker_pos][1]=memory_start_location;
				mem_checker_length = 0;
				isFirst = 0;
				
			}
			else{
				//do nothing
			}
			
		}
	}
	printf("%d and %d\n",mem_checker[0][0],mem_checker[0][1]);
	*/
	
	
	
	if(strategy == BESTFIT){
		printf("We are doing bestfit!\n");
		
		
	}
	else if (strategy == FIRSTFIT){
		printf("We are doing firstfit!\n");
		
	}
	else{
		printf("We are doing nextfit!\n");
	}
}

/*
  Go through all of memory and decrement all positive-valued entries.
  This simulates one unit of time having transpired.  NOTE: when a
  memory cell is decremented to zero, it becomes "unallocated".
 */
int mem_single_time_unit_transpired()
{
	int i;
	//memory[900]=10;
	for(i=0;i<mem_size;i++){
		if(memory[i]!=0){
			memory[i]=memory[i]-1;
			
		}
	}
	
	
}

/*
  Return the number of fragments in memory.  A fragment is a
  contiguous free block of memory of size less than or equal to
  frag_size.
 */
 //NOTE THIS MEANS STUFF THAT IS 0
int mem_fragment_count(int frag_size)
{
	int i;
	int frag_count;
	int isFirst;
	int pieces;
	
	pieces = 0;
	isFirst = 1;
	for(i=0;i<mem_size;i++){
		if(memory[i]==0){
			pieces++;
		}
		else if (memory[i]!=0){
			if(pieces <=frag_size){
				frag_count++;
			}
			pieces = 0;
		}
	}
	return frag_count;
	
}

/*
  Set the value of zero to all entries of memory.
 */
void mem_clear()
{
	int i;
	for(i=0;i<mem_size;i++){
		//memory[i]=1;
		//printf("before: %d\n",memory[i]);
		memory[i]=0;
		//printf("after: %d\n",memory[i]);
	}
	last_placement_position=0;
}

/*
 Allocate physical memory to size. This function should 
 only be called once near the beginning of your main function.
 */
void mem_init(int size)
{
	//printf("%d\n",size);
  memory = malloc(sizeof(dur_t)*size);
  mem_size = size;
  //printf("mem_size is %d\n",mem_size);
  //printf("memory is %d\n",sizeof(memory));
}

/*
 Deallocate physical memory. This function should 
 only be called once near the end of your main function.
 */
void mem_free()
{
  free(memory);
}

/*
  Print memory for testing/debugging purposes.  This is an optional
  routine to write, but highly recommended!  You will need to test and
  debug your allocation algorithms.  Calling this routine in your
  main() after every allocation (successful or not) will help in this
  endeavor.  NOTE: you should print the memory contents in contiguous
  blocks, rather than single units; otherwise, the output will be very
  long.
 */
void mem_print()
{
	int i;
	for(i=0;i<mem_size;i++){
		printf("Memory location %d:\t%d\n",i,memory[i]);
	}
}
