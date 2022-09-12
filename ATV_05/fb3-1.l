
/* recognize tokens for the calculator */
%option noyywrap nodefault yylineno
%{
# include "fb3-1.h"
# include "fb3-1.tab.h"
%}

/* float exponent */
EXP ([Ee][-+]?[0-9]+)



/*Calculator*/
%%
"+" |
"-" |
"*" |
"/" |
"|" |
"(" |
")" { return yytext[0]; }

"obmc" { return START_COMP; }

([a-zA-Z][a-zA-Z0-9]*)\.(calc)$ { yylval.s = yytext; return CALC_SCRIPT; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }

\n { return EOL; }
"//".* 
[ \t] { /* ignore whitespace */ }
. { yyerror("Mystery character %c\n", *yytext); }
%%