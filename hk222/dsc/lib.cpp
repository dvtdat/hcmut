#include "lib.h"

template <typename T> T add(const T & a, const T & b) { return a + b; }
template <typename T> T sub(const T & a, const T & b) { return a - b; }
template <typename T> T mul(const T & a, const T & b) { return a * b; }
template <typename T> T div(const T & a, const T & b) { return a / b; }
template <typename T> T exp(const T & a, const T & b) { return pow(a, b); }

template <typename T> T non(const T & a, const T & b) { return true; }
template <typename T> T con(const T & a, const T & b) { return a & b; }
template <typename T> T dis(const T & a, const T & b) { return a | b; }
template <typename T> T imp(const T & a, const T & b) { return !a | b; }
template <typename T> T neg(const T & a, const T & b) { return !a; }
template <typename T> T eql(const T & a, const T & b) { return !(a ^ b); }

string rounding(double val)
{
    stringstream tmp;
    tmp << fixed << setprecision(4) << val;

    if (tmp.str()[tmp.str().length() - 1] != '0') return tmp.str();
    for (int i = tmp.str().length() - 1; i >= 0; --i)
    {
        if (tmp.str()[i] == '.') return tmp.str().substr(0, i);
        if (tmp.str()[i] != '0') return tmp.str().substr(0, i + 1);
    }
    return tmp.str();
}

bool isOp(char c)
{
    string check = "+-*/^";
    for (int i = 0; i < (int)check.length(); ++i)
    {
        if (c == check[i]) return true;
    }
    return false;
}

myOp getOpFunc(char c)
{
    switch (c)
    {
        case '+': return add<double>;
        case '-': return sub<double>;
        case '*': return mul<double>;
        case '/': return div<double>;
        case '^': return exp<double>;
        default: return nullptr;
    }
}

bool isLogOp(string s)
{
    string check[5] = {"&", "|", "->", "~", "<->"};
    for (int i = 0; i < 5; ++i)
    {
        if (s == check[i]) return true;
    }
    return false;
}

myLogOp getLogOpFunc(string s)
{
    if (s == "&") return con<bool>;
    if (s == "|") return dis<bool>;
    if (s == "->") return imp<bool>;
    if (s == "~") return neg<bool>;
    if (s == "<->") return eql<bool>;
    return non<bool>;
}

int priority[200];
string in[1000];

string Infix2Postfix(string s)
{
    s = '(' + s + ')';

    priority['('] = priority[')'] = 0;
    priority['+'] = priority['-'] = 1;
    priority['*'] = priority['/'] = 2;
    priority['^'] = 3;

    int cnt = 0;
    string tmp;
    for (int i = 0; i < (int)s.length(); ++i)
    {
        if (s[i] == '(' || s[i] == ')' || isOp(s[i]))
        {
            if (tmp != "") in[cnt++] = tmp; 
            in[cnt++] = s[i]; tmp = "";
        }
        else tmp += s[i];
    }
    
    string post = "";
    stack<string> st;

    for (int i = 0; i < cnt; ++i)
    {
        if (in[i] == "(")
        {
            st.push("(");
        }
        else if (in[i] == ")")
        {
            while (!st.empty() && st.top() != "(")
            {
                post += st.top(); st.pop();
                post += ' ';
            }
            st.pop();
        }
        else if (isOp(in[i][0]))
        {
            while (!st.empty() && priority[(int)st.top()[0]] >= priority[(int)in[i][0]])
            {
                post += st.top(); st.pop();
                post += ' ';
            }
            st.push(in[i]);
        }
        else
        {
            post += in[i];
            post += ' ';
        }
    }

    while (!st.empty())
    {
        post += st.top(); st.pop();
        post += ' ';
    }

    return post;
}

