#include <iostream>
#include <cstring>
#include <cctype>
#include "tree.hpp"
#include "well_formed.hpp"
using namespace std;

static int brackets[MAX_SIZE];

bool is_bin_symbol(char c)
{
    return (c == '&') || (c == '|') || (c == '>') || (c == '~');
}

bool is_letter(char c)
{
    return isalpha(c) || (c == '0') || (c == '1');
}    

bool embraced_brackets(const char* input, int start, int end)
{
    return input[start] == '(' && input[end] == ')' && brackets[start] == brackets[end - 1];
}

bool blank(const char* input, int start, int end)
{
    return input[start] == ' ' || input[end] == ' ';
}

bool check_brackets(const char* input)
{
    int state = 0;
    for (int i = 0; input[i]; i++)
    {
        if (input[i] == '(')
            state++;
        else if (input[i] == ')')
            state--;
        if (state < 0)
            return false;
        brackets[i] = state;
    }
    return state == 0;
}

Node* create_tree(const char* input, int start, int end)
{
    for (int i = start; i <= end; i++)
        cout << input[i];
    cout << '\n';

    while (input[start] == ' ' && start < end) start++;
    while (input[end] == ' ' && start < end) end--;
    if (start > end) return NULL;

    if (end - start + 1 > 2 && !embraced_brackets(input, start, end))
        return NULL;
    // uklanjanje spoljnih zagrada i spoljnih blanko znakova
    while (start <= end && (embraced_brackets(input, start, end) || blank(input, start, end)))
    {
        if (!blank(input, start, end))
        {
            start++;
            end--;
        }
        else
        {
            if (input[start] == ' ') start++;
            if (input[end] == ' ') end--;
        }
    }
    if (start > end)
        return NULL;
    
    if (start == end)
    {
        if (is_letter(input[start]))
            return create_node(input[start]);
        return NULL;
    }

    for (int i = start + 1; i <= end; i++) // start + 1 jer ako je binarni operator na poziciji start onda je los format
        if (is_bin_symbol(input[i]))
            if (brackets[start - 1] == brackets[i - 1] && brackets[i] == brackets[end]) // PROBLEM !! start - 1 moze biti van dosega !!
            {
                Node *left = create_tree(input, start, i - 1);
                Node *right = create_tree(input, i + 1, end);
                if (left && right)
                {
                    Node *root = create_node(input[i]);
                    root->left = left;
                    root->right = right;
                    return root;
                }
                return NULL;
            }
    if (input[start] == '*')
        return create_tree(input, start + 1, end);
    return NULL;
}

Node *check_well_form(const char *input)
{
    if (!check_brackets(input))
        return NULL;
    return create_tree(input, 0, strlen(input) - 1);
}
