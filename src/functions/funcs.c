#include "../include/doublelinked.h"

void add(List *list, Item *item) {
    if (list && item) {
        if (is_empty(list)) {
            list->head = item, list->tail = item;
            item->next = NULL, item->prev = NULL; 
        } else {
            item->prev = list->tail;
            list->tail->next = item;
            item->next = NULL;
            list->tail = item;
        }
    }
}

void clear(List *list) {
    if (list) {

        while (list->head) {
            Delete(list, 0);
        }

        list->head = NULL, list->tail = NULL;
    }
}

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


int create_item(Item **item) {
    int code = 0;

    *item = calloc(1, sizeof(Item));
    if (!item) {
        code = 1;
    }
    
    return code;
}

void Delete(List *list, const int n) {
    if (list) {
        Item *item = Remove(list, n);
        if (item) {
            free(item);
        } 
    }
}

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

int is_empty(List *list) {
    return (list->head == NULL && list->tail == NULL) ? 1 : 0;
}

Item* Remove(List *list, const int n) {
    Item* result = NULL;

    /*Проверка входных параметров*/
    if (list) { 
        result = getitem(list, n);
        if (result) { // Продолжаем работу если элемент с индексом n есть в списке
            Item *temp = NULL;

            if (list->head == list->tail) { // Если у нас один элемент в списке
                list->head = NULL, list->tail = NULL;
            } else if (list->head == result) { // Если мы убираем первый элемент
                temp = result->next;
                temp->prev = NULL;
                list->head = temp;
            } else if (list->tail == result) { // Если мы убираем последний элемент
                temp = result->prev;
                temp->next = NULL;
                list->tail = temp;
            } else { // Если мы убираем элемент в любом другом месте
                temp = result->prev;
                temp->next = result->next;
                temp = result->next;
                temp->prev = result->prev;
            }
        }
    }

    return result;
}