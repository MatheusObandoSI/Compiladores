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

%token <d> NUMBER
%token <s> CALC_SCRIPT
%token EOL
%token START_COMP

%type <a> exp
%type <a> factor 
%type <a> term

%%



calculation: 
| calculation EOL /* blank line or a comment */
| calculation exp {
    printf("= %4.4g\n", eval($2));
    treefree($2);}
| calculation START_COMP CALC_SCRIPT { opencalc($3); }
;

exp: factor
 | exp '+' factor { $$ = newast('+', $1,$3); }
 | exp '-' factor { $$ = newast('-', $1,$3);}
 ;

factor: term
 | factor '*' term { $$ = newast('*', $1,$3); }
 | factor '/' term { $$ = newast('/', $1,$3); }
 ;

term: NUMBER { $$ = newnum($1); }
 | '|' term { $$ = newast('|', $2, NULL); }
 | '(' exp ')' { $$ = $2; }
 ;

%%
