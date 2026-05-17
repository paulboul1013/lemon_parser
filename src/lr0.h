#ifndef LEMON_LR0_H
#define LEMON_LR0_H

#include "grammar.h"

typedef struct {
    int rule_id;
    int dot_pos;
} Item;

void print_item(Grammar *g, Item item);

#endif