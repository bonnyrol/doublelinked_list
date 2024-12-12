#ifndef SUBJ_H_
#define SUBJ_H_

#include "doublelinked.h"
#include <string.h>

#define MAX_STR_SIZE 50

typedef enum {
    T_none,
    T_long,
    T_double,
    T_string,
    T_char
} DataType;

typedef struct {
    /* Унаследованно от Item */
    Item *next;
    Item *prev;

    /* Добавленно в Base*/
    DataType type;
    size_t size;
} Base;

typedef struct {
    /* Унаследованно от Item */
    Item *next;
    Item *prev;

    /* Унаследованно от Base*/
    DataType type;
    size_t size;

    /* Добавленно в Long*/
    long data;
} Long;

typedef struct {
    /* Унаследованно от Item */
    Item *next;
    Item *prev;

    /* Унаследованно от Base*/
    DataType type;
    size_t size;

    /* Добавленно в Double*/
    double data;
} Double;

typedef struct {
    /* Унаследованно от Item */
    Item *next;
    Item *prev;

    /* Унаследованно от Base*/
    DataType type;
    size_t size;

    /* Добавленно в String*/
    char str[MAX_STR_SIZE];
} String;

typedef struct {
    /* Унаследованно от Item */
    Item *next;
    Item *prev;

    /* Унаследованно от Base*/
    DataType type;
    size_t size;

    /* Добавленно в Char*/
    char ch;
} Char;

void sort(List *l, const int mode);
void search(const List *l, const char *value, List *out);
Base * Create(const DataType t);

#endif // SUBJ_H_