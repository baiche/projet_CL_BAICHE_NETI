#ifndef AST_H
#define AST_H
#include <string>


enum Operateur {PLUS, MINUS, MULT, DIV, INTEGER, DOUBLE, NOTHING};

class AST
{
    public:
        AST();
        AST(Operateur op, AST * left, AST * right);
        AST(double valueDouble );
        AST *Parse(std::string& theExpress );
        AST *Getleft() { return _left; }
        void Setleft(AST *val) { _left = val; }
        AST *Getright() { return _right; }
        void Setright(AST *val) { _right = val; }
        double GetvalueDouble() { return _valueDouble; }
        void SetvalueDouble(double val) { _valueDouble = val; }
        Operateur GetOperateur() { return _op; }
        void SetOperateur(Operateur op) { _op = op; }
        double eval();

    private:
        Operateur _op;
        AST *_left;
        AST *_right;
        double _valueDouble;

};

#endif // AST_H
