/*
 * Declarations for a calculator fb3-1
 */
/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);

/* symbol table */
struct symbol
{ /* a variable name */
    char *name;
    double value;
};
/* simple symtab of fixed size */
#define NHASH 9997
struct symbol symtab[NHASH];
/* list of symbols, for an argument list */
struct symlist
{
    struct symbol *sym;
    struct symlist *next;
};

struct symbol *lookup(char *);
void insert(char *, struct symbol *);
struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);

/* nodes in the abstract syntax tree */
struct ast
{
    int nodetype;
    struct ast *l;
    struct ast *r;
};
struct numval
{
    int nodetype; /* type K for constant */
    double number;
};


/* build an AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(double d);
/* Open file*/
int readscript(char* file);
/* evaluate an AST */
double eval(struct ast *);
/* delete and free an AST */
void treefree(struct ast *);