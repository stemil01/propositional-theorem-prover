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

void free_tree(Node* root)
{
    if (root)
    {
        free_tree(root->left);
        free_tree(root->right);
        delete root;
    }
}

Tnode* create_tnode(Node* formula)
{
    Tnode *new_tnode = new Tnode;
    if (new_tnode == NULL)
        return NULL;

    new_tnode->formula = formula;
    new_tnode->left = NULL;
    new_tnode->right = NULL;
    new_tnode->used = false;
    new_tnode->closed = false;

    return new_tnode;
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

// GeeksforGeeks code for printing binary tree vertically
static const int COUNT = 4;

void print2DUtil(Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    cout << root->symbol << '\n';
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(Node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}

void t_print2DUtil(Tnode *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    t_print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    root->sign == T ? cout << "T " : cout << "F ";
    // root->closed ? cout << "x " : cout << "o ";
    print_formula(root->formula);
 
    // Process left child
    t_print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void t_print2D(Tnode *root)
{
   // Pass initial space count as 0
   t_print2DUtil(root, 0);
}
