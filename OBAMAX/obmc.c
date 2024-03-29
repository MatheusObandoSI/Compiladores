#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "obmc.h"

FILE *yyin;

static unsigned symhash(char *sym)
{
    unsigned int hash = 0;
    unsigned c;
    while (c = *sym++)
        hash = hash * 9 ^ c;
    return hash;
}

void insert(char *sym, double value)
{
    struct symbol *sp = &symtab[symhash(sym) % NHASH];
    int scount = NHASH; /* how many have we looked at */
    while (--scount >= 0)
    {
        if (sp->name && !strcmp(sp->name, sym))
        {
            sp->value = value; 
        }
        if (!sp->name)
        { /* new entry */
            sp->name = strdup(sym);
            sp->value = value;
            return;
        }
        if (++sp >= symtab + NHASH)
            sp = symtab; /* try the next entry */
    }
    yyerror("symbol table overflow\n");
    abort(); /* tried them all, table is full */
}

struct symbol *lookup(char *sym)
{
    struct symbol *sp = &symtab[symhash(sym) % NHASH];
    int scount = NHASH; /* how many have we looked at */
    while (--scount >= 0)
    {
        if (sp->name && !strcmp(sp->name, sym))
        {
            return sp;
        }
        if (!sp->name)
        { /* new entry */
            sp->name = strdup(sym);
            sp->value = 0;
            return sp;
        }
        if (++sp >= symtab + NHASH)
            sp = symtab; /* try the next entry */
    }
    yyerror("symbol table overflow\n");
    abort(); /* tried them all, table is full */
}

struct symlist *
newsymlist(struct symbol *sym, struct symlist *next)
{
    struct symlist *sl = malloc(sizeof(struct symlist));

    if (!sl)
    {
        yyerror("out of space");
        exit(0);
    }
    sl->sym = sym;
    sl->next = next;
    return sl;
}
/* free a list of symbols */
void symlistfree(struct symlist *sl)
{
    struct symlist *nsl;
    while (sl)
    {
        nsl = sl->next;
        free(sl);
        sl = nsl;
    }
}

struct ast *newast(int nodetype, struct ast *l, struct ast *r)
{
    struct ast *a = malloc(sizeof(struct ast));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *newnum(double d)
{
    struct numval *a = malloc(sizeof(struct numval));

    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->number = d;
    return (struct ast *)a;
}

double eval(struct ast *a)
{
    double v;
    switch (a->nodetype)
    {
    case 'K':
        v = ((struct numval *)a)->number;
        break;
    case '+':
        v = eval(a->l) + eval(a->r);
        break;
    case '-':
        v = eval(a->l) - eval(a->r);
        break;
    case '*':
        v = eval(a->l) * eval(a->r);
        break;
    case '/':
        v = eval(a->l) / eval(a->r);
        break;
    case '|':
        v = eval(a->l);
        if (v < 0)
            v = -v;
        break;
    case 'M':
        v = -eval(a->l);
        break;
    default:
        printf("internal error: bad node %c\n", a->nodetype);
    }
    return v;
}

void treefree(struct ast *a)
{
    switch (a->nodetype)
    {
    /* two subtrees */
    case '+':
    case '-':
    case '*':
    case '/':
        treefree(a->r);
    /* one subtree */
    case '|':
    case 'M':
        treefree(a->l);
    case 'K':
    case 'N':
        break;
    default:
        printf("internal error: free bad node %c\n", a->nodetype);
    }

    free(a); /* always free the node itself */
}

int readscript(char *file)
{
    yyin = fopen(file, "r");
    return yyparse();
    fclose(yyin);
}

void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        return yyparse();
    }

    else if (argc == 2)
    {
        yyin = fopen(argv[1], "r");
        return yyparse();
    }
}