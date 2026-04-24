#include<stdio.h>
#include <stdlib.h>
#include <string.h>

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
} Grammar;

void grammar_init(Grammar *g){
    g->symbol_count=0;
    g->rule_count=0;
    g->start_symbol=-1;
}

int add_symbol(Grammar *g,const char *name,Symbolkind kind){
    if (g->symbol_count>=MAX_SYMBOLS){
        fprintf(stderr,"Error: too many symbols\n");
        exit(1);
    }

    int id=g->symbol_count;

    g->symbols[id].id=id;
    strncpy(g->symbols[id].name,name,MAX_NAME-1);
    g->symbols[id].name[MAX_NAME-1]='\0';
    g->symbols[id].kind=kind;

    g->symbol_count++;

    return id;
}

void add_rule(Grammar *g,int lhs,int rhs[],int rhs_len){
    if (g->rule_count>=MAX_RULES){
        fprintf(stderr,"Error: too many rules\n");
        exit(1);
    }

    if (rhs_len > MAX_RHS){
        fprintf(stderr,"Error: RHS too long\n");
        exit(1);
    }

    int id=g->rule_count;

    g->rules[id].id=id;
    g->rules[id].lhs=lhs;
    g->rules[id].rhs_len=rhs_len;

    for(int i=0;i<rhs_len;i++){
        g->rules[id].rhs[i]=rhs[i];
    }

    g->rule_count++;
    
}

const char *symbol_kind_name(Symbolkind kind){
    if (kind==SYM_TERMINAL){
        return "TERMINAL";
    }else{
        return "NONTERMINAL";
    }
}

void print_symbols(Grammar *g){
    printf("Symbols:\n");

    for(int i=0;i<g->symbol_count;i++){
        Symbol *sym=&g->symbols[i];

        printf(" [%d] %-8s %s\n",
                sym->id,
                sym->name,
                symbol_kind_name(sym->kind));
    }

    printf("\n");
}

void print_rules(Grammar *g){
    printf("Rules:\n");

    for(int i=0;i<g->rule_count;i++){
        Rule *r=&g->rules[i];

        printf("  Rule %d: %s ->",
                r->id,
                g->symbols[r->lhs].name);

        for(int j=0;j<r->rhs_len;j++){
            int sym_id=r->rhs[j];
            printf(" %s",g->symbols[sym_id].name);
        }

        printf("\n");
    }

    printf("\n");
}

void print_grammar(Grammar *g){
    if (g->start_symbol!=-1){
        printf("Start symbol: %s\n\n",g->symbols[g->start_symbol].name);
    }else {
        printf("Start symbol: <not set>\n\n");
    }

    print_symbols(g);
    print_rules(g);
}


int main(void){
    Grammar g;
    grammar_init(&g);

    int expr=add_symbol(&g,"expr",SYM_NONTERMINAL);
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

    print_grammar(&g);

}
