#include "lib.cpp"

int main()
{
    string s = "2+4/5+((1+2)*(3*(4^5))+7^9)";
    cout << Infix2Postfix(s) << '\n';
    cout << Infix2Prefix(s);
}