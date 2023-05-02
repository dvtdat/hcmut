#include "lib.h"

bool isOperator(char c)
{
    string check = "+-*/^";
    for (int i = 0; i < (int)check.length(); ++i)
    {
        if (c == check[i]) return true;
    }
    return false;
}

int priority[200];
string in[300];

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
        if (s[i] == '(' || s[i] == ')' || isOperator(s[i]))
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
        else if (isOperator(in[i][0]))
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
        if (s[i] == '(' || s[i] == ')' || isOperator(s[i]))
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
        else if (isOperator(in[i][0]))
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