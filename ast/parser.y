%{

#include <string.h>
#include<stdio.h>
#include"ast.h"

extern int globalReadOffset;
 
// Text to read:
 extern char *globalInputText;
 extern struct expression* e;

 extern int readInputForLexer(char *buffer, int *numBytesRead, int maxBytesToRead);

%}

%union {int integer; struct expression* expression; }

%token <integer>INT

%type <expression> expr

%start MainExpr

%left '-' '+'
%left '*' '/'

%% 

MainExpr : 
  '$' '[' expr ']' { e = $3 }
;

expr :       expr '+' expr  { $$ = new_expression_binaire(PLUS, $1, $3 ); }
| expr '-' expr  { $$ = new_expression_binaire(MINUS, $1, $3 ); }
| expr '*' expr  { $$ = new_expression_binaire(MUL, $1, $3 ); }
| expr '/' expr  { $$ = new_expression_binaire(DIV, $1, $3 ); }
| INT            { $$ = new_int($1); }
;
%%

int yyerror(char* s){
    printf("Error throw by Mourad: syntax error.\n");
    return 0;
}

int readInputForLexer(char *buffer, int *numBytesRead, int maxBytesToRead) {
  int numBytesToRead = maxBytesToRead;
  int bytesRemaining = strlen(globalInputText)-globalReadOffset;
  int i;
 
  if ( numBytesToRead > bytesRemaining ) { numBytesToRead = bytesRemaining; }
  
  for ( i = 0; i < numBytesToRead; i++ ) {
    buffer[i] = globalInputText[globalReadOffset+i];
  }
  
  *numBytesRead = numBytesToRead;
  globalReadOffset += numBytesToRead;
  
  return 0;
}
