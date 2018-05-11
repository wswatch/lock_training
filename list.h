#ifndef _list_t
#define _list_t
#include "spin.h"

typedef struct NODE {
    unsigned int key;
    void* element;
    struct NODE *next;
}node_t;

typedef struct linklist {
    node_t *head;
    spinlock_t *lock;
}list_t;

void List_Init(list_t *list);
void List_Insert(list_t *list, void *element, unsigned int key);
void List_Delete(list_t *list, unsigned int key);
void *List_Lookup(list_t *list, unsigned int key);
void delete_node(node_t* node);
void delete_list(list_t *list);
#endif
