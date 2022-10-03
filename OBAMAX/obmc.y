/* calculator with AST */
%{
# include <stdio.h>
# include <stdlib.h>
# include "obmc.h"
%}

%union {
 struct ast *a;
 char *str;
 struct symbol *s; /* which symbol */
 struct symlist *sl;
 double d;
}

%token START_COMP 
%token SEMI_COLON
%token PRINT
%token READ
%token EOL
%token ASSIGN

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> EXP
%token <d> NUMBER
%token <str> NAME
%token <str> STR
%token <str> CALC_SCRIPT
%token <str> OBM_SCRIPT

%token CHAR
%token INT
%token FLOAT 
%token DOUBLE

%%

STATEMENT:
| STATEMENT EOL {
    return yyparse();}
| STATEMENT EXP { 
    printf("= %4.4g\n", eval($2));
    treefree($2); }
| START_COMP CALC_SCRIPT { readscript($2); }
| START_COMP OBM_SCRIPT { readscript($2); }
| PRINT '(' STR ')' SEMI_COLON { printf("%s\n", $3); }
| PRINT '(' EXP ')' SEMI_COLON { printf("%g\n", eval($3));}
| PRINT '(' NAME ')' SEMI_COLON { printf("%g\n", lookup($3)->value);}
| READ '(' NAME ')' SEMI_COLON { printf("Statement read \n"); }
| TYPE NAME SEMI_COLON { lookup($2); }
| NAME ASSIGN NUMBER SEMI_COLON {insert($1, $3); }
| NAME ASSIGN EXP SEMI_COLON {insert($1, eval($3)); }
;

 
TYPE: INT | FLOAT | DOUBLE | CHAR
;

VALUE: NUMBER | EXP
;

ASSIGNMENT: 
NAME ASSIGN VALUE
;

DECLARATION:
TYPE NAME
| TYPE NAME ASSIGN VALUE
;

EXP: 
EXP '+' EXP { $$ = newast('+', $1,$3); }
| EXP '-' EXP { $$ = newast('-', $1,$3);}
| EXP '*' EXP { $$ = newast('*', $1,$3); }
| EXP '/' EXP { $$ = newast('/', $1,$3); }
| '|' EXP { $$ = newast('|', $2, NULL); }
| '(' EXP ')' { $$ = $2; }
| '-' EXP %prec UMINUS{ $$ = newast('M', $2, NULL); }
| NUMBER { $$ = newnum($1); }
| NAME { $$ = newnum(lookup($1)->value); }
;

%%
