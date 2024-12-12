#include <stdio.h>
#include "include/subj.h" // Удали 'include/' перед subj.h

int DoMenu(const char **s, const int n) {
    int i, choise;
    char ch;
    for (i = 1; i < n; i++) {
        printf("%d. %s\n", i, s[i]);
    }

    while (1) {
        int k = 0;
        printf("Выберете пункт: ");

        k = scanf("%d", &choise);
        while(((ch = getchar()) != '\n') && (ch != EOF)); // замени на fflush(stdin);
        if (k != 1) {
            printf("Некорректный ввод\n");
        } else {
            break;
        }
    }

    return choise;
}

void PrintVal(const Base *p) {

    if (p) {

        switch (p->type) {
        case T_char:
            printf("%c", ((Char *)p)->ch);
            break;
        case T_double:
            printf("%.2lf", ((Double *)p)->data);
            break;
        case T_long:
            printf("%ld", ((Long *)p)->data);
            break;
        case T_string:
            printf("%s", ((String *)p)->str);
            break;
        default:
            break;
        }
    }

}

void PrintType(const DataType t) {
    switch (t) {
        case T_char:
            printf("Char");
            break;
        case T_double:
            printf("Double");
            break;
        case T_long:
            printf("Long");
            break;
        case T_string:
            printf("String");
            break;
        default:
            break;
        }
}

void InputVal(Base *p) {
    int k = 0;
    char ch;
    if (p) {
        while (k != 1) {
            
            switch (p->type) {
            case T_char:
                k = scanf("%[^\n]c", &((Char *)p)->ch);
                break;
            case T_double:
                k = scanf("%lf", &((Double *)p)->data);
                break;
            case T_long:
                k = scanf("%ld", &((Long *)p)->data);
                break;
            case T_string:
                k = scanf("%s", ((String *)p)->str);
                break;
            default:
                break;
            }

            if (!k) {
                printf("Некорректный ввод, попробуй снова\n");
            }
            while(((ch = getchar()) != '\n') && (ch != EOF)); // замени на fflush(stdin);
        }
    
    }

}

void PrintList(const List *l) {
    Item *p;
    if (l) {
        if (l->head) {
            int i = 0;
            printf("Head: %p, Tail: %p\n\n", l->head, l->tail);
            printf(" №\tItem\t\tType\tValue\n");
            for (p = l->head; p; p = p->next) {
                printf("%2d\t%p\t", i++, p);
                PrintType(((Base *)p)->type);
                putchar('\t');
                PrintVal((Base *)p);
                putchar('\n');
            }
        } else {
            printf("List is empty.\n");
        }
    } else {
        printf("ERROR: wrong list!\n");
    }

    putchar('\n');
}

void cls() {
#ifdef _WIN64
    system("cls");
#elif defined __linux__
    system("clear");
#endif
}


int main() {

    List l = {0};
    int choise = 0;

    system("chcp 1251 > nul");


    Base * a = Create(T_long);
    Base * b = Create(T_double);
    Base * c = Create(T_char);
    Base * s = Create(T_string);

    ((Long *)a)->data = 52;
    ((Double *)b)->data = 1.52;
    ((Char *)c)->ch = 'R';
    strncpy(((String *)s)->str, "test string", 12);


    add(&l, (Item *)a);
    add(&l, (Item *)b);
    add(&l, (Item *)c);
    add(&l, (Item *)s);

    const char *TypeName[] = 
            { "(unknown)", "Long", "Double", "String", "Char" };

    const char *Menu[] =
            {"(none)",
            "Добавить новый элемент",
            "Вывести список",
            "Поиск элементов",
            "Сортировка",
            "Подчёт элементов в списке",
            "Удаление элемента",
            "Очистка списка",
            "Выход из программы"};
    const char *SortMode[] = {"(none)", "По возрастанию", "По убыванию"};

    do {
        
        choise = DoMenu(Menu, 9);
        cls();
        switch (choise) {
        case 1:
        {

            DataType t = (DataType)DoMenu(TypeName, 5);
            Base *new = Create(t);
            InputVal(new);
            add(&l, (Item *)new);
            break;
        }
        case 2:
            PrintList(&l);
            break;
        case 3:
        {
            List temp = {0};
            printf("Значение для поиска: ");
            char buff[MAX_STR_SIZE] = {'\0'};
            scanf("%50s", buff);
            search(&l, buff, &temp);
            PrintList(&temp);
            clear(&temp);
            break;
        }
        case 4:
            sort(&l, DoMenu(SortMode, 3) - 1);
            break;
        case 5:
            printf("Кол-во элементов в списке: %d\n", count(&l));
            break;
        case 6:
        {
            int i = 0;
            printf("Введите индекс для удаления: ");
            scanf("%d", &i);
            Delete(&l, i);
            break;
        }
        case 7:
            clear(&l);
            printf("Cписок очищен\n");
            break;
        case 8:
            printf("Выход из программы\n");
            clear(&l);
            break;
        default:
            printf("Такого пункта меню нет\n");
            break;
        }

    } while (choise != 8);
    

    system("pause");

    return 0;

}