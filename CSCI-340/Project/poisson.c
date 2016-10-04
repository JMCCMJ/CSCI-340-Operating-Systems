#include <stdlib.h>   /* for srand(), rand() */
#include <math.h>     /* exp() */

static double lambda;

void init_poisson(unsigned int seed, double lam)
{
  srand(seed);
  lambda = lam;
}

int poisson()
{
  int k = 0;
  double L = exp(-lambda), p = 1;
  
  do {
    ++k;
    p *= rand()/(double) RAND_MAX;
  } while (p > L);
  
  return --k;
}
