#include "../include/doublelinked.h"

void insert(List *list, Item *item, const int n) {
    if (list && item) {
        Item *temp = getitem(list, n);
        
        /*Если список пуст или мы вставляем в конец списка*/
        if (is_empty(list) || !temp) {
            add(list, item);
        } else if (temp == list->head) {
            item->next = list->head;
            list->head->prev = item;
            list->head = item;
        } else {
            item->prev = temp->prev;
            item->next = temp;
            temp->prev = item;
            item->prev->next = item;
            
        }
    }
}