#include <iostream>
#include <vector>
#include "tree.hpp"
#include "tableaux.hpp"
using namespace std;

static vector<Tnode*> leaves;

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
    if (tnode->sign == 'T' && tnode->root->symbol == '&') // T A&B
    {
        Tnode *tnode1 = create_tnode('T', tnode->root->left);
        Tnode *tnode2 = create_tnode('T', tnode->root->right);
        leaf->left = tnode1;
        tnode1->left = tnode2;
    }
    if (tnode->sign == 'F' && tnode->root->symbol == '|') // F A|B
    {
        Tnode *tnode1 = create_tnode('F', tnode->root->left);
        Tnode *tnode2 = create_tnode('F', tnode->root->right);
        leaf->left = tnode1;
        tnode1->left = tnode2;
    }
    if (tnode->sign == 'F' && tnode->root->symbol == '>') // F A>B
    {
        Tnode *tnode1 = create_tnode('T', tnode->root->left);
        Tnode *tnode2 = create_tnode('F', tnode->root->right);
        leaf->left = tnode1;
        tnode1->left = tnode2;
    }
    if (tnode->sign == 'F' && tnode->root->symbol == '*') // F *A
    {
        Tnode *tnode1 = create_tnode('T', tnode->root->right);
        Tnode *tnode2 = create_tnode('T', tnode->root->right);
        leaf->left = tnode1;
        tnode1->left = tnode2;
    }
    if (tnode->sign == 'T' && tnode->root->symbol == '*') // T *A
    {
        Tnode *tnode1 = create_tnode('F', tnode->root->right);
        Tnode *tnode2 = create_tnode('F', tnode->root->right);
        leaf->left = tnode1;
        tnode1->left = tnode2;
    }

    // BETA FORMULAS
    if (tnode->sign == 'F' && tnode->root->symbol == '&') // F A&B
    {
        Tnode *tnode1 = create_tnode('F', tnode->root->left);
        Tnode *tnode2 = create_tnode('F', tnode->root->right);
        leaf->left = tnode1;
        leaf->right = tnode2;
    }
    if (tnode->sign == 'T' && tnode->root->symbol == '|') // T A|B
    {
        Tnode *tnode1 = create_tnode('T', tnode->root->left);
        Tnode *tnode2 = create_tnode('T', tnode->root->right);
        leaf->left = tnode1;
        leaf->right = tnode2;
    }
    if (tnode->sign == 'T' && tnode->root->symbol == '>') // T A>B
    {
        Tnode *tnode1 = create_tnode('F', tnode->root->left);
        Tnode *tnode2 = create_tnode('T', tnode->root->right);
        leaf->left = tnode1;
        leaf->right = tnode2;
    }
}

Tnode* create_tableuax(Node* root)
{
    Tnode *troot = create_tnode('F', root); // starting tableaux with F "formula"

    while (Tnode *tnode = find_root(troot))
    {
        tnode->used = true;

        find_leaves(tnode);

        for (Tnode *leaf : leaves)
            apply_rules(tnode, leaf);

        leaves.clear(); // empty the vector for leaves of next unused signed node
    }

    return troot;
}
