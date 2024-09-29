#include "../include/doublelinked.h"

int create_item(Item **item) {
    int code = 0;

    *item = calloc(1, sizeof(Item));
    if (!item) {
        code = 1;
    }
    
    return code;
}