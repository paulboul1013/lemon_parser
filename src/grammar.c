#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "grammar.h"


void grammar_init(Grammar *g){
    g->symbol_count=0;
    g->rule_count=0;
    g->start_symbol=-1;

    g->augmented_start_symbol=-1;
    g->augmented_rule=-1;
}


int find_symbol(Grammar *g,const char *name){
    int name_len=strlen(name);
    for(int i=0;i<g->symbol_count;i++){
        if (strncmp(g->symbols[i].name,name,name_len-1)==0){
            return g->symbols[i].id;
        }
    }

    return -1;
}

int add_symbol(Grammar *g,const char *name,Symbolkind kind){
    int existing_id=find_symbol(g,name);

    if (existing_id!=-1){
        if (g->symbols[existing_id].kind!=kind){
            fprintf(stderr,"Error: symbol '%s' already exists with different kind\n",name);
            exit(1);
        }
        return existing_id;
    }
    
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

int add_rule(Grammar *g,int lhs,int rhs[],int rhs_len){
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
    
    return id;
}

void augment_grammar(Grammar *g){
    if (g->start_symbol==-1){
        fprintf(stderr,"Error: start symbol is not set\n");
        exit(1);
    }

    if (g->augmented_rule!=-1){
        return;
    }

    if (g->rule_count >=MAX_RULES){
        fprintf(stderr, "Error: too many rules for augmented grammar\n");
        exit(1);
    }

    int accept=add_symbol(g,"$accept",SYM_NONTERMINAL);

    //make origin rules move back one position
    for(int i=g->rule_count;i>0;i--){
        g->rules[i]=g->rules[i-1];
        g->rules[i].id=i;
    }

    //Add rule 0: $accept -> start_symbol

    g->rules[0].id=0;
    g->rules[0].lhs=accept;
    g->rules[0].rhs[0]=g->start_symbol;
    g->rules[0].rhs_len=1;

    g->rule_count++;

    g->augmented_start_symbol=accept;
    g->augmented_rule=0;
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

    if (g->augmented_start_symbol!=-1){
        printf("Augmented start symbol: %s\n",
               g->symbols[g->augmented_start_symbol].name);
        printf("Augmented rule: Rule %d\n", g->augmented_rule);
    }else {
        printf("Augmented start symbol: <not set>\n");
    }

    print_symbols(g);
    print_rules(g);
}