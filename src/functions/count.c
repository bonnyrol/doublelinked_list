#include "../include/doublelinked.h"

int count(const List *list) {
    int cnt = 0;

    if (list) {
        Item *item = list->head;
        
        while (item) {
            cnt++;
            item = item->next;
        }
    }

    return cnt;
}