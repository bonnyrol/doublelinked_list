#include <stdio.h>
#include "include/subj.h"


void listout(List *list) {

    printf("%s\n", __func__);

    Item *i = list->head;

    while (i) {

        Base *temp = (Base *)i;

        switch (temp->type) {
        case T_Pawn:
            printf("Пешка\n");
            break;
        case T_Rook:
            printf("Ладья\n");
            break;
        case T_Knight:
            printf("Конь\n");
            break;
        case T_Bishop:
            printf("Слон\n");
            break;
        case T_Queen:
            printf("Ферзь\n");
            break;
        case T_King:
            printf("Король\n");
            break;
        default:
            break;
        }

        i = i->next;
    }
    


}

int main() {

    // Base * pawn = Create(T_Pawn);
    List list = {NULL};

    for (int i = 0; i < 12; i++) {
        add(&list, (Item *)Create((PieceType)((i % 6) + 1)));
    }
    
    listout(&list);

    sort(&list);

    putchar('\n');

    listout(&list);

    clear(&list);
    
    printf("%s\n", (char *)&list);

    return 0;
}