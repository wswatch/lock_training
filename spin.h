#ifndef _spinlock_t
#define _spinlock_t

#include <stdlib.h>
#include <sys/types.h>

typedef struct spinlock {
	volatile unsigned int flag;
}spinlock_t;

static inline unsigned int
xchg(volatile unsigned int *addr, unsigned int newval);

void spinlock_acquire(spinlock_t *lock);

void spinlock_release(spinlock_t *lock);

spinlock_t* init_lock();


#endif
