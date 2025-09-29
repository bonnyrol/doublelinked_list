#include "../include/subj.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
} Pawn;

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
} Rook;

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
} Knight;

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
} Bishop;

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;   
} Queen;

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
} King;


/* Вспомогательные, или инкапсулированные функции, которые требуются 
* только для работы в данном контексте. Интерфейс к ним не предоставляется */

Base* cpy(Base *src) {

    Base *dst = Create(src->type);

    size_t bytes_to_copy = 0;

    switch (src->type) {
    case T_Pawn:
        bytes_to_copy = sizeof(Pawn);
        break;

    case T_Rook:
        bytes_to_copy = sizeof(Rook);
        break;

    case T_Knight:
        bytes_to_copy = sizeof(Knight);
        break;

    case T_Bishop:
        bytes_to_copy = sizeof(Bishop);
        break;

    case T_Queen:
        bytes_to_copy = sizeof(Queen);
        break;

    case T_King:
        bytes_to_copy = sizeof(King);
        break;

    default:
        break;
    }

    memcpy(dst, src, bytes_to_copy);
    dst->next = NULL, dst->prev = NULL;

    return dst;
}

bool is_attack(Base *shape, char x, int y) {
    bool result = false;

    switch (shape->type) {
    case T_Pawn:
        result = ((shape->color ? shape->y - 1 : shape->y + 1) == y && \
            (shape->x - 1 == x || shape->x + 1 == x));
        break;
    case T_Rook:
        result = shape->x == x || shape->y == y;
        break;
    case T_Knight:
        if ((shape->y + 2 == y || shape->y - 2 == y) && (shape->x + 1 == x || shape->x - 1 == x)) {
            result = true;
        } else if ((shape->x + 2 == x || shape->x - 2 == x) && (shape->y + 1 == y || shape->y - 1 == y)) {
            result = true;
        }
        break;
    case T_Bishop:
        result = abs(shape->x - x) == abs(shape->y - y);
        break;
    case T_Queen:
        result = ((shape->x == x || shape->y == y) || \
            (abs(shape->x - x) == abs(shape->y - y)));
        break;
    case T_King:
        result = (shape->x + 1 == x || shape->x - 1 == x) && \
            (shape->y + 1 == y || shape->y - 1 == y);
        break;
    default:
        break;
    }

    return result;
}

Base * Create(PieceType t) {

    Base * p = NULL;
    switch (t) {
        case T_Pawn:
            p = calloc(1, sizeof(Pawn));
            break;
        case T_Rook:
            p = calloc(1, sizeof(Rook));
            break;
        case T_Knight:
            p = calloc(1, sizeof(Knight));
            break;
        case T_Bishop:
            p = calloc(1, sizeof(Bishop));
            break;
        case T_Queen:
            p = calloc(1, sizeof(Queen));            
            break;
        case T_King:
            p = calloc(1, sizeof(King));
            break;
        default:
            break;
    }

    if (p) {
        p->type = t;
    }

    return p;
}

void search_by_color(List *src, List *dst, const bool color) {

    Item* i = src->head;

    while (i) {

        Base *temp = (Base*)i;

        if (temp->color == color) {
            add(dst, (Item*)cpy(temp));
        }

        i = i->next;
    }
    
}

void sort(List *l) {
    List new = {0};

    insert(&new, Remove(l, 0), 0);

    Item *unsorted = l->head, *sorted = NULL;
    
    while (unsorted) {
        sorted = new.head;
        while (sorted && ((Base *)unsorted)->type >= ((Base *)sorted)->type) {
            sorted = sorted->next;
        }
        if (sorted) {
            Base *copy = cpy((Base *)unsorted);
            
            insert(&new, (Item *)copy, getindex(&new, sorted));
        } else {
            Base *copy = cpy((Base *)unsorted);

            add(&new, (Item *)copy);
        }
        unsorted = unsorted->next;
    }
    
    clear(l);
    *l = new;
}

void search_attacking(List *src, List *dst, const char x, const char y) {

    Item* i = src->head;

    while (i) {

        Base *temp = (Base*)i;

        if (is_attack(temp, x, y)) {
            add(dst, (Item*)cpy(temp));
        }

        i = i->next;
    }
    
}