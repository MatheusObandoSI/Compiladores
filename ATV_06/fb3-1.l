
/* recognize tokens for the calculator */
%option noyywrap nodefault yylineno
%{
# include "fb3-1.h"
# include "fb3-1.tab.h"
%}

/* float exponent */
EXP ([Ee][-+]?[0-9]+)
/*OBX ([a-zA-Z][a-zA-Z0-9]*)(\.obx)*/
/*CALC ([a-zA-Z][a-zA-Z0-9]*)(\.calc)*/

%%

 /* Single character operations */
"+" |
"-" |
"*" |
"/" |
"=" |
"|" |
"," |
";" |
"(" |
")" { return yytext[0]; }


 /* comparison ops, all are a CMP token */
 /* ">" { yylval.fn = 1; return CMP; }
"<" { yylval.fn = 2; return CMP; }
"<>" { yylval.fn = 3; return CMP; }
"==" { yylval.fn = 4; return CMP; }
">=" { yylval.fn = 5; return CMP; }
"<=" { yylval.fn = 6; return CMP; }
*/

 /* keywords */
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"do" { return DO; }

 /* "=" { return ASSOCIATION; } */

 /* built-in functions */
"read" { return READ; }
"print" { return PRINT; }

"obmc" { return START_COMP; }

 /* Names */

([a-zA-Z][a-zA-Z0-9]*)\.(calc)$ {  yylval.s = yytext; return CALC_SCRIPT; }
([a-zA-Z][a-zA-Z0-9]*)\.(obmx)$ {  yylval.s = yytext; return OBMX_SCRIPT; }

[a-zA-Z][a-zA-Z0-9]* { yylval.s = yytext; return NAME; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }

\n { return EOL; }
"//".* /* Ignore comentaries */
[ \t] { /* ignore whitespace */ }
. { yyerror("Mystery character %c\n", *yytext); }

%%