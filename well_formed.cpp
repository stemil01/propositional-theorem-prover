#include <iostream>
#include "tree.hpp"
#include "well_formed.hpp"
using namespace std;

bool is_bin_symbol(char c)
{
    return (c == '&') || (c == '|') || (c == '>') || (c == '~');
}

Node* check_well_form(const char* input, int length)
{
    int brackets[MAX_SIZE], state = 0;
    for (int i = 0; input[i]; i++)
    {
        if (input[i] == '(')
            state++;
        else if (input[i] == ')')
            state--;
        if (state < 0)
            return NULL;
        brackets[i] = state;
    }
    if (state != 0)
        return NULL;

    int start = 0, end = length - 1;
    while (start <= end && input[start] == '(' && input[end] == ')' && brackets[start] == brackets[end - 1])
    {
        start++;
        end--;
    }
    if (start > end)
        return NULL;
    
    for (int i = start; i <= end; i++)
        if (is_bin_symbol(input[i]))
            if (brackets[start - 1] == brackets[i - 1] && brackets[i] == brackets[end]) // sta ako je start == 0?
            {
                Node *root = create_node(input[i]);
                root->left = check_well_form(input + start, i - start + 1);
                root->right = check_well_form(input + i + 1, end - i + 1);
                return root;
            }
    
}
