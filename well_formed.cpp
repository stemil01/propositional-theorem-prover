#include <iostream>
#include <string.h>
#include "tree.hpp"
#include "well_formed.hpp"
using namespace std;

static int brackets[MAX_SIZE];

bool is_bin_symbol(char c)
{
    return (c == '&') || (c == '|') || (c == '>') || (c == '~');
}

bool check_brackets(const char *input)
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
    while (start <= end && input[start] == '(' && input[end] == ')' && brackets[start] == brackets[end - 1])
    {
        start++;
        end--;
    }
    if (start > end)
        return NULL;
    
    for (int i = start + 1; i <= end; i++) // start + 1 jer ako je binarni operator na poziciji start onda je los format
        if (is_bin_symbol(input[i]))
            if (brackets[start - 1] == brackets[i - 1] && brackets[i] == brackets[end])
            {
                Node *left = create_tree(input, start, i - start + 1);
                Node *right = create_tree(input, i + 1, end - i + 1);
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
