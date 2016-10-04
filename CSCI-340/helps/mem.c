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
	/*TODO
	 *
	 */
	int i, block_size, probes = 0,  start_pos = -1, best_index, best_size = mem_size + 1, done = 0, at_end = 0;

	//BEST
	if(strategy == BESTFIT) {
	  	//Find first open slot
		for(i = 0; i < mem_size; i++)
			if(memory[i] == 0) {
				start_pos = i;
				break;
			}

		//If no open slots
		if(start_pos == -1)
			return -1;

		while(start_pos < mem_size) {
			//Reset block_size
			block_size = 0;

			//Get block_size
			for(i = start_pos; i < mem_size; i++) {
				if(memory[i] == 0)
					block_size++;
				else
					break;
			}

			//Keep on going
			if(block_size <= 0)
				start_pos++;

			//Perfect fit, return
			else if(block_size == size)
				return start_pos;

			//Better block
			else if(block_size > size && block_size < best_size) {
				best_index = start_pos;
				best_size = block_size;
				done = 1;
				start_pos += block_size;
			}

			//Too small
			else {
				probes++;
				start_pos += block_size;
			}
		}

		//Did we do it?
		if(done) { //Yes
			//Put the values in
			for (i = 0; i < size; i++)
				memory[best_index + i] = duration;

			return probes;
		}
		else //No
			return -1;
	}

	//FIRST
	if(strategy == FIRSTFIT) {
		//Find first open slot
		for(i = 0; i < mem_size; i++)
			if(memory[i] == 0) {
				start_pos = i;
				break;
			}

		//If no open slots
		if(start_pos == -1)
			return -1;


		//Look for available places
		while(start_pos < mem_size && !done) {
			//Reset block_size
			block_size = 0;

			//Get block_size
			for(i = start_pos; i < mem_size; i++) {
				if (memory[i] == 0)
					block_size++;
				else
					break;
			}

			//Keep on going
			if(block_size <= 0)
				start_pos++;

			//We have a match!
			else if(block_size >= size) {
				//Put the values in
				for(i = 0; i < size; i++)
					memory[start_pos + i] = duration;

				//Set the "completed" flag
				done = 1;
			}

			//Try again after the block
			else {
				probes++;
				start_pos += block_size;
			}
		}

		//Did we do it?
		if (done) //Yes
			return probes;
		else //No
			return -1;
	}

	//NEXT
	if(strategy == NEXTFIT) {
		start_pos = last_placement_position;
		while(start_pos < mem_size && !done) {
			//Reset block_size
			block_size = 0;

			//Get block_size
			for(i = start_pos; i < mem_size; i++) {
				if(memory[i] == 0)
					block_size++;
				else
					break;
			}

			//Keep on going
			if(block_size <= 0)
				start_pos++;

			//It's fit!
			else if(block_size >= size) {
				//Put the values in
				for (i = 0; i < size; i++)
					memory[start_pos + i] = duration;

				//Set last_placement
				last_placement_position = start_pos;

				//Set the "completed" flag
				done = 1;
			}

			//Try again after the block
			else {
				probes++;
				start_pos += block_size;
				if(!at_end && start_pos >= mem_size) { //Hit the end and start over
					at_end = 1;
					start_pos = start_pos % mem_size;
				}
			}
		}

		//Did we do it?
		if(done) //Yes
			return probes;
		else //No
			return -1;
	}

	return 0;
}

/*
  Go through all of memory and decrement all positive-valued entries.
  This simulates one unit of time having transpired.  NOTE: when a
  memory cell is decremented to zero, it becomes "unallocated".
 */
int mem_single_time_unit_transpired()
{
	int i;

	for(i = 0; i < mem_size; i++)
		if(memory[i] > 0)
			memory[i]--;

	return 0; //I guess...
}

/*
  Return the number of fragments in memory.  A fragment is a
  contiguous free block of memory of size less than or equal to
  frag_size.
 */
int mem_fragment_count(int frag_size)
{
	int i = 0, num_frags = 0, num_free = 0;

	for(i = 0; i < mem_size; i++) {
		if(memory[i] == 0)
			num_free++;
		if(i > 0 && memory[i] != 0 && memory[i - 1] == 0) {
			if(num_free < frag_size)
				num_frags++;
			num_free = 0;
		}
	}

	return num_frags;
}

/*
  Set the value of zero to all entries of memory.
 */
void mem_clear()
{
	int i;

	for(i = 0; i < mem_size; i++)
		memory[i] = 0;
}

/*
 Allocate physical memory to size. This function should 
 only be called once near the beginning of your main function.
 */
void mem_init(int size)
{
  memory = malloc(sizeof(dur_t)*size);
  mem_size = size;
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

	for(i = 0; i < mem_size; i++)
		printf("%d", memory[i]);

	printf("\n");
}
