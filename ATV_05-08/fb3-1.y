/* calculator with AST */
%{
# include <stdio.h>
# include <stdlib.h>
# include "fb3-1.h"
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
%token QUOTE

%%

STATEMENT:
| STATEMENT EOL{
    printf("> ");
    return yyparse();}
| STATEMENT EXP { 
    printf("= %4.4g\n", eval($2));
    treefree($2); }
| STATEMENT START_COMP CALC_SCRIPT { readscript($3); }
| STATEMENT START_COMP OBM_SCRIPT { readscript($3); }
| STATEMENT PRINT '(' STR ')' SEMI_COLON { printf("%s\n", $4); }
| STATEMENT READ '(' VARIABLE ')' SEMI_COLON { printf("Statement read value \n"); }
| STATEMENT DECLARATION { printf("Statement declaration \n"); }
| STATEMENT ASSIGNMENT { printf("Statement assignment \n"); }
;

VARIABLE: NAME
;
 
TYPE: INT | FLOAT | DOUBLE | CHAR
;

VALUE: NAME | NUMBER | EXP
;

ASSIGNMENT: 
VARIABLE ASSIGN VALUE SEMI_COLON
;

DECLARATION:
TYPE VARIABLE SEMI_COLON
| TYPE VARIABLE ASSIGN VALUE SEMI_COLON
;

EXP: 
 EXP '+' EXP { $$ = newast('+', $1,$3); }
 | EXP '-' EXP { $$ = newast('-', $1,$3);}
 | EXP '*' EXP { $$ = newast('*', $1,$3); }
 | EXP '/' EXP { $$ = newast('/', $1,$3); }
 | '|' EXP { $$ = newast('|', $2, NULL); }
 | '(' EXP ')' { $$ = $2; }
 | '-' EXP %prec UMINUS{ $$ = newast('M', NULL, $2); }
 | NUMBER { $$ = newnum($1); }
 ;

%%
