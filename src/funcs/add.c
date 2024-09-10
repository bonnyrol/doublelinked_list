#include "../doublelinked_list.h"

void add(List *list, Item *item) {
    if (!list->head) {
        list->head = item, list->head = item;
        item->next = NULL, item->prev = NULL; 
    } else {
        item->prev = list->tail;
        item->next = NULL;
        list->tail = item;
    }
}