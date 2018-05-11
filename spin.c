#include "spin.h"

static inline unsigned int
xchg(volatile unsigned int *addr, unsigned int newval)
{
    unsigned int result;
    asm volatile("lock; xchgl %0, %1" : "+m" (*addr), "=a" (result) : "1" (newval) : "cc");
    return result;
}

void spinlock_acquire(spinlock_t *lock)
{
    while(xchg(&(lock->flag), 1) == 1)
        ;
}

void spinlock_release(spinlock_t *lock)
{
    xchg(&(lock->flag), 0);
}

spinlock_t* init_lock() {
    spinlock_t *res = (spinlock_t*)malloc(sizeof(spinlock_t));
    res->flag = 0;
    return res;
}
