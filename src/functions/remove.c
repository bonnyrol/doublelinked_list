#include "../include/doublelinked.h"

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