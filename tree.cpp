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
