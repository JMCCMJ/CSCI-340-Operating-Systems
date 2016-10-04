#include <stdio.h>   /* for printf() */
#include <stdlib.h>  /* for malloc() */

#include "procs.h"
#include "poisson.h"

proc_t *procs_random_create(int numprocs, unsigned seed,
			    int arrival_lambda, int service_lambda)
{
  int i;
  proc_t *procs;

  procs = malloc(numprocs * sizeof(proc_t));
  
  init_poisson(seed, arrival_lambda);
  procs[0].arrival_time = poisson();
  for (i = 1; i < numprocs; i++) {
    procs[i].arrival_time = procs[i-1].arrival_time + poisson();
  }

  init_poisson(seed, service_lambda);
  for (i = 0; i < numprocs; i++) {
    procs[i].service_time = poisson();
  }

  return procs;
}

void procs_print(const proc_t *procs, int numprocs)
{
  int i;
  
  for (i = 0; i < numprocs; i++) {
    printf("   (%.0f, %.0f)\n", procs[i].arrival_time, procs[i].service_time);
  }
  printf("\n");
}

proc_t *procs_read(const char* filename, int *numprocs)
{
  double arrival_time, service_time;
  int count = 0;
  proc_t *procs;
  FILE *fp;

  if ((fp = fopen (filename, "r")) == NULL) {
    fprintf(stderr, "Error opening file %s for reading\n", filename);
    return NULL;
  }

  while (fscanf(fp, "%lf %lf", &arrival_time, &service_time) == 2) {
    count++;
  }

  procs = malloc(count * sizeof(proc_t));
  *numprocs = count;

  rewind(fp);

  count = 0;
  while (fscanf(fp, "%lf %lf", &arrival_time, &service_time) == 2) {
    procs[count].arrival_time = arrival_time;
    procs[count].service_time = service_time;
    count++;
  }

  fclose(fp);

  return procs;
}
