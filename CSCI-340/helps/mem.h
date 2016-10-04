/* minimum and maximum duration of use for an allocated block of memory */
#define MIN_DURATION     13
#define MAX_DURATION     27      /* must "fit" in a dur_t type (see below) */

/* minimum and maximum allocation request size */
#define MIN_REQUEST_SIZE    7
#define MAX_REQUEST_SIZE   57

typedef unsigned char dur_t;     /* duration type (eg. unsigned char, int) */
typedef enum mem_strats { BESTFIT, FIRSTFIT, NEXTFIT } mem_strats_t;

int mem_allocate(mem_strats_t strategy, int size, dur_t duration);

int mem_single_time_unit_transpired();

int mem_fragment_count(int frag_size);

void mem_clear();

void mem_init(int size);

void mem_free();

void mem_print();
