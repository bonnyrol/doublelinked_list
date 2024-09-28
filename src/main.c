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

/*Вставка элемента item в индекс n в список list */
void insert(List *list, Item *item, const int n);

/*Функиця для очитски экрана*/
void cls();

/*Вывод меню в консоль*/
void menu();

/*Возвращает введённое целочисленное значение*/
int input(char *msg);

int entry(List *list);

/*Вывод списка list в консоль*/
void listout(const List *list);

void print_item(Item *item);

/*Выделяет память под элемент item, возвращает 1 в случае ошибки*/
int create_item(Item **item);

/*Возвращает истинну если список list пуст*/
int is_empty(List *list);

int main() {
    List list = {NULL, NULL};

#ifdef _WIN64
    system("chcp 65001 > NUL");
#endif

    while (entry(&list));
    
#ifdef _WIN64
    system("pause");
#endif

    return 0;
}

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

void clear(List *list) {
    if (list) {
        // Item *temp = list->head;
        //Item *next = NULL;

        while (list->head) {
            Delete(list, 0);
        }

        list->head = NULL, list->tail = NULL;
    }
}

void Delete(List *list, const int n) {
    if (list) {
        Item *item = Remove(list, n);
        if (item) {
            free(item);
        } 
    }
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

void listout(const List *list) {
    Item *item = list->head;
    int i = 0;

    printf("List: %p\tHead: %p\tTail: %p\n", list, list->head, list->tail);
    printf("№\titem\t\tprev\t\tnext\n");
    while (item) {
        printf("%d\t%016p\t%016p\t%016p\n", i, item, item->prev, item->next);
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
    //printf("6. Поиска индекса по элементу\n"); Не имеет практической пользы для конечного пользователя
    //printf("6. Исключение элемента из списка\n"); Утечка памяти
    printf("6. Удаление элемента из списка\n");
    printf("7. Полная очистка списка\n");
    printf("0. Выход из программы\n");
}

int input(char *msg) {
    double buff = 0;
    char ch = '\0';
    int flag = 1;

    while (flag) {

        if (msg) {
            printf("%s", msg);
        }
        if (scanf("%lf", &buff) != 1 || buff - (int)buff != 0) {
            printf("Некорректный ввод, попробуй снова\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        } else {
            flag = 0;
        }
    }  

    return (int)buff;
}

int entry(List *list) {
    int code = 1, choise = 0, n = 0;
    char ch = '\0';
    Item *item = NULL;

    menu();
    choise = input("Выберите пункт: ");
    cls();

    switch (choise) {
    case 0:
        if (!is_empty(list)) {
            printf("Очистка списка перед выходом\n");
            clear(list);
        }
        code = 0;
        break;
    case 1:
        listout(list);
        break;
    case 2:
        if (!create_item(&item)) {
            add(list, item);
            printf("Элемент %p, добавлен в список\n", item);
        } else {
            printf("Memory allocation error! Please try again\n");
        }
        break;
    case 3:
        if (!create_item(&item)) {
            listout(list);
            printf("Элемент для вставки: %p\n", item);
            n = input("Введите индекс для вставки: ");
            insert(list, item, n);
            cls();
            listout(list);
        } else {
            printf("Memory allocation error! Please try again\n");
        }
        break;
    case 4:
        printf("Количество элементов в списке: %d\n", count(list));
        break;
    case 5:
        listout(list);
        n = input("Введите n: ");
        print_item(getitem(list, n));
        break;
    case 6:
        if (!is_empty(list)) {
            listout(list);
            n = input("Введите индекс элемента для удаления: ");
            Delete(list, n);    
            cls();
            listout(list);
        } else {
            printf("Нет элементов для удаления\n");
        }
        break;
    case 7:
        if (is_empty(list)) {
            printf("Список пуст!\n");
        } else {
            clear(list);
        }
        break;
    default:
        printf("Такого пункта меню нет, попробуй снова\n");
        break;
    }

    //printf("Press enter to countinue...\n");
    // while ((ch = getchar()) != '\n' && ch != EOF);
    // getchar();
    // cls();

    return code;
}

int create_item(Item **item) {
    int code = 0;

    *item = calloc(1, sizeof(Item));
    if (!item) {
        code = 1;
    }

    return code;
}

void print_item(Item *item) {
    if (!item) {
        printf("Пустой элемент\n");
    } else {
        printf("%p\t%p\n", item->prev, item->next);
    }
}

int is_empty(List *list) {
    return (list->head == NULL && list->tail == NULL) ? 1 : 0;
}


