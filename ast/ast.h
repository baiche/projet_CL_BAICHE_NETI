
#ifndef AST_H
#define AST_H

#include<stdio.h>

/*

<expression> ::= <expression> <lowop> <term> | <term>
<term> ::= <term> <highop> <factor> | <factor>
<factor> ::= <numeral> | ( <expression> )
<lowop> ::= + | -
<highop> ::= * | /
*/



enum TypeExpr{ Integer, BinaryOperation };
enum OPERATOR{PLUS,MINUS,DIV,MUL};

typedef struct expression expression;
typedef struct expressionBinaire expressionBinaire;

struct expressionBinaire{
  
  enum OPERATOR op;
  struct expression *left,*right;
};

struct expression{
  enum TypeExpr type_expr;
  union {
    struct expressionBinaire *expr;
    int value;
  } content;
};


struct expression*  new_expression_binaire(enum OPERATOR op, 
					   struct expression* left, 
					   struct expression* right);

struct expression* new_int(int i);
expression* simplifier(expression *expr);

int eval(struct expression* e);
int parse(char* cp);
#endif /* AST_H */