string Infix2Prefix(string s)
{
    s = '(' + s + ')';

    priority['('] = priority[')'] = 0;
    priority['+'] = priority['-'] = 1;
    priority['*'] = priority['/'] = 2;
    priority['^'] = 3;

    int cnt = 0;
    string tmp;
    for (int i = 0; i < (int)s.length(); ++i)
    {
        if (s[i] == '(' || s[i] == ')' || isOp(s[i]))
        {
            if (s[i] == '(') s[i] = ')';
            else if (s[i] == ')') s[i] = '(';

            if (tmp != "") in[cnt++] = tmp; 
            in[cnt++] = s[i]; tmp = "";
        }
        else tmp += s[i];
    }
    reverse(in, in + cnt);
    
    string pre = "";
    stack<string> st;

    for (int i = 0; i < cnt; ++i)
    {
        if (in[i] == "(")
        {
            st.push("(");
        }
        else if (in[i] == ")")
        {
            while (!st.empty() && st.top() != "(")
            {
                pre = st.top() + ' ' + pre; st.pop();
            }
            st.pop();
        }
        else if (isOp(in[i][0]))
        {
            while (!st.empty() && priority[(int)st.top()[0]] > priority[(int)in[i][0]])
            {
                pre = st.top() + ' ' + pre; st.pop();
            }
            st.push(in[i]);
        }
        else
        {
            pre = in[i] + ' ' + pre;
        }
    }

    while (!st.empty())
    {
        pre = st.top() + ' ' + pre; st.pop();
    }
    
    return pre;
}

string PostfixPrefixCalculator(string input)
{
    if (isOp(input[0])) goto prefix;
    else goto postfix; 

prefix:
{
    stringstream ss(input);
    string s;

    stack<double> valStack;

    vector<string> inp;
    while (ss >> s) inp.push_back(s);
    reverse(inp.begin(), inp.end());

    for (int i = 0; i < (int)inp.size(); ++i)
    {
        s = inp[i];
        if (!isOp(s[0])) 
        {
            valStack.push(atof(s.data()));
        }
        else
        {
            double a = valStack.top();
            valStack.pop();    
            double b = valStack.top();
            valStack.pop();

            valStack.push(getOpFunc(s[0])(a, b));
        }
    }
    
    return rounding(valStack.top());
}
postfix:
{
    stringstream ss(input);
    string s;

    stack<double> valStack;
    stack<char> opStack;

    while (ss >> s)
    {
        if (s.size() == 1 && isOp(s[0]))
        {
            opStack.push(s[0]);
        }
        else
        {
            valStack.push(atof(s.data()));
        }

        if (opStack.size())
        {
            double a = valStack.top();
            valStack.pop();    
            double b = valStack.top();
            valStack.pop();
        
            valStack.push(getOpFunc(opStack.top())(b, a));
            opStack.pop();
        }
    }

    return rounding(valStack.top());
}
}

int logPriority(string s)
{
    if (s == "(" || s == ")") return 0;
    if (s == "->") return 1;
    if ( s == "<->") return 2;
    if (s == "&" || s == "|") return 3;
    if (s == "~") return 4;
    return 0;
}

string LogicInfix2Postfix(string s)
{
    int cnt = 1;
    in[0] = "(";
    string tmp;
    for (int i = 0; i < (int)s.length(); ++i)
    {
        if (s[i] == ' ') continue;
        if (('a' <= s[i] && s[i] <= 'z') || s[i] == '~' || s[i] == '(' || s[i] == ')')
        {
            if (tmp != "")
            {
                in[cnt++] = tmp; tmp = "";
            }
            in[cnt++] = s[i]; 
        }
        else tmp += s[i];
    }
    in[cnt++] = ")";
    
    string post = "";
    stack<string> st;

    for (int i = 0; i < cnt; ++i)
    {
        if (in[i] == "(")
        {
            st.push("(");
        }
        else if (in[i] == ")")
        {
            while (!st.empty() && st.top() != "(")
            {
                post += st.top(); st.pop();
            }
            st.pop();
        }
        else if (isLogOp(in[i]))
        {
            while (!st.empty() && logPriority(st.top()) >= logPriority(in[i]))
            {
                post += st.top(); st.pop();
            }
            st.push(in[i]);
        }
        else
        {
            post += in[i];
        }
    }

    while (!st.empty())
    {
        post += st.top(); st.pop();
    }

    return post;    
}

