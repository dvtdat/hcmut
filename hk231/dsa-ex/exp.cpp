#include <iostream>

class Exp {
protected:
    int val;
public:
    Exp(): val(0) {}
    Exp(int val): val(val) {}
    virtual ~Exp() {}
    
    /*  When you have a base class with derived classes and you intend to delete objects of the derived classes
        through a pointer to the base class, the base class's destructor should be virtual.
        This allows for the proper cleanup of resources when objects are deleted through a pointer to the base class.
    */

    int eval() {
        return val;
    }

    virtual void printPrefix() = 0;
};

class BinExp : public Exp {
private:
    Exp* left;
    char op;
    Exp* right;
public:
    BinExp(Exp* left, char op, Exp* right): left(left), op(op), right(right) {
        if (op == '+') this->val = left->eval() + right->eval();
        if (op == '-') this->val = left->eval() - right->eval();
        if (op == '*') this->val = left->eval() * right->eval();
        if (op == '/') this->val = left->eval() / right->eval();
    }
    ~BinExp() {
        delete left;
        delete right;
    }

    void printPrefix() {
        std::cout << op << ' ';
        left->printPrefix();
        std::cout << ' ';
        right->printPrefix();
    }
};

class UnExp : public Exp {
private:
    char op;
    Exp* exp;
public:
    UnExp(char op, Exp* exp): op(op), exp(exp) {
        if (op == '-') this->val = -(exp->eval());
    }
    ~UnExp() {
        delete exp;
    }

    void printPrefix() {
        std::cout << op << ". ";
        exp->printPrefix();
    }
};

class IntLit : public Exp {
public:
    IntLit(int val): Exp(val) {}
    ~IntLit() {}

    void printPrefix() {
        if (val < 0) std::cout << "-. " << abs(val);
        else std::cout << val;
    }
};

int main() {
    Exp* intExp1 = new IntLit(1);
    Exp* intExp2 = new IntLit(2);
    Exp* intExp3 = new IntLit(2);

    Exp* binExp1 = new BinExp(intExp1, '+', intExp2);
    Exp* binExp2 = new BinExp(binExp1, '*', intExp3);
    Exp* unExp = new UnExp('-', binExp2);

    unExp->printPrefix();
}