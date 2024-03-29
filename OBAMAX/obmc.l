
/* recognize tokens for the calculator */
%option noyywrap nodefault yylineno
%{
# include "obmc.h"
# include "obmc.tab.h"
%}

/* float exponent */
EXP ([Ee][-+]?[0-9]+)

%%

 /* Single character operations */
"+" |
"-" |
"*" |
"/" |
"|" |
"(" |
")" { return yytext[0]; }

 /* built-in functions */
"read" { return READ; }
"print" { return PRINT; }

 /* Identifiers */
"int" { return INT; }
"char" { return CHAR; }
"float" { return FLOAT; }
"double" { return DOUBLE; }

"obmc" { return START_COMP; }

 /* Names */
([a-zA-Z][a-zA-Z0-9]+)\.(calc)$ {  yylval.str = yytext; return CALC_SCRIPT; }
([a-zA-Z][a-zA-Z0-9]+)\.(obm)$ {  yylval.str = yytext; return OBM_SCRIPT; }

[a-zA-Z][a-zA-Z0-9]* { yylval.s = lookup(yytext); return NAME; }

 /* Double quoted string */
["]([^"\\\n]|\\(.|\n))*["] {  yylval.str = malloc(yyleng -1);
          memcpy(yylval.str, yytext + 1, yyleng - 2);
          yylval.str[yyleng - 2] = 0; 
          return STR;}

 /* Single quoted strings */
[']([^'\\\n]|\\(.|\n))*['] {  yylval.str = malloc(yyleng -1);
          memcpy(yylval.str, yytext + 1, yyleng - 2);
          yylval.str[yyleng - 2] = 0; 
          return STR;}

[0-9]+"."[0-9]*{EXP}? | 
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }

";" { return SEMI_COLON; }
"=" { return ASSIGN; }
\n { return EOL; }

 /* Ignore */
"//".* ; 
[\t]+ ;
[[:space:]] ;
. { yyerror("Mystery character %c\n", *yytext); }

%%