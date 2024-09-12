#include <stdlib.h>
#include <stdio.h>

typedef struct _item {
    struct _item *next;
    struct _item *prev;
} Item;

typedef struct {
    Item *head;
    Item *tail;
} List;

/*Добавляет в конец списка list элемент item*/
void add(List *list, Item *item);

/*Удаляет из списка list элемент по индексу n*/
void Delete(List *list, const int n);

/*Возвращает элемент по индексу n из списка list*/
Item* getitem(const List *list, const int n);

/*Исключает и возвращает элемент по индексу n из списка list*/
Item* Remove(List *list, const int n);

/*Возвращает кол-во элементов списка list*/
int count(const List *list);

/*Очищает список list*/
void clear(List *list);

/*Возвращает индекс элемента item из списка list*/
int getindex(const List *list, const Item *item);

void insert(List *list, Item *item, const int n);

int main() {
    List list = {NULL, NULL};
    Item item0 = {NULL, NULL};
    Item item1 = {NULL, NULL};
    Item item2 = {NULL, NULL};
    Item *item3;
    add(&list, &item0);
    add(&list, &item1);
    add(&list, &item2);
    int k = count(&list);
    printf("cnt before removal: %d\n", k); 

    item3 = Remove(&list, 2); 
    if (item3 = &item2) {
        printf("norm\n");
    } else {
        printf("ploho\n");
    }

    printf("cnt: %d\n", count(&list));

    return 0;
}

void add(List *list, Item *item) {
    if (!list->head) {
        list->head = item, list->tail = item;
        item->next = NULL, item->prev = NULL; 
    } else {
        item->prev = list->tail;
        list->tail->next = item;
        item->next = NULL;
        list->tail = item;
    }
}

int count(const List *list) {
    int cnt = 0;
    Item *item = list->head;
    
    while (item) {
        cnt++;
        item = item->next;
    }

    return cnt;
}

int getindex(const List *list, const Item *item) {
    int i = 0;
    Item *temp = list->head;

    while (temp != item && temp) {
        i++;
        temp = temp->next;
    }

    return (temp) ? i : -1;
}

Item* getitem(const List *list, const int n) {
    Item *item = list->head;

    if (n >= count(list)) {
        item = NULL;
    } else {
        for (int i = 0; i < n; i++) {
            item = item->next;
        } 
    }

    return item;
}

Item* Remove(List *list, const int n) {
    Item* result = NULL;

    /*Проверка входных параметров*/
    if (list && n >= 0) { 
        result = getitem(list, n);
        if (result) { // Продолжаем работу если элемент с индексом n есть в списке
            Item *temp = NULL;

            if (list->head == list->tail) { // Если у нас один элемент в списке
                list->head = NULL, list->tail = NULL;
            } else if (n == 0) { // Если мы убираем первый элемент
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

void clear(List *list) {
    
}

void Delete(List *list, const int n) {
    
}

void insert(List *list, Item *item, const int n) {
    
}
