#include <iostream>
#include <string>

using namespace std;

class Exp;

class Visitor {
public:
    virtual void visit(Exp* exp) = 0;
    virtual void visitPrintPrefix(Exp* exp) = 0;
    virtual void visitPrintPostfix(Exp* exp) = 0;
};

class Exp {
public:
    int val;

public:
    Exp() : val(0) {}
    Exp(int val) : val(val) {}
    virtual ~Exp() {}

    int eval() {
        return val;
    }

    virtual void accept(Visitor* visitor) {
        visitor->visit(this);
    }

    virtual void acceptPrintPrefix(Visitor* visitor) {
        visitor->visitPrintPrefix(this);
    }

    virtual void acceptPrintPostfix(Visitor* visitor) {
        visitor->visitPrintPostfix(this);
    }
};

class BinExp : public Exp {
public:
    Exp* left;
    char op;
    Exp* right;

public:
    BinExp(Exp* left, char op, Exp* right) : left(left), op(op), right(right) {
        if (op == '+') this->val = left->eval() + right->eval();
        if (op == '-') this->val = left->eval() - right->eval();
        if (op == '*') this->val = left->eval() * right->eval();
        if (op == '/') this->val = left->eval() / right->eval();
    }

    ~BinExp() {
        delete left;
        delete right;
    }

    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }

    void acceptPrintPrefix(Visitor* visitor) override {
        visitor->visitPrintPrefix(this);
    }

    void acceptPrintPostfix(Visitor* visitor) override {
        visitor->visitPrintPostfix(this);
    }
};

class UnExp : public Exp {
public:
    char op;
    Exp* exp;

public:
    UnExp(char op, Exp* exp) : op(op), exp(exp) {
        if (op == '-') this->val = -(exp->eval());
    }

    ~UnExp() {
        delete exp;
    }

    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }

    void acceptPrintPrefix(Visitor* visitor) override {
        visitor->visitPrintPrefix(this);
    }

    void acceptPrintPostfix(Visitor* visitor) override {
        visitor->visitPrintPostfix(this);
    }
};

class IntLit : public Exp {
public:
    IntLit(int val) : Exp(val) {}

    ~IntLit() {}

    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }

    void acceptPrintPrefix(Visitor* visitor) override {
        visitor->visitPrintPrefix(this);
    }

    void acceptPrintPostfix(Visitor* visitor) override {
        visitor->visitPrintPostfix(this);
    }
};

class Eval : public Visitor {
private:
    int result;

public:
    int getResult() const {
        return result;
    }

    void visit(Exp* exp) override {
        // Do nothing for evaluation
    }

    void visit(IntLit* intLit) {
        result = intLit->val;
    }

    void visit(BinExp* binExp) {
        // Do nothing for evaluation
    }

    void visit(UnExp* unExp) {
        // Do nothing for evaluation
    }

    void visitPrintPrefix(Exp* exp) {}
    void visitPrintPostfix(Exp* exp) {}
};

// Define the concrete visitor for printing in prefix format
class PrintPrefix : public Visitor {
private:
    string prefixExpression;

public:
    void visit(Exp* exp) override {
        // Do nothing for printing in prefix format
    }

    void visit(IntLit* intLit) {
        if (intLit->val < 0) {
            prefixExpression += "-. " + to_string(abs(intLit->val)) + " ";
        } else {
            prefixExpression += to_string(intLit->val) + " ";
        }
    }

    void visit(BinExp* binExp) {
        prefixExpression += binExp->op + " ";
        binExp->left->acceptPrintPrefix(this);
        binExp->right->acceptPrintPrefix(this);
    }

    void visit(UnExp* unExp) {
        prefixExpression += unExp->op + ". ";
        unExp->exp->acceptPrintPrefix(this);
    }

    string getPrefixExpression() const {
        return prefixExpression;
    }
    
    void visitPrintPrefix(Exp* exp) {}
    void visitPrintPostfix(Exp* exp) {}
};

// Define the concrete visitor for printing in postfix format
class PrintPostfix : public Visitor {
private:
    string postfixExpression;

public:

    void visit(IntLit* intLit) {
        if (intLit->val < 0) {
            postfixExpression += "-. " + to_string(abs(intLit->val)) + " ";
        } else {
            postfixExpression += to_string(intLit->val) + " ";
        }
    }

    void visit(BinExp* binExp) {
        binExp->left->acceptPrintPostfix(this);
        binExp->right->acceptPrintPostfix(this);
        postfixExpression += binExp->op + " ";
    }

    void visit(UnExp* unExp) {
        unExp->exp->acceptPrintPostfix(this);
        postfixExpression += unExp->op + ". ";
    }

    string getPostfixExpression() const {
        return postfixExpression;
    }

    void visit(Exp* exp) {}
    void visitPrintPrefix(Exp* exp) {}
    void visitPrintPostfix(Exp* exp) {}
};

int main() {
    // Create an expression tree: 2 * (3 + 4)
    Exp* expression = new BinExp(new IntLit(2), '*', new BinExp(new IntLit(3), '+', new IntLit(4)));

    // Create visitors
    Eval eval;
    PrintPrefix pre;
    PrintPostfix pos;

    // Evaluate the expression
    expression->accept(&eval);
    int result = eval.getResult();
    cout << "Evaluation result: " << result << endl;

    // Print in prefix format
    expression->acceptPrintPrefix(&pre);
    cout << "Prefix format: " << pre.getPrefixExpression() << endl;

    // Print in postfix format
    expression->acceptPrintPostfix(&pos);
    cout << "Postfix format: " << pos.getPostfixExpression() << endl;

    delete expression; // Clean up the dynamically allocated memory

    return 0;
}
