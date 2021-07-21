#include <iostream>
#include <cstring>
#include <cctype>
#include "tree.hpp"
#include "well_formed.hpp"
using namespace std;

void input_form(const char* input, char* tranformed)
{
    int ind = 0;
    tranformed[ind++] = '(';
    for (int i = 0; input[i]; i++)
        if (input[i] != ' ')
            tranformed[ind++] = input[i];
    tranformed[ind++] = ')';
    tranformed[ind] = '\0';
}

bool is_bin_symbol(char c)
{
    return (c == '&') || (c == '|') || (c == '>') || (c == '~');
}

bool is_letter(char c)
{
    return isalpha(c) || (c == '0') || (c == '1');
}    

bool check_brackets(const char* input, int start, int end)
{
    int state = 0;
    for (int i = start; i <= end; i++)
    {
        if (input[i] == '(')
            state++;
        else if (input[i] == ')')
            state--;
        if (state < 0)
            return false;
    }
    return state == 0;
}

bool embraced_brackets(const char* input, int start, int end)
{
    return input[start] == '(' && input[end] == ')' && check_brackets(input, start + 1, end - 1);
}

bool blank(const char* input, int start, int end)
{
    return input[start] == ' ' || input[end] == ' ';
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
            if (check_brackets(input, start, i - 1) && check_brackets(input, i + 1, end))
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
    {
        Node *right = create_tree(input, start + 1, end);
        if (right)
        {
            Node *root = create_node('*');
            root->right = right;
            return root;
        }
        return NULL;
    }
    return NULL;
}

Node *check_well_form(const char *input)
{
    int length = strlen(input);
    if (!check_brackets(input, 0, length - 1))
        return NULL;
    return create_tree(input, 0, length - 1);
}
