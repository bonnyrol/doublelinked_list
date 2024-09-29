#include "../include/doublelinked.h"

void clear(List *list) {
    if (list) {

        while (list->head) {
            Delete(list, 0);
        }

        list->head = NULL, list->tail = NULL;
    }
}