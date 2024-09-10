#include "../doublelinked_list.h"

int getindex(List *list, Item *item) {
    int i = 0;
    Item *temp = list->head;

    while (temp != item && temp) {
        i++;
        temp = item->next;
    }

    return i;
}