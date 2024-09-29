#ifndef DBL_LIST_H_
#define DBL_LIST_H_

#include <stdlib.h>

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

/*Вставка элемента item в индекс n в список list */
void insert(List *list, Item *item, const int n);

/*Выделяет память под элемент item, возвращает 1 в случае ошибки*/
int create_item(Item **item);

/*Возвращает истинну если список list пуст*/
int is_empty(List *list);

#endif //DBL_LIST_H_