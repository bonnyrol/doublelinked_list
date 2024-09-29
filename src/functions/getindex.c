#include "../include/doublelinked.h"

int getindex(const List *list, const Item *item) {
    int i = 0;
    Item *temp = NULL;

    if (list && item) {
        temp = list->head;

        while (temp != item && temp) {
            i++;
            temp = temp->next;
        }
    }

    return (temp) ? i : -1;
}