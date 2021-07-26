#include <iostream>
#include <cstring>
#include <cctype>
#include "tree.hpp"
#include "well_formed.hpp"
using namespace std;

void format(char* input)
{
    char transformed[MAX_SIZE];
    int ind = 0;
    transformed[ind++] = '(';
    for (int i = 0; input[i]; i++)
        if (input[i] != ' ')
            transformed[ind++] = input[i];
    transformed[ind++] = ')';
    transformed[ind] = '\0';
    strcpy(input, transformed);
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

Node* create_tree(const char* input, int start, int end)
{
    bool embraced = (end - start + 1 > 2) && embraced_brackets(input, start, end);

    while (start <= end && embraced_brackets(input, start, end))
    {
        start++;
        end--;
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
                if (left && right && embraced)
                {
                    if (input[i] == '~')
                    {
                        // decomposing equivalence as konjunction of two implications
                        // e.g. A ~ B to (A > B) & (B > A)
                        Node *left_implication = create_node('>');
                        left_implication->left = left;
                        left_implication->right = right;
                        Node *right_implication = create_node('>');
                        right_implication->left = copy_tree(right);
                        right_implication->right = copy_tree(left);

                        Node *root = create_node('&');
                        root->left = left_implication;
                        root->right = right_implication;
                        return root;
                    }
                    else
                    {
                        Node *root = create_node(input[i]);
                        root->left = left;
                        root->right = right;
                        return root;
                    }
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

Node* check_well_form(char *input)
{
    format(input);
    int length = strlen(input);
    if (!check_brackets(input, 0, length - 1))
        return NULL;
    return create_tree(input, 0, length - 1);
}
