#include <stdlib.h>
#include<stdio.h>
#include "ast.h"

int globalReadOffset;
 
// Text to read:
char *globalInputText = "";

//where the parsed expr is save after yyparse();
struct expression* e= NULL;




struct expression* new_int(int i){
  struct expression* e = (struct expression*) malloc(sizeof(struct expression));

  e->type_expr = Integer;
  e->content.value = i;

  return e;
}

struct expression*  new_expression_binaire(enum OPERATOR op, 
					   struct expression* left, 
					   struct expression* right){
  struct expression* e = (struct expression*) malloc(sizeof(struct expression));

  e->type_expr = BinaryOperation;

  e->content.expr = (struct expressionBinaire*) malloc(sizeof(expressionBinaire));
  e->content.expr->op = op;
  e->content.expr->left = left;
  e->content.expr->right = right;
  
  return e;
}

void display(struct expression* expression){
  if(expression->type_expr == Integer){
    printf(" %d ", expression->content.value);
  }
  else if(expression->type_expr == BinaryOperation){

    printf(" ( ");
    display(expression->content.expr->left);

    if(expression->content.expr->op == MINUS){
      printf(" - ");
    }
    else if(expression->content.expr->op == PLUS){
      printf(" + ");
    }
    else if(expression->content.expr->op == MUL){
      printf(" * ");
    }
    else if(expression->content.expr->op == DIV){
      printf(" / ");
    }

    display(expression->content.expr->right);
    printf(" ) ");
  }
  else {
    printf("not traited");
  }
}

int eval(expression *expr){
	printf("****** looool eval *******\n");
 
  if(expr->type_expr==Integer) return expr->content.value;
  if(expr->type_expr==BinaryOperation){
    switch(expr->content.expr->op){
    case PLUS :return eval(expr->content.expr->left) + eval(expr->content.expr->right) ;break;
     case MINUS :return eval(expr->content.expr->left) - eval(expr->content.expr->right) ;break;
 	case MUL :return eval(expr->content.expr->left) * eval(expr->content.expr->right) ;break;
    case DIV : return eval(expr->content.expr->left) / eval(expr->content.expr->right) ;break;

    }
  }
	return 0;
}

expression* simplifier(expression *expr){

	if(expr->type_expr==Integer) {
		printf("****** looool 1 *******\n"); 
		return expr;}
	if(expr->type_expr==BinaryOperation){
	
	switch(expr->content.expr->op){
    	
	case PLUS :
		{
		printf("****** looool plus *******\n"); 
		if(eval(expr->content.expr->left)==0)   return simplifier(expr->content.expr->right) ;
		if(eval(expr->content.expr->right)==0)   return simplifier(expr->content.expr->left) ;
		return  new_expression_binaire(expr->content.expr->op, 
					   simplifier(expr->content.expr->left), 
					   simplifier(expr->content.expr->left));
			}
     	case MINUS :
		{
		printf("****** looool moins *******\n"); 
		if (eval(expr->content.expr->left)==eval(expr->content.expr->right)) {printf("****** looool mois a *******\n"); 
		 return new_int(0) ;}break;
		if(eval(expr->content.expr->right)==0) {
		printf("****** looool mois a *******\n");
		return simplifier(expr->content.expr->left); }
		
		return  new_expression_binaire(expr->content.expr->op, 
					   simplifier(expr->content.expr->left), 
					   simplifier(expr->content.expr->left));
		}

 	case MUL :
		{
		printf("****** looool mult *******\n");
		 
		 if(eval(expr->content.expr->left)==1) return simplifier(expr->content.expr->right) ;	
		if(eval(expr->content.expr->right)==1) return simplifier(expr->content.expr->left) ;
		 return  new_expression_binaire(expr->content.expr->op, 
					   simplifier(expr->content.expr->left), 
					   simplifier(expr->content.expr->left));
		}
	
	 case DIV : {
		printf("****** looool div *******\n"); 
		if (eval(expr->content.expr->left)==eval(expr->content.expr->right)) return new_int(1) ;
		if (eval(expr->content.expr->right)==1) return simplifier(expr->content.expr->left) ;
		 return  new_expression_binaire(expr->content.expr->op, 
					   simplifier(expr->content.expr->left), 
					   simplifier(expr->content.expr->left));
		}
	
	}
}
}

int parse(char* cp){
 
  if(*cp == '$' && *(cp + 1) == '['){
    globalInputText = cp;
    yyparse();
    return eval(e); 
  }

  return 0;
}


int main(){
    char* str="$[8*6+9/9 +1*6*7]";
    globalInputText=str;
    
   //printf("*******test de l'evaluateur *******\n");
   //printf("%d\n",parse(str));
   //e=NULL;
	
  printf("******** test du parser ********\n ");
   yyparse();
   display(e);
  // printf("********** test du simplifieur ***********\n");
	

   //globalInputText="$[8*6+9-0]";
   //yyparse();
  //printf("%d\n",parse(str));
  // yyparse();

/*
   printf("******avant simplification *******\n");   
	//display(e);
   printf("******apres simplification *******\n"); 
   e=simplifier(e);
  	display(e);
  */
   return 0;
}

