#include "../doublelinked_list.h"

int count(List *list) {
    int cnt = 0;
    Item *item = list->head;
    
    while (item) {
        cnt++;
        item = item->next;
    }

    return cnt;
}