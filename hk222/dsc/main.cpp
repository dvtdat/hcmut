#include "lib.cpp"

int main()
{
    string s1 = "1+10";
    string s2 = "a&b";
    string s3 = "a b 0 1";

    cout << Infix2Postfix(s1) << '\n';
    cout << Infix2Prefix(s1) << '\n';
    cout << PostfixPrefixCalculator(Infix2Postfix(s1)) << '\n';

    cout << LogicInfix2Postfix(s2) << '\n';
    cout << LogicInfix2Prefix(s2) << '\n';
    cout << LogicPostfixPrefixCalculator(s2, s3) << '\n'; 
}