#include <stdio.h>

#include "lr0.h"

void print_item(Grammar *g, Item item) {
    Rule *r=&g->rules[item.rule_id];

    printf("%s ->",g->symbols[r->lhs].name);

    for (int i=0;i<=r->rhs_len;i++) {
        if (i==item.dot_pos) {
            printf(" .");
        }

        if (i<r->rhs_len) {
            int sym_id=r->rhs[i];
            printf(" %s",g->symbols[sym_id].name);
        }
    }

    printf("\n");
}

