#include <stdio.h>

#include "grammar.h"

int main(void){
    Grammar g;
    grammar_init(&g);

    int expr=add_symbol(&g,"expr",SYM_NONTERMINAL);
    int expr2=add_symbol(&g,"expr",SYM_NONTERMINAL);
    // int expr3=add_symbol(&g,"expr",SYM_TERMINAL);
    int term=add_symbol(&g,"term",SYM_NONTERMINAL);
    int factor=add_symbol(&g,"factor",SYM_NONTERMINAL);

    int NUMBER=add_symbol(&g,"NUMBER",SYM_TERMINAL);
    int PLUS   = add_symbol(&g, "PLUS", SYM_TERMINAL);
    int STAR   = add_symbol(&g, "STAR", SYM_TERMINAL);
    int LPAREN = add_symbol(&g, "LPAREN", SYM_TERMINAL);
    int RPAREN = add_symbol(&g, "RPAREN", SYM_TERMINAL);
    int EOF_SYM = add_symbol(&g, "EOF", SYM_TERMINAL);

    g.start_symbol=expr;

    int rhs0[]={expr,PLUS,term};
    add_rule(&g,expr,rhs0,3);

    int rhs1[] = {term};
    add_rule(&g, expr, rhs1, 1);

    int rhs2[] = {term, STAR, factor};
    add_rule(&g, term, rhs2, 3);

    int rhs3[] = {factor};
    add_rule(&g, term, rhs3, 1);

    int rhs4[] = {NUMBER};
    add_rule(&g, factor, rhs4, 1);

    int rhs5[] = {LPAREN, expr, RPAREN};
    add_rule(&g, factor, rhs5, 3);

    (void)EOF_SYM;

    printf("original grammar\n");
    print_grammar(&g);

    augment_grammar(&g);

    printf("augmented grammar\n");
    print_grammar(&g);

}
