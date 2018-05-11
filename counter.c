#include "counter.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
// initialize each bucket in the counter
block_t* init_block() {
    block_t* res = (block_t*)malloc(sizeof(block_t));
    res->lock = (spinlock_t*)malloc(sizeof(spinlock_t));
    res->value = 0;
    return res;
}
void delete_block(block_t *t) {
    if(t) {
        free(t->lock);
    }
    free(t);
}
void Counter_Init(counter_t *c, int value) {
    int i = 0;
    c->threshold = value;
    c->global = value;       // let value be the initial value
    c->glock = init_lock();
    for(i = 0; i < SIZE; ++i) {
        c->bucket[i] = init_block();
    }
}
void delete_counter(counter_t *t) {
    int i = 0;
    free(t->glock);
    for(i = 0; i < SIZE; ++i) {
        delete_block(t->bucket[i]);
    }
    free(t);
}
// when use it, just all values in the buckets up
int Counter_GetValue(counter_t *c) {
    int i = 0;
    int res = 0;
    res = c->global;
    for(i = 0; i < SIZE; ++i) {
        res += c->bucket[i]->value;
    }
    return res;
}
void Counter_Increment(counter_t *c) {
    //int i = gettid() % SIZE;
    // it seems that gettid is lost, use syscall(SYS_gettid) instead
    int i = syscall(SYS_gettid) % SIZE;
    spinlock_acquire(c->bucket[i]->lock);
    ++(c->bucket[i]->value);
    spinlock_release(c->bucket[i]->lock);
}
void Counter_Decrement(counter_t *c) {
    //int i = gettid() % SIZE;
    int i = syscall(SYS_gettid) % SIZE;
    spinlock_acquire(c->bucket[i]->lock);
    --(c->bucket[i]->value);
    spinlock_release(c->bucket[i]->lock);
}
