#include <iostream>
#include "include/AST.h"


using namespace std;

int main()
{
    AST *a1= new AST(MINUS,a1 , a2);
    AST *a2= new AST(MINUS,b1 , b2);
    AST *a3= new AST(PLUS,a , b);

    string expre = "2+2+8";
    AST * test = a1->Parse(expre);

    double res =  test->eval();

    return 0;

}
