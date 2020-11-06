//date:2020.11.06
//given several strings of arthmetic expression
//output the result of expressions in each line

#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

int simple_calculate(string s)
{
    stack<int> t;
    int res = 0;
    int n = 0;
    char sign = '+';
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] >= '0')
            n = n * 10 + (s[i] - '0');//put the origin number into stack
        if (s[i] < '0' && s[i] != ' ' && s[i] != '(' && s[i] != ')' || i == s.size() - 1) //ignore the space character and paretheses
        {
            int tmp;
            switch (sign)
            {
            case '+':
                t.push(n);
                break;
            case '-':
                t.push(-n);
                break;
            case '*':
                tmp = t.top();
                t.pop();
                t.push(tmp * n); //combine n with the top element for the priority
                break;
            case '/':
                tmp = t.top();
                t.pop();
                t.push(tmp / n);
                break;
            }
            sign = s[i]; //refresh the sign and number
            n = 0;
        }
    }
    while (!t.empty())
    {
        res += t.top(); //just simply add them up
        t.pop();
    }
    return res;
}

int calculate(string s)
{
    stack<int> t;
    string sub;
    int tmp, res;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            t.push(i); //store the position of left paretheses
        }
        if (s[i] == ')')
        {
            tmp = t.top();
            t.pop();
            sub = s.substr(tmp, i - tmp + 1);
            res = simple_calculate(sub);
            sub = to_string(res);
            s.replace(tmp, i - tmp + 1, sub); //use calculate result replace the sub string
        }
    } //now we deal with all the paretheses
    return simple_calculate(s);
}

int main()
{
    string tmp;
    vector<string> save_tmp;
    while (getline(cin, tmp))
    {
        save_tmp.push_back(tmp);
    }
    vector<string>::iterator it;
    for (it = save_tmp.begin(); it != save_tmp.end(); it++)
    {
        cout << calculate(*it) << endl;
    }
    return 0;
}
