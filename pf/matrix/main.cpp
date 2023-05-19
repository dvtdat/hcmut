#include "matrix.cpp"

template <typename T> T add(const T & a, const T & b) { return a + b; }
template <typename T> T sub(const T & a, const T & b) { return a - b; }
template <typename T> T mul(const T & a, const T & b) { return a * b; }
template <typename T> T div(const T & a, const T & b) { return a / b; }

typedef float (*myOp)(const float &, const float &);
myOp getOpFunc(char c)
{
    switch (c)
    {
        case '+': return add<float>;
        case '-': return sub<float>;
        case '*': return mul<float>;
        case '/': return div<float>;
        default: break;
    }
}


float calPostFixExpr(const string & str)
{
    stringstream ss(str);
    string s;

    MyVector<float> valStack;
    valStack.resize(128);

    MyVector<char> opStack;
    opStack.resize(128);

    while (ss >> s)
    {
        if (s.size() == 1 && (s[0] < '0' || s[0] > '9') && s[0] != '.')
        {
            opStack.push(s[0]);
        }
        else
        {
            valStack.push(atof(s.data()));
        }

        if (opStack.size())
        {
            float a = valStack.top();
            valStack.pop();    
            float b = valStack.top();
            valStack.pop();
        
            valStack.push(getOpFunc(opStack.top())(b, a));
            opStack.pop();
        }
    }

    return valStack.top();
}

int main(int narg, char** argv)
{
    /*
    int nR, nC;

    stringstream ss("2 3");
    ss >> nR >> nC;

    MyMatrix mat(nR, nC);

    for (int i = 0; i < mat.getNRows(); ++i)
    {
        for (int j = 0; j < mat.getNCols(); ++j)
        {
            mat.at(i, j) = (rand() % 101) * 0.01f;
        }
    }

    cout << mat << '\n';
    cout << mat * 2.0f << '\n';
    // MyMatrix B = (mat * 2.0f), C(mat);
    // mat = std::move(B);

    // cout << B << '\n';
    */

   srand(time(NULL));

    MyVector<float> V;
    V.resize(128);

    for (int i = 0; i < 8; ++i) V.push((rand() % 101) * .01f);
    for (int i = 0; i < V.size(); ++i) cout << V[i] << ' ';
    cout << '\n';


    string str = "3 5 - 6 / 3 2 / 1 - * 8 4 * 6 3 2 + * - -";
    cout << "Expression " << str << " = " << calPostFixExpr(str) << '\n';
}