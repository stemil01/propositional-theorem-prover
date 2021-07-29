#include <iostream>
#include <vector>
#include "tree.hpp"
#include "well_formed.hpp"
#include "tableaux.hpp"
using namespace std;

static int occurence[2][MAX_CHAR];

void find_leaves(Tnode* node, vector<Tnode*> &leaves)
{
    if (node)
    {
        if (node->left == NULL && node->right == NULL)
            leaves.push_back(node);
        find_leaves(node->left, leaves);
        find_leaves(node->right, leaves);
    }
}

Tnode* find_next(Tnode* root)
{
    if (root)
    {
        if (!root->used && !root->closed)
            return root;
        Tnode *left = find_next(root->left);
        Tnode *right = find_next(root->right);
        return left ? left : right;
    }
    return NULL;
}

void alpha_rule(Tnode* node, Node* left_formula, Sign left_sign, Node* right_formula, Sign right_sign)
{
    // there are no check of (potentially) unsuccessfull allocations
    Tnode *first = create_tnode(left_formula);
    first->sign = left_sign;
    Tnode *second = create_tnode(right_formula);
    second->sign = right_sign;
    node->left = first; // both left and right can work
    first->left = second;
}

void beta_rule(Tnode* node, Node* left_formula, Sign left_sign, Node* right_formula, Sign right_sign)
{
    // there are no check of (potentially) unsuccessfull allocations
    Tnode *left = create_tnode(left_formula);
    left->sign = left_sign;
    Tnode *right = create_tnode(right_formula);
    right->sign = right_sign;
    node->left = left;
    node->right = right;
}

// should be enough for negation (in order to avoid duplicates in alpha rule)
void negation_rule(Tnode* node, Node* next_formula, Sign sign)
{
    Tnode *next = create_tnode(next_formula);
    next->sign = sign;
    node->left = next;
}

void apply_rule(Tnode* node, Tnode* leaf)
{
    if (!is_letter(node->formula->symbol))
    {
        Node *left_formula = node->formula->left;
        Node *right_formula = node->formula->right;
        if (node->sign == T)
        {
            switch (node->formula->symbol)
            {
            case '&':
                alpha_rule(leaf, left_formula, T, right_formula, T);
                break;
            case '|':
                beta_rule(leaf, left_formula, T, right_formula, T);
                break;
            case '>':
                beta_rule(leaf, left_formula, F, right_formula, T);
                break;
            case '*':
                // alpha_rule(leaf, right_formula, F, right_formula, F);
                negation_rule(leaf, right_formula, F);
                break;
            default:
                cout << "error occured during application of rules\n";
                break;
            }
        }
        else
        {
            switch (node->formula->symbol)
            {
            case '&':
                beta_rule(leaf, left_formula, F, right_formula, F);
                break;
            case '|':
                alpha_rule(leaf, left_formula, F, right_formula, F);
                break;
            case '>':
                alpha_rule(leaf, left_formula, T, right_formula, F);
                break;
            case '*':
                // alpha_rule(leaf, right_formula, T, right_formula, T);
                negation_rule(leaf, right_formula, T);
                break;
            default:
                cout << "error occured during application of rules\n";
                break;
            }
        }
    }
}

void check_tableaux(Tnode* node)
{
    if (node)
    {
        if (is_letter(node->formula->symbol))
        {
            occurence[node->sign][node->formula->symbol]++;
            if (occurence[1 - (node->sign)][node->formula->symbol] > 0) // if there is occurence of letter with opposite sign
                node->closed = true;
        }

        check_tableaux(node->left);
        if (node->left && is_letter(node->left->formula->symbol))
            occurence[node->left->sign][node->left->formula->symbol]--;

        check_tableaux(node->right);
        if (node->right && is_letter(node->right->formula->symbol))
            occurence[node->right->sign][node->right->formula->symbol]--;

        // if all children are closed, then the parent is closed as well
        if (node->left || node->right)
            if ((node->left == NULL || node->left->closed) && (node->right == NULL || node->right->closed))
                node->closed = true;
    }
}

Tnode* create_tableaux(Node* formula)
{
    Tnode *root = create_tnode(formula);
    root->sign = F;
    Tnode *node;
    while ((node = find_next(root)))
    {
        vector<Tnode*> leaves;
        find_leaves(node, leaves);

        for (auto leaf : leaves)
            if (!leaf->closed)
                apply_rule(node, leaf);

        check_tableaux(root);
        node->used = true;
    }
    return root;
}

void all_letters(Tnode* root, bool in_formula[])
{
    if (root)
    {
        if (is_letter(root->formula->symbol))
            in_formula[root->formula->symbol] = true;
        all_letters(root->left, in_formula);
        all_letters(root->right, in_formula);
    }
}


void variations(bool in_formula[], Sign interpretation[], int position)
{
    if (position < MAX_CHAR)
    {
        if (in_formula[position])
        {
            if (occurence[F][position])
            {
                interpretation[position] = F;
                variations(in_formula, interpretation, position + 1);
            }
            else if (occurence[T][position])
            {
                interpretation[position] = T;
                variations(in_formula, interpretation, position + 1);
            }
            else
            {
                // the letter is "free" and can have both truth values
                interpretation[position] = F;
                variations(in_formula, interpretation, position + 1);

                interpretation[position] = T;
                variations(in_formula, interpretation, position + 1);
            }
        }
        else
            variations(in_formula, interpretation, position + 1);
    }
    else
    {
        for (int i = 0; i < MAX_CHAR; i++)
            if (in_formula[i])
                cout << "I(" << (char)i << ") = " << interpretation[i] << "; ";
        cout << '\n';
    }
}

void countermodels(Tnode* root, bool in_formula[], Sign interpretation[])
{
    if (root && !root->closed)
    {
        if (is_letter(root->formula->symbol))
            occurence[root->sign][root->formula->symbol]++;
        if (root->left == NULL && root->right == NULL)
            variations(in_formula, interpretation, 0); // generate all variations for "free" letters
        else
        {
            // left side
            countermodels(root->left, in_formula, interpretation);
            if (root->left && !root->left->closed && is_letter(root->left->formula->symbol))
                occurence[root->left->sign][root->left->formula->symbol]--;

            // right side
            countermodels(root->right, in_formula, interpretation);
            if (root->right && !root->right->closed && is_letter(root->right->formula->symbol))
                occurence[root->right->sign][root->right->formula->symbol]--;
        }
    }
}

void print_countermodels(Tnode* root)
{
    // go throught tableaux to find all letters that occur
    bool in_formula[MAX_CHAR];
    Sign interpretation[MAX_CHAR];
    for (int i = 0; i < MAX_CHAR; i++)
        in_formula[i] = false;
    all_letters(root, in_formula);

    // generate all countermodels
    countermodels(root, in_formula, interpretation);
}
