#include "../include/subj.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/* Вспомогательные, или инкапсулированные функции, которые требуются 
* только для работы в данном контексте. Интерфейс к ним не предоставляется */

static field f = 0;

int get_bit(const int a, const int i) {
    return (a & (1 << i)) >> i;
}

int set_bit(int a, const int i, const int bit) {
    return (bit) ? (a | (1 << i)) : (~(1 << i) & a);
}

int convert(const void* shape) {
    Base s = *(Base *)shape;

    return (s.x - 'a') * 8 + s.y;
}

bool check_availability(const void* shape) {
    return !get_bit(f, convert(shape));
}

/* Базовые функции */

// Base * Create(PieceType t) {
//     Base * p = NULL;
//     switch (t) {
//         case T_Pawn:
//             p = malloc(sizeof(Pawn));
//             break;
//         case T_Rook:
//             p = malloc(sizeof(Rook));
//             break;
//         case T_Knight:
//             p = malloc(sizeof(Knight));
//             break;
//         case T_Bishop:
//             p = malloc(sizeof(Bishop));
//             break;
//         case T_Queen:
//             p = malloc(sizeof(Queen));
//             break;
//         case T_King:
//             p = malloc(sizeof(King));
//             break;
//     }
//     if (p) {
//         p->type = t;
//         p->x = 0, p->y = 0;

//         if (t == T_Pawn || t == T_Rook) { // Если фигура - это пешка или ладья
//             p->moves = CAN_MOVE_V | (t == T_Rook) ? CAN_MOVE_H : 0;
//         } else if (t == T_Queen || t == T_King) { // Если фигура - это ферзь или король
//             p->moves = CAN_MOVE_H | CAN_MOVE_V | CAN_MOVE_D;
//         } else if (t == T_Bishop) { // Если наш слоняра
//             p->moves = CAN_MOVE_D;
//         } else { // Если мы не попали ни в одно из условий выше, значит текущая фигура - конь
//             p->moves = CAN_MOVE_K;
//         }
//     }

//     return p;
// }

void PawnInit(void *pawn) {
    
}

void RookInit(void *rook) {

}

void KnightInit(void *knight) {

}

void BishopInit(void *bishop) {

}

void QueenInit(void *queen) {

}

void KingInit(void *king) {

}

Base * Create(PieceType t) {
    void (*init[])(void *base) = {NULL, PawnInit, RookInit, KnightInit, BishopInit, QueenInit, KingInit};

    Base * p = NULL;
    switch (t) {
        case T_Pawn:
            p = malloc(sizeof(Pawn));
            break;
        case T_Rook:
            p = malloc(sizeof(Rook));
            break;
        case T_Knight:
            p = malloc(sizeof(Knight));
            break;
        case T_Bishop:
            p = malloc(sizeof(Bishop));
            break;
        case T_Queen:
            p = malloc(sizeof(Queen));            
            break;
        case T_King:
            p = malloc(sizeof(King));
            break;
        default:
            break;
    }

    if (p) {
        p->type = t;
        init[(int)t](p);
    }

    return p;
}


void input(Base *shape) {


    char ch;

    printf("0 - black, 1 - white: ");
    while (scanf("%d", (int *)&shape->color) != 1 ) {
        printf("color govno\n");
        while ((ch = getchar()) != '\n' && (ch != EOF));
    }
    
    while(true) {
        


    }




    // do {
    //    int  k = scanf("%c", &shape->x);
    //     if (k != 2) {
    //         printf("Некорректный ввод, k = %d\n", k);
    //     } else if (shape->x < 'a' || shape->x > 'h') {
    //         printf("govno\n");
    //     } else if (!check_availability(shape)) {
    //         continue;
    //     } else {
    //         break;
    //     }   

    // } while (1);
    
    
}

