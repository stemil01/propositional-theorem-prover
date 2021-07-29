#include <iostream>
#include <vector>
#include "tree.hpp"
#include "well_formed.hpp"
#include "tableaux.hpp"
using namespace std;

static vector<Tnode*> leaves;
static int occurence[2][MAX_CHAR];

void find_leaves(Tnode *node)
{
    if(node == NULL)
        return ;

    if(node->left == NULL && node->right == NULL)
        leaves.push_back(node);

    find_leaves(node->left);
    find_leaves(node->right);
}

Tnode* find_root(Tnode* root)
{
    Tnode *left, *right;

    if(root && !(root->used))
        return root;

    if(root && root->left == NULL)
        left =  NULL;
    else
        left = find_root(root->left);

    if(root && root->right == NULL)
        right = NULL;
    else
        right = find_root(root->right);

    return left ? left : right;
}

void apply_rules(Tnode* tnode, Tnode* leaf)
{
    // ALFA FORMULAS
    if (tnode->sign == T && tnode->root->symbol == '&') // T A&B
    {
        Tnode *tnode1 = create_tnode(T, tnode->root->left);
        Tnode *tnode2 = create_tnode(T, tnode->root->right);
        leaf->left = tnode1;
        tnode1->left = tnode2;
    }
    if (tnode->sign == F && tnode->root->symbol == '|') // F A|B
    {
        Tnode *tnode1 = create_tnode(F, tnode->root->left);
        Tnode *tnode2 = create_tnode(F, tnode->root->right);
        leaf->left = tnode1;
        tnode1->left = tnode2;
    }
    if (tnode->sign == F && tnode->root->symbol == '>') // F A>B
    {
        Tnode *tnode1 = create_tnode(T, tnode->root->left);
        Tnode *tnode2 = create_tnode(F, tnode->root->right);
        leaf->left = tnode1;
        tnode1->left = tnode2;
    }
    if (tnode->sign == F && tnode->root->symbol == '*') // F *A
    {
        Tnode *tnode1 = create_tnode(T, tnode->root->right);
        Tnode *tnode2 = create_tnode(T, tnode->root->right);
        leaf->left = tnode1;
        tnode1->left = tnode2;
    }
    if (tnode->sign == T && tnode->root->symbol == '*') // T *A
    {
        Tnode *tnode1 = create_tnode(F, tnode->root->right);
        Tnode *tnode2 = create_tnode(F, tnode->root->right);
        leaf->left = tnode1;
        tnode1->left = tnode2;
    }

    // BETA FORMULAS
    if (tnode->sign == F && tnode->root->symbol == '&') // F A&B
    {
        Tnode *tnode1 = create_tnode(F, tnode->root->left);
        Tnode *tnode2 = create_tnode(F, tnode->root->right);
        leaf->left = tnode1;
        leaf->right = tnode2;
    }
    if (tnode->sign == T && tnode->root->symbol == '|') // T A|B
    {
        Tnode *tnode1 = create_tnode(T, tnode->root->left);
        Tnode *tnode2 = create_tnode(T, tnode->root->right);
        leaf->left = tnode1;
        leaf->right = tnode2;
    }
    if (tnode->sign == T && tnode->root->symbol == '>') // T A>B
    {
        Tnode *tnode1 = create_tnode(F, tnode->root->left);
        Tnode *tnode2 = create_tnode(T, tnode->root->right);
        leaf->left = tnode1;
        leaf->right = tnode2;
    }
}

void check_tableaux(Tnode* node)
{
    if (node)
    {
        if (is_letter(node->root->symbol))
        {
            occurence[node->sign][node->root->symbol]++;
            if (occurence[1 - (node->sign)][node->root->symbol] > 0) // if there is occurence of letter with opposite sign
                node->closed = true;
        }

        check_tableaux(node->left);
        if (node->left && is_letter(node->left->root->symbol))
            occurence[node->left->sign][node->left->root->symbol]--;

        check_tableaux(node->right);
        if (node->right && is_letter(node->right->root->symbol))
            occurence[node->right->sign][node->right->root->symbol]--;

        // if all children are closed, then the parent is closed as well
        if (node->left || node->right)
            if ((node->left == NULL || node->left->closed) && (node->right == NULL || node->right->closed))
                node->closed = true;
    }
}

Tnode* create_tableaux(Node* root)
{
    Tnode *troot = create_tnode(F, root); // starting tableaux with F "formula"

    while (Tnode *tnode = find_root(troot))
    {
        tnode->used = true;

        find_leaves(tnode);

        for (Tnode *leaf : leaves)
            if (!leaf->closed)
                apply_rules(tnode, leaf);

        leaves.clear(); // empty the vector for leaves of next unused signed node
        check_tableaux(troot);
    }
    return troot;
}

void all_letters(Tnode* node, bool in_formula[])
{
    if (node)
    {
        if (is_letter(node->root->symbol))
            in_formula[node->root->symbol] = true;
        all_letters(node->left, in_formula);
        all_letters(node->right, in_formula);
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

void countermodels(Tnode* node, bool in_formula[], Sign interpretation[])
{
    if (node && !node->closed)
    {
        if (is_letter(node->root->symbol))
            occurence[node->sign][node->root->symbol]++;
        if (node->left == NULL && node->right == NULL)
            variations(in_formula, interpretation, 0); // generate all variations for "free" letters
        else
        {
            // left side
            countermodels(node->left, in_formula, interpretation);
            if (node->left && !node->left->closed && is_letter(node->left->root->symbol))
                occurence[node->left->sign][node->left->root->symbol]--;

            // right side
            countermodels(node->right, in_formula, interpretation);
            if (node->right && !node->right->closed && is_letter(node->right->root->symbol))
                occurence[node->right->sign][node->right->root->symbol]--;
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