string LogicInfix2Prefix(string s)
{
    int cnt = 1;
    in[0] = ")";
    string tmp;
    for (int i = 0; i < (int)s.length(); ++i)
    {
        if (s[i] == ' ') continue;
        if (('a' <= s[i] && s[i] <= 'z') || s[i] == '~' || s[i] == '(' || s[i] == ')')
        {
            if (s[i] == '(') s[i] = ')';
            else if (s[i] == ')') s[i] = '(';

            if (tmp != "")
            {
                in[cnt++] = tmp; tmp = "";
            }
            in[cnt++] = s[i]; 
        }
        else tmp += s[i];
    }
    in[cnt++] = "(";
    reverse(in, in + cnt);

    string pre = "";
    stack<string> st;

    for (int i = 0; i < cnt; ++i)
    {
        if (in[i] == "(")
        {
            st.push("(");
        }
        else if (in[i] == ")")
        {
            while (!st.empty() && st.top() != "(")
            {
                pre = st.top() + pre; st.pop();
            }
            st.pop();
        }
        else if (isLogOp(in[i]))
        {
            while (!st.empty() && logPriority(st.top()) > logPriority(in[i]))
            {
                pre = st.top() + pre; st.pop();
            }
            st.push(in[i]);
        }
        else
        {
            pre = in[i] + pre;
        }
    }

    while (!st.empty())
    {
        pre = st.top() + pre; st.pop();
    }
    
    return pre;
}

string LogicPostfixPrefixCalculator(string s, string var)
{
    int cnt = 0;
    string tmp = "";
    for (int i = 0; i < (int)s.length(); ++i)
    {
        if (('a' <= s[i] && s[i] <= 'z') || s[i] == '~' || s[i] == '&' || s[i] == '|')
        {
            if (tmp != "")
            {
                in[cnt++] = tmp; tmp = "";
            }
            in[cnt++] = s[i]; 
        }
        else if (tmp == "->" || tmp == "<->")
        {
            in[cnt++] = tmp; tmp = s[i];
        }
        else tmp += s[i];
    }
    if (tmp != "") in[cnt++] = tmp;

    bool val[210];
    for (int i = 0; i < 200; ++i) val[i] = false;

    for (int i = 0; i < (int)var.length() / 2; ++i)
    {
        if (var[i] == ' ') continue;
        val[var[i] - 'a'] = var[i + var.length() / 2 + 1] - '0';
    }

    if (isLogOp(in[0]))
    {
        stack<bool> valStack;
        reverse(in, in + cnt);

        for (int i = 0; i < cnt; ++i)
        {
            if (!isLogOp(in[i]))
            {
                valStack.push(val[in[i][0] - 'a']);
                continue;
            }
            
            if (in[i] == "~" && !valStack.empty())
            {
                bool a = valStack.top();
                valStack.pop(); 
                valStack.push(getLogOpFunc(in[i])(a, a));
                continue;
            }
            
            if (valStack.size() >= 2)
            {
                bool a = valStack.top();
                valStack.pop();    
                bool b = valStack.top();
                valStack.pop();
                valStack.push(getLogOpFunc(in[i])(a, b));
            }
            
        }
        
        if (valStack.empty()) return "FALSE";
        return (valStack.top() ? "TRUE" : "FALSE");
    }

    stack<bool> valStack;
    stack<string> opStack;

    for (int i = 0; i < cnt; ++i)
    {
        if (isLogOp(in[i])) opStack.push(in[i]);
        else valStack.push(val[in[i][0] - 'a']);

        if (opStack.size())
        {
            if (opStack.top() == "~" && !valStack.empty())
            {
                bool a = valStack.top();
                valStack.pop(); 
                valStack.push(getLogOpFunc(opStack.top())(a, a));
                opStack.pop();
                continue;
            }
            
            if (valStack.size() >= 2 && !opStack.empty())
            {
                bool a = valStack.top();
                valStack.pop();    
                bool b = valStack.top();
                valStack.pop();
                valStack.push(getLogOpFunc(opStack.top())(b, a));
                opStack.pop();
            }
        }
    }

    if (valStack.empty()) return "FALSE";
    return (valStack.top() ? "TRUE" : "FALSE");
}    
