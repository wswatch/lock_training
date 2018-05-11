#include "hash.h"
#include <stdio.h>
// use fix bucket size
// inside the hash is a bunch of list_t
void Hash_Init(hash_t *hash, int buckets) {
    int i;
    hash->bucket_num = buckets;
    hash->buckets = (list_t **)malloc(sizeof(list_t*)*buckets);
    for(i = 0; i < buckets; ++i) {
        hash->buckets[i] = (list_t *)malloc(sizeof(list_t));
        List_Init(hash->buckets[i]);
    }
    hash->glock = init_lock();
}
void Hash_Insert(hash_t *hash, void *element, unsigned int key) {
    int hash_value = key % hash->bucket_num;
    List_Insert(hash->buckets[hash_value], element, key);
}
void Hash_Delete(hash_t *hash, unsigned int key) {
    int hash_value = key % hash->bucket_num;
    List_Delete(hash->buckets[hash_value], key);
}
void *Hash_Lookup(hash_t *hash, unsigned int key) {
    int hash_value = key % hash->bucket_num;
    return List_Lookup(hash->buckets[hash_value], key);
}
void delete_hash(hash_t *hash) {
    int i = 0;

    for(i = 0; i < hash->bucket_num; ++i) {
        delete_list(hash->buckets[i]);
    }
    //printf("B");
    free(hash->buckets);
    //printf("C");
    free(hash);
}
