#ifndef _hash_t
#define _hash_t

#include "spin.h"
#include "list.h"

typedef struct HASHTABLE {
    int bucket_num;
    spinlock_t *glock;
    list_t **buckets;
}hash_t;


void Hash_Init(hash_t *hash, int buckets);
void Hash_Insert(hash_t *hash, void *element, unsigned int key);
void Hash_Delete(hash_t *hash, unsigned int key);
void *Hash_Lookup(hash_t *hash, unsigned int key);
void delete_hash(hash_t *hash);

#endif
