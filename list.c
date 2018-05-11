#include "list.h"
#include <stdio.h>

void List_Init(list_t *list) {
    list->head = NULL;
    list->lock = init_lock();
}
void List_Insert(list_t *list, void *element, unsigned int key) {
    node_t *t;
    if (list == NULL || element == NULL) {
        printf("Error");
        return;
    }
    t = (node_t *)malloc(sizeof(node_t));
    if (t == NULL) {
        printf("Build Fail");
        return;
    }
    t->key = key;
    t->element = element;
    t->next = NULL;
    // just lock the part that will influence the whole link list
    spinlock_acquire(list->lock);
    t->next = list->head;
    list->head = t;
    spinlock_release(list->lock);
}
void List_Delete(list_t *list, unsigned int key) {

    node_t * cur = NULL;
    node_t * pre = NULL;
    // lock the whole process, otherwise it might delete the same node twice
    spinlock_acquire(list->lock);
    cur = list->head;
    while(cur) {
        if (cur -> key == key) {
            if (pre == NULL) {
                list->head = cur->next;
            }
            else {
                pre->next = cur->next;
            }
            free(cur);
            break;
        }
        else {
            pre = cur;
            cur = cur->next;
        }
    }
    spinlock_release(list->lock);
}
// do similar operaion as the list_delete
void *List_Lookup(list_t *list, unsigned int key) {
    void *res = NULL;
    node_t * cur = NULL;
    spinlock_acquire(list->lock);
    cur = list->head;
    while(cur) {
        if (cur -> key == key) {
            res = cur->element;
            break;
        }
        else {
            cur = cur->next;
        }
    }
    spinlock_release(list->lock);
    return res;
}
void delete_node(node_t *node) {

    if (node->element) {
        free(node->element);
    }
    free(node);
}
void delete_list(list_t *list) {
    node_t *cur = NULL;
    while(list->head) {
        cur = list->head;
        list->head = cur->next;
        delete_node(cur);
    }
    free(list);
}
