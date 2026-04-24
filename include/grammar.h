#ifndef LEMON_GRAMMAR_H
#define LEMON_GRAMMAR_H

#define MAX_SYMBOLS 128
#define MAX_RULES 128
#define MAX_RHS 16
#define MAX_NAME 64

typedef enum {
    SYM_TERMINAL,
    SYM_NONTERMINAL
} Symbolkind;

typedef struct {
    int id; //symbol id
    char name[MAX_NAME]; //expr,NUMBER,PLUS ...
    Symbolkind kind;//terminal or non-terminal
} Symbol;

typedef struct {
    int id; 
    int lhs;
    int rhs[MAX_RHS];
    int rhs_len;
} Rule;

typedef struct {
    Symbol symbols[MAX_SYMBOLS]; //all termianl / non-terminal
    int symbol_count;
    
    Rule rules[MAX_RULES]; //all grammar rules
    int rule_count;

    int start_symbol; //start grammar，like expr

    int augmented_start_symbol;
    int augmented_rule;
} Grammar;

void grammar_init(Grammar *g);

int find_symbol(Grammar *g, const char *name);

int add_symbol(Grammar *g, const char *name, Symbolkind kind);

int add_rule(Grammar *g, int lhs, int rhs[], int rhs_len);

void augment_grammar(Grammar *g);

const char *symbol_kind_name(Symbolkind kind);

void print_symbols(Grammar *g);

void print_rules(Grammar *g);

void print_grammar(Grammar *g);

#endif