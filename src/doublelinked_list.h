#ifndef _DOUBLELINKED_LIST
#define _DOUBLELINKED_LIST

typedef struct _item {
    _item *next;
    _item *prev;
} Item;

typedef struct {
    Item *head;
    Item *tail;
} List;

/*Добавляет в конец списока list элемент item */
void add(List *list, Item *item);

/*Удаляет из списка list элемент n*/
void Delete(List *list, int n);

/*Возвращает элемент n из списка list*/
Item* getitem(List *list, int n);

/*????? ?????? ????? ?? ???? ?????? ???????*/
Item* remove(List *list, int n);

/*Возвращает кол-во элементов списка list*/
int count(List *list);

/*Очищает список list*/
void clear(List *list);

/*Возвращает порядковый номер элемента item списка list*/
int getindex(List *list, Item *item);

#endif //_DOUBLELINKED_LIST