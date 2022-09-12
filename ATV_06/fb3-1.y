/* calculator with AST */
%{
# include <stdio.h>
# include <stdlib.h>
# include "fb3-1.h"
%}

%union {
 struct ast *a;
 char* s;
 double d;
}

%token START_COMP 

%token <s> CALC_SCRIPT
%token <s> OBMX_SCRIPT

%token IF
%token ELSE
%token WHILE
%token DO

%token PRINT
%token READ

%token EOL

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%token <d> NUMBER
%type <a> EXP
%token <s> NAME

%%

STATEMENT: 
| STATEMENT EOL
| STATEMENT EXP { 
    printf("= %4.4g\n", eval($2));
    treefree($2); }
| STATEMENT START_COMP CALC_SCRIPT { openscript($3); }
| STATEMENT PRINT '('  NAME  ')' ';' { printf("%s\n", $4); }


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
