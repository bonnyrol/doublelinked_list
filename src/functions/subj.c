#include "../include/subj.h"
#include <stdlib.h>
#include <stdio.h>

/* Вспомогательные, или инкапсулированные функции, которые требуются 
* только для работы в данном контексте. Интерфейс к ним не предоставляется */

/* Перевод данных в строку out */
void convert_to_str(const void *data, char *out) {
    switch (((Base *)data)->type) {
        case T_long:
            snprintf(out, MAX_STR_SIZE, "%ld", ((Long *)data)->data);
            break;
        case T_double:
            snprintf(out, MAX_STR_SIZE, "%.2lf", ((Double *)data)->data);
            break;
        case T_string:
            snprintf(out, MAX_STR_SIZE, "%s", ((String *)data)->str);
            break;
        case T_char:
            snprintf(out, MAX_STR_SIZE, "%c", ((Char *)data)->ch);
            break;
        default:
            break;
    }
}

/* Неиспользуемая функция, удалить при пуше в прод */
// void swap(List *l, Item *a, Item *b) {

//     int i = getindex(l, a), j = getindex(l, b);
//     Item *b_temp = Remove(l, j);
//     insert(l, b_temp, i);
//     Item *a_temp = Remove(l, i + 1);
//     insert(l, a_temp, j);

// }

Base* make_copy(const Base *item) {
    Base *copy = Create(item->type);
    
    memcpy(copy, item, item->size);

    return copy;
}

int cool_comporator(const char *a, const char *b, const int mode) {

    int result = strcmp(a, b) > 0;

    return (mode) ? !result : result;
}

/* Базовые функции */

Base * Create(const DataType t) {
    Base * p = NULL;

    size_t size = 0;

    switch (t) {
        case T_long:
            size = sizeof(Long);
            break;
        case T_double:
            size = sizeof(Double);
            break;
        case T_string:
            size = sizeof(String);
            break;
        case T_char:
            size = sizeof(Char);
            break;
        default:
            break;
    }

    if (size) {

        p = calloc(1, size); // Выделяем память и заполняем всё нулями
    }

    if (p) {
        p->type = t;
        p->size = size;
    }

    return p;
}

void search(const List *l, const char *value, List *out) {

    /* Шаришь за законы Де Моргана??? */
    if (!(l || value || out)) {
        return;
    }

    List result = {0};

    Item *temp = l->head;

    while (temp) { // temp != NULL
        char buff[MAX_STR_SIZE] = {'\0'};
        Base *tmp = (Base *)temp;
        
        convert_to_str(temp, buff);

        /* Поиск по строгому условию */
        // if (!strcmp(value, buff)) {

        //     Base *copy = make_copy(tmp);

        //     add(&result, ((Item *)copy));
        // }

        /* Нормальный поиск */
        if (strstr(buff, value)) {

            Base *copy = make_copy(tmp);

            add(&result, ((Item *)copy));

        }

        temp = temp->next;
    }

    *out = result;
}

/* mode = 0 - По возрастанию, mode = 1 - по убыванию */
void sort(List *l, const int mode) {
    List new = {0};
    char i_buff[MAX_STR_SIZE] = {'\0'}, j_buff[MAX_STR_SIZE] = {'\0'};

    insert(&new, Remove(l, 0), 0);

    Item *unsorted = l->head, *sorted = NULL;
    
    while (unsorted) {
        sorted = new.head;
        convert_to_str(unsorted, i_buff), convert_to_str(sorted, j_buff);
        while (sorted && cool_comporator(i_buff, j_buff, mode)) {
            sorted = sorted->next;
        }
        if (sorted) {
            Base *copy = make_copy((Base *)unsorted);
            
            insert(&new, (Item *)copy, getindex(&new, sorted));
        } else {
            Base *copy = make_copy((Base *)unsorted);

            add(&new, (Item *)copy);
        }
        unsorted = unsorted->next;
    }
    
    clear(l);
    *l = new;
}
