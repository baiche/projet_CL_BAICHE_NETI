#include<stdio.h>
#include "ast.h"



expression* simplifier(expression *expr){

	if(expr->type_expr==Integer) return expr;
	if(expr->type_expr==BinaryOperation){
	switch(expr->content.expr->op){
    	
	case PLUS :
		{
		if(eval(expr->content.expr->left)==0)   return simplifier(expr->content.expr->right) ;break;
		if(eval(expr->content.expr->right)==0)   return simplifier(expr->content.expr->left) ;break;
			}
     	case MINUS :
		{
		if (eval(expr->content.expr->left)==eval(expr->content.expr->right)) return 0 ;break;
		if(eval(expr->content.expr->right)==0) return simplifier(expr->content.expr->left); break;	
		}

 	case MUL :
		{
		 if(eval(expr->content.expr->left)==1) return simplifier(expr->content.expr->right) ;break;	
		if(eval(expr->content.expr->right)==1) return simplifier(expr->content.expr->left) ;break ;
		}
	
	 case DIV : 
		if (eval(expr->content.expr->left)==eval(expr->content.expr->right)) return 1;break;
		if (eval(expr->content.expr->right)==1) return simplifier(expr->content.expr->left) ;break;
		}
	}
}
