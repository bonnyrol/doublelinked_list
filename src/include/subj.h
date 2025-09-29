#ifndef SUBJ_H_
#define SUBJ_H_

#include "doublelinked.h"
#include <stdbool.h>

typedef enum {
    T_None, // Фигура не определена
    T_Pawn, // Пешка
    T_Rook, // Ладья
    T_Knight, // Конь
    T_Bishop, // Слон
    T_Queen, // Ферзь(Королева)
    T_King // Король
} PieceType;

typedef enum {
    black = false,
    white = true
} chess_color;
typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color; // false - чёрный, true - белый
    char x;
    int y;
    // char moves;
} Base;

void sort(List *l);
Base *Create(PieceType t);
void search_attacking(List *src, List *dst, const char x, const char y);
void search_by_color(List *src, List *dst, const bool color);


#endif // SUBJ_H_