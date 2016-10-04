#include <semaphore.h>

sem_t lock;
sem_init( &lock,0,-1);
printf("num %d",sem_getValue(&lock));