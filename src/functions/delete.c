#include "../include/doublelinked.h"

void Delete(List *list, const int n) {
    if (list) {
        Item *item = Remove(list, n);
        if (item) {
            free(item);
        } 
    }
}