#include <iostream>
#include <string>
#include <stack>
#include <math.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

template <typename T> T add(const T & a, const T & b);
template <typename T> T sub(const T & a, const T & b);
template <typename T> T mul(const T & a, const T & b);
template <typename T> T div(const T & a, const T & b);
template <typename T> T exp(const T & a, const T & b);

template <typename T> T con(const T & a, const T & b);
template <typename T> T dis(const T & a, const T & b);
template <typename T> T imp(const T & a, const T & b);
template <typename T> T neg(const T & a, const T & b);
template <typename T> T eql(const T & a, const T & b);

typedef double (*myOp)(const double &, const double &);
typedef bool (*myLogOp)(const bool &, const bool &);

string Infix2Postfix(string s);
string Infix2Prefix(string s);
string PostfixPrefixCalculator(string input);
string LogicInfix2Postfix(string s);
string LogicInfix2Prefix(string s);
string LogicPostfixPrefixCalculator(string s, string var);
