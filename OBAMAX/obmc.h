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
    struct ast *func;     /* stmt for the function */
    struct symlist *syms; /* list of dummy args */
};
/* simple symtab of fixed size */
#define NHASH 9997
struct symbol symtab[NHASH];
struct symbol *lookup(char *);
/* list of symbols, for an argument list */
struct symlist
{
    struct symbol *sym;
    struct symlist *next;
};


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

struct symref
{
    int nodetype; /* type N */
    struct symbol *s;
};
struct symasgn
{
    int nodetype; /* type = */
    struct symbol *s;
    struct ast *v; /* value */
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);

struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);


/* build an AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(double d);
/* Open file*/
int readscript(char* file);
/* evaluate an AST */
double eval(struct ast *);
/* delete and free an AST */
void treefree(struct ast *);