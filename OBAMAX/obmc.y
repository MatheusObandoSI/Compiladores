/* calculator with AST */
%{
# include <stdio.h>
# include <stdlib.h>
# include "obmc.h"
%}

%union {
 struct ast *a;
 char *s;
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
%token <s> NAME
%token <s> STR
%token <s> CALC_SCRIPT
%token <s> OBM_SCRIPT

%token CHAR
%token INT
%token FLOAT 
%token DOUBLE

%%

STATEMENT:
| STATEMENT EOL {
    printf("> ");
    return yyparse();}
| STATEMENT EXP { 
    printf("= %4.4g\n", eval($2));
    treefree($2); }
| START_COMP CALC_SCRIPT { readscript($2); }
| START_COMP OBM_SCRIPT { readscript($2); }
| PRINT '(' STR ')' SEMI_COLON { printf("%s\n", $3); }
| READ '(' NAME ')' SEMI_COLON { printf("Statement read value \n"); }
| DECLARATION SEMI_COLON { printf("Statement declaration \n"); }
| ASSIGNMENT SEMI_COLON { printf("Statement assignment \n"); }
;

 
TYPE: INT | FLOAT | DOUBLE | CHAR
;

VALUE: NAME | NUMBER | EXP
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
;

%%
