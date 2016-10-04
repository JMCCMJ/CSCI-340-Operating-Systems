#ifndef PROCS_H
#define PROCS_H

typedef struct proc_struct {
  double arrival_time;
  double service_time;
  double wait_time;     // a computed value used only for HRRN
} proc_t;

proc_t *procs_random_create(int numprocs, unsigned seed,
			    int service_lambda, int arrival_lambda);
proc_t *procs_read(const char* filename, int *numprocs);
void    procs_print(const proc_t *procs, int numprocs);

#endif /* PROCS_H */
