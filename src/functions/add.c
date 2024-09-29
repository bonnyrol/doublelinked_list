#include "../include/doublelinked.h"

void add(List *list, Item *item) {
    if (list && item) {
        if (is_empty(list)) {
            list->head = item, list->tail = item;
            item->next = NULL, item->prev = NULL; 
        } else {
            item->prev = list->tail;
            list->tail->next = item;
            item->next = NULL;
            list->tail = item;
        }
    }
}