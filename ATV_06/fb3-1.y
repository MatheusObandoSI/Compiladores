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
%token PRINT
%token READ
%token EOL
%token SEMI_COLON
%token ASSIGN

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> EXP
%token <d> NUMBER
%token <s> NAME
%token <s> STR
%token <s> CALC_SCRIPT
%token <s> OBMX_SCRIPT

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
| STATEMENT START_COMP CALC_SCRIPT { openscript($3); }
| STATEMENT START_COMP OBMX_SCRIPT { openscript($3); }
| STATEMENT PRINT '(' STR ')' SEMI_COLON { printf("%s\n", $4); }
;

VARIABLE: NAME
;

TYPE: 
INT 
| FLOAT 
| DOUBLE
;

VALUE: NUMBER
; 

DECLARATION:
DECLARATION TYPE VARIABLE SEMI_COLON
| DECLARATION VARIABLE ASSIGN VALUE SEMI_COLON;
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
