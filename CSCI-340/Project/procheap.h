#ifndef PROCHEAP_H
#define PROCHEAP_H

#include "procs.h"

void    heap_init(int size, double (*value_func)(proc_t *));
void    heap_free();
int     heap_insert(proc_t *elem);
proc_t *heap_deletemin();
proc_t *heap_top();
int     heap_size();
void    heap_age(double amount);   // used by HRRN

#endif /* PROCHEAP_H */
