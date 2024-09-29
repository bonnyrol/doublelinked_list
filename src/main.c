#include <stdio.h>
#include "include/doublelinked.h"

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

void print_item(Item *item) {
    if (!item) {
        printf("Пустой элемент\n");
    } else {
        printf("%p\t%p\n", item->prev, item->next);
    }
}


