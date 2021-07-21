#include <bits/stdc++.h>

using namespace std;

int current = 0, previous = 0; //variables that represent current and previous state//

/*
0 - no input
1 - identified letter
2 - identified negation
3 - identified operator
4 - identified (
5 - identified )
*/

stack <char> Symbol_stack;

bool is_letter(char s)
{
    return (s >= 'a' && s <= 'z');
}

bool is_operator(char s)
{
    return (s == '&' || s == '|' || s == '>' || s == '~');
}

bool read_symbol(char s)
{
    if(current != 1 && current != 5 && is_letter(s))
    {
        previous = current;
        current = 1;
    }

    else if(current != 1 && current != 5 && s == '*')
    {
        previous = current;
        current = 2;
    }

    else if(current != 1 && s == '(')
    {
        Symbol_stack.push('(');
        previous = current;
        current = 4;
    }

    else if((current == 1 || current == 5) && s == ')' && Symbol_stack.size() >= 1)
    {
        Symbol_stack.pop();
        previous = current;
        current = 5;
    }

    else if(current != 3 && current != 2 && previous != 3 && is_operator(s))
    {
        previous = current;
        current = 3;
    }

    else return false;

    return true;

}

int main()
{
    string s;

    getline(cin,s);

    int n = s.length();
    int i;

    if(s[0] != '*' && s[0] != '(')
    {
        cout << "nije dobar";
        return 0;
    }


    for(i = 0 ; i < n ; i++)
    {
        if(!read_symbol(s[i]))
            break;
    }

    if(i == n && Symbol_stack.size() == 0)
        cout << "dobar";

    else
        cout << "nije dobar";


    return 0;
}
