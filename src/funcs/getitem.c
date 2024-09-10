#include "../doublelinked_list.h"

Item* getitem(List *list, int n) {
    Item *item = list->head;

    if (n >= count(list)) {
        item = NULL;
    } else {
        for (int i = 0; i < n; i++) {
            item = item->next;
        } 
    }

    return item;
}