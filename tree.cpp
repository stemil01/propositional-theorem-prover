#include <iostream>
#include <string>
#include "tree.hpp"
#include "well_formed.hpp"
using namespace std;

Node* create_node(char symbol)
{
    Node *new_node = new Node;
    if (new_node == NULL)
        return NULL;
    new_node->symbol = symbol;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node* copy_tree(Node* root)
{
    if (root)
    {
        Node *left = copy_tree(root->left);
        Node *right = copy_tree(root->right);
        Node *new_root = create_node(root->symbol);
        new_root->left = left;
        new_root->right = right;
        return new_root;
    }
    return NULL;
}

void print_tree(Node* root)
{
    if (root)
    {
        print_tree(root->left);
        cout << root->symbol << " ";
        print_tree(root->right);
    }
}

void print_formula(Node* root)
{
    if (root)
    {
        bool left_brackets = root->left && is_bin_symbol(root->left->symbol);
        bool right_brackets = root->right && is_bin_symbol(root->right->symbol);

        // print left side with brackets if needed
        if (left_brackets) cout << "(";
        print_formula(root->left);
        if (left_brackets) cout << ")";

        if (root->left) cout << ' ';
        cout << root->symbol;
        if (root->right && root->symbol != '*') cout << ' '; // we don't want negation separated from letter

        // print right side with brackets if needed
        if (right_brackets) cout << "(";
        print_formula(root->right);
        if (right_brackets) cout << ")";
    }
}

void free_tree(Node* root)
{
    if (root)
    {
        free_tree(root->left);
        free_tree(root->right);
        delete root;
    }
}

Tnode* create_tnode(char s, Node *root)
{
    Tnode *tnode = new Tnode;
    if (tnode == NULL)
        return NULL;

    tnode->sign = s;
    tnode->root = root;
    tnode->left = NULL;
    tnode->right = NULL;
    tnode->used = false;

    return tnode;
}

void t_free_tree(Tnode* root)
{
    if (root)
    {
        t_free_tree(root->left);
        t_free_tree(root->right);
        delete root;
    }
}

//customized print2DUtil for signed formula
static const int COUNT = 7;

void print_signed_2D(Tnode *troot, int space)
{
    if(troot == NULL)
        return ;

    space += COUNT;

    print_signed_2D(troot->right, space);

    printf("\n");

    for(int i = COUNT; i < space ; i++)
        printf(" ");

    cout<<troot->sign<< " ";
    print_formula(troot->root);
    cout<<'\n';

    print_signed_2D(troot->left, space);

}
