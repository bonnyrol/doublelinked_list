#include <stdlib.h>
#include <stdio.h>

#define EPS 1e-52
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

/*idk*/
void insert(List *list, Item *item, const int n);

/*Функиця для очитски экрана*/
void cls();

/*Вывод меню в консоль*/
void menu();

int input_choise();

/*Вывод списка list в консоль*/
void listout(const List *list);

int main() {
    List list = {NULL, NULL};
    Item item0 = {NULL, NULL};
    Item item1 = {NULL, NULL};
    Item item2 = {NULL, NULL};
    Item *item3;

#ifdef _WIN64
    system("chcp 65001 > NUL");
#endif

    add(&list, &item0);
    add(&list, &item1);
    add(&list, &item2);

    menu();
    printf("%d\n", input_choise());

#ifdef _WIN64
    system("pause");
#endif

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

void clear(List *list) {
    Item *item = list->head;
    Item *next = item->next;
    while (item) {
        Item *next = item->next;
        free(item);
        item = next;
    }
}

void Delete(List *list, const int n) {
    Item *item = Remove(list, n);
    if (item) {
        free(item);
    } 
}

void insert(List *list, Item *item, const int n) {
    // if (list && item && n >= 0) {
    //     Item *temp = getitem(list, n);

    //     if (temp) {
    //         /*Если список пуст или мы вставляем в конец списка*/
    //         if ((!list->head && !list->tail) || list->tail == temp) {
    //             add(list, item);
    //         } else if () {

    //         } else {

    //         }
    //     }
    // }
}

void listout(const List *list) {
    Item *item = list->head;
    int i = 0;

    printf("List: %p\tHead: %p\tTail: %p\n", list, list->head, list->tail);
    printf("№\titem\tprev\tnext\n");
    while (item) {
        printf("%d\t%p\t%p\t%p\n", i, item, item->prev, item->next);
        i++, item = item->next;
    }
}

void cls() {
#ifdef _WIN64
    system("cls");
#elif defined __linux__
    system("clear");
#endif
}

void menu() {
    printf("1. Вывод всех элементов на экран\n");
    printf("2. Добавление элемента в список\n");
    printf("3. Добавление элемента в любое место списка\n");
    printf("4. Подсчёт всех элементов в списке\n");
    printf("5. Поиск элемента по индексу\n");
    printf("6. Поиска индекса по элементу\n");
    printf("7. Исключение элемента из списка\n");
    printf("8. Удаление элемента из списка\n");
    printf("9. Полная очистка списка\n");
    printf("0. Выход из программы\n");
}

int input_choise() {
    double buff = 0;
    char ch = '\0';
    int flag = 1;

    while (flag) {
        printf("Выберите пункт: ");
        if (scanf("%lf", &buff) != 1 || buff - (int)buff != 0 || (int)buff < 0 || (int)buff > 9) {
            printf("Некорректный ввод, попробуй снова\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        } else {
            flag = 0;
        }
    }  

    return (int)buff;
}