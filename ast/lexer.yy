%{

/* doit etre inclu avant parser.h */
#include "ast.h"

#include "parser.h"

#undef YY_INPUT
#define YY_INPUT(b,r,s) readInputForLexer(b,&r,s)

%}

BLANC [ \t]+
SYMBOL [\+\-\*\/]
INT [0-9]+

%%

{BLANC} ;	

{SYMBOL} { return yytext[0]; } 

{INT}    { yylval.integer = atoi(yytext); return INT;}

[\$\[\]] { return yytext[0]; }

%%





