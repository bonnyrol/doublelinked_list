#ifndef SUBJ_H_
#define SUBJ_H_

#include "doublelinked.h"
#include <stdbool.h>

typedef enum {
    //T_None, // Фигура не определена
    T_Pawn, // Пешка
    T_Rook, // Ладья
    T_Knight, // Конь
    T_Bishop, // Слон
    T_Queen, // Ферзь(Королева)
    T_King // Король
} PieceType;

typedef long int field;

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
    char moves;
} Base;
 
typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
    char moves;
} Pawn;

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
    char moves;
} Rook;

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
    char moves;
} Knight;

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
    char moves;
} Bishop;

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
    char moves;
} Queen;

typedef struct {
    Item *next;
    Item *prev;
    PieceType type;
    bool color;
    char x;
    int y;
    char moves;
} King;

#define CAN_MOVE_H 1 /* Может двигаться горизонтально */
#define CAN_MOVE_V 2 /* Может двигаться вертикально */
#define CAN_MOVE_D 4 /* Может дваигаться по диагонали */
#define CAN_MOVE_K 8 /* Двигается как конь*/

/* piece->moves = CAN_MOVE_H | CAN_MOVE_V | CAN_MOVE_D */

void sort(List *l);
Base * Create(PieceType t);
void print(const Base *p);
void input(Base *shape);


#endif // SUBJ_H_