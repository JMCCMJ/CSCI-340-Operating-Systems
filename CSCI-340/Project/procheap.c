#include <stdio.h>   /* for printf() */
#include <stdlib.h>  /* for malloc() */
#include <values.h>  /* for MAXDOUBLE */

#include "procs.h"

static proc_t **heap;
static int heapsize;
static int max_heapsize;
static double (*proc_val)(const proc_t *);

void heap_init(int size, double (*value_func)(const proc_t *))
{
  max_heapsize = size;
  heap = malloc((size+1)*sizeof(proc_t*));  /* heap starts at position 1 */
  heapsize = 0;
  proc_val = value_func;
  heap[0] = malloc(sizeof(proc_t));
  heap[0]->arrival_time = -MAXDOUBLE;
  heap[0]->service_time = -MAXDOUBLE;
  heap[0]->wait_time = -MAXDOUBLE;
}

void heap_free()
{
  free(heap[0]);
  free(heap);
}

int heap_size()
{
  return heapsize;
}

proc_t *heap_top()
{
  return heapsize > 0 ? heap[1] : NULL;
}

int heap_insert(proc_t *elem)
{
  if (++heapsize > max_heapsize)
    return 0;

  heap[heapsize] = elem; /* Insert in the last place */
  
  /* Adjust its position */
  int pos = heapsize;
  while (proc_val(heap[pos/2]) > proc_val(elem)) {
    heap[pos] = heap[pos/2];
    pos /= 2;
  }
  heap[pos] = elem;

  return 1;
}

proc_t *heap_deletemin()
{
  /* heap[1] is the minimum element. So we remove heap[1]. Size of the
     heap is decreased.  Now heap[1] has to be filled. We put the last
     element in its place and see if it fits.  If it does not fit,
     take minimum element among both its children and replace parent
     with it.  Again, see if the last element fits in that place.
  */
  proc_t *last_elem, *min_elem;
  int child, parent;

  if (heapsize == 0)
    return NULL;

  min_elem = heap[1];
  last_elem = heap[heapsize--];
  
  for (parent = 1; parent*2 <= heapsize ; parent = child) {
    
    /* child is the index of the element which is minimum among both
       the children.  Indexes of children are i*2 and i*2 + 1*/
    child = parent*2;
    
    /* child != heapsize because heap[heapsize+1] does not exist,
       which means it has only one child */
    if (child != heapsize &&
       proc_val(heap[child+1]) < proc_val(heap[child])) {
      child++;
    }
    /* To check if the last element fits or not it suffices to check
       if the last element is less than the minimum element among both
       the children */
    if (proc_val(last_elem) > proc_val(heap[child])) {
      heap[parent] = heap[child];
    }
    else { /* It fits here */
      break;
    }
  }
  
  heap[parent] = last_elem;
  
  return min_elem;
}

/*
void heap_age(double amount)
{
  int i;
  int size = heapsize;
  proc_t **a = malloc(size*sizeof(proc_t*));

  // NOTE:  heap is a complete binary tree
  for (i = 0; i < size; i++) {
    a[i] = heap[i+1];
    a[i]->wait_time += amount;
  }

  heap_free();
  heap_init(max_heapsize, proc_val);

  for (i = 0; i < size; i++)
    heap_insert(a[i]);

  free(a);
}
*/

// this should be equivalent to more complicated version above
void heap_age(double amount)
{
  int i;
  
  for (i = 1; i <= heapsize; i++) {
    heap[i]->wait_time += amount;
  }
}
