#include "../include/doublelinked.h"

Item* getitem(const List *list, const int n) {
    Item *item = NULL;

    if (list) {
        item = list->head;
        int i = 0;

        while (item && n != i) {
            i++;
            item = item->next;
        }
    }

    return item;
}