#include "../include/doublelinked.h"

int is_empty(List *list) {
    return (list->head == NULL && list->tail == NULL) ? 1 : 0;
}