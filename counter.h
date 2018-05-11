#ifndef _counter_t
#define _counter_t

#define SIZE 128
#include "spin.h"
#include <unistd.h>

typedef struct BLOCK {
    spinlock_t * lock;
    int value;
}block_t;
typedef struct Counter {
    int global;
    int threshold;
    spinlock_t * glock;
    block_t* bucket[SIZE];
}counter_t;

block_t* init_block();
void delete_block(block_t*);
void delete_counter(counter_t *);

void Counter_Init(counter_t *c, int value);
int Counter_GetValue(counter_t *c);
void Counter_Increment(counter_t *c);
void Counter_Decrement(counter_t *c);

#endif
